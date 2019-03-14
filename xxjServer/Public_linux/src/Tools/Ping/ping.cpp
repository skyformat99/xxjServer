#include "ping.h"
#ifdef WIN32
USHORT CPing::s_usPacketSeq = 0;

CPing::CPing() :
	m_szICMPData(NULL),
	m_bIsInitSucc(FALSE)
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(1, 1), &WSAData);

	m_event = WSACreateEvent();
	m_usCurrentProcID = (USHORT)GetCurrentProcessId();

	if ((m_sockRaw = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0, 0)) != SOCKET_ERROR)
	{
		WSAEventSelect(m_sockRaw, m_event, FD_READ);
		m_bIsInitSucc = TRUE;

		m_szICMPData = (char*)malloc(DEF_PACKET_SIZE + sizeof(ICMPHeader));

		if (m_szICMPData == NULL)
		{
			m_bIsInitSucc = FALSE;
		}
	}
	else
	{
		int nLastError = GetLastError();
		printf("Error at socket(): %ld\n", WSAGetLastError());//�Լ���Ϲ���
		nLastError = WSAGetLastError();
		printf("0");
	}
}

CPing::~CPing()
{
	WSACleanup();

	if (NULL != m_szICMPData)
	{
		free(m_szICMPData);
		m_szICMPData = NULL;
	}
}

BOOL CPing::Ping(DWORD dwDestIP, PingReply *pPingReply, DWORD dwTimeout)
{
	return PingCore(dwDestIP, pPingReply, dwTimeout);
}

BOOL CPing::Ping(const char *szDestIP, PingReply *pPingReply, DWORD dwTimeout)
{
	if (NULL != szDestIP)
	{
		return PingCore(inet_addr(szDestIP), pPingReply, dwTimeout);
	}
	return FALSE;
}

BOOL CPing::PingCore(DWORD dwDestIP, PingReply *pPingReply, DWORD dwTimeout)
{
	//�жϳ�ʼ���Ƿ�ɹ�
	if (!m_bIsInitSucc)
	{
		return FALSE;
	}

	//����SOCKET
	sockaddr_in sockaddrDest;
	sockaddrDest.sin_family = AF_INET;
	sockaddrDest.sin_addr.s_addr = dwDestIP;
	int nSockaddrDestSize = sizeof(sockaddrDest);

	//����ICMP��
	int nICMPDataSize = DEF_PACKET_SIZE + sizeof(ICMPHeader);
	ULONG ulSendTimestamp = GetTickCountCalibrate();
	USHORT usSeq = ++s_usPacketSeq;
	memset(m_szICMPData, 0, nICMPDataSize);
	ICMPHeader *pICMPHeader = (ICMPHeader*)m_szICMPData;
	pICMPHeader->m_byType = ECHO_REQUEST;
	pICMPHeader->m_byCode = 0;
	pICMPHeader->m_usID = m_usCurrentProcID;
	pICMPHeader->m_usSeq = usSeq;
	pICMPHeader->m_ulTimeStamp = ulSendTimestamp;
	pICMPHeader->m_usChecksum = CalCheckSum((USHORT*)m_szICMPData, nICMPDataSize);

	//����ICMP����
	if (sendto(m_sockRaw, m_szICMPData, nICMPDataSize, 0, (struct sockaddr*)&sockaddrDest, nSockaddrDestSize) == SOCKET_ERROR)
	{
		return FALSE;
	}

	//�ж��Ƿ���Ҫ������Ӧ����
	if (pPingReply == NULL)
	{
		return TRUE;
	}

	char recvbuf[256] = { "\0" };
	while (TRUE)
	{
		//������Ӧ����
		if (WSAWaitForMultipleEvents(1, &m_event, FALSE, 100, FALSE) != WSA_WAIT_TIMEOUT)
		{
			WSANETWORKEVENTS netEvent;
			WSAEnumNetworkEvents(m_sockRaw, m_event, &netEvent);

			if (netEvent.lNetworkEvents & FD_READ)
			{
				ULONG nRecvTimestamp = GetTickCountCalibrate();
				int nPacketSize = recvfrom(m_sockRaw, recvbuf, 256, 0, (struct sockaddr*)&sockaddrDest, &nSockaddrDestSize);
				if (nPacketSize != SOCKET_ERROR)
				{
					IPHeader *pIPHeader = (IPHeader*)recvbuf;
					USHORT usIPHeaderLen = (USHORT)((pIPHeader->m_byVerHLen & 0x0f) * 4);
					ICMPHeader *pICMPHeader = (ICMPHeader*)(recvbuf + usIPHeaderLen);

					if (pICMPHeader->m_usID == m_usCurrentProcID //�ǵ�ǰ���̷����ı���
						&& pICMPHeader->m_byType == ECHO_REPLY //��ICMP��Ӧ����
						&& pICMPHeader->m_usSeq == usSeq //�Ǳ��������ĵ���Ӧ����
						)
					{
						pPingReply->m_usSeq = usSeq;
						pPingReply->m_dwRoundTripTime = nRecvTimestamp - pICMPHeader->m_ulTimeStamp;
						pPingReply->m_dwBytes = nPacketSize - usIPHeaderLen - sizeof(ICMPHeader);
						pPingReply->m_dwTTL = pIPHeader->m_byTTL;
						return TRUE;
					}
				}
			}
		}
		//��ʱ
		if (GetTickCountCalibrate() - ulSendTimestamp >= dwTimeout)
		{
			return FALSE;
		}
	}
}

USHORT CPing::CalCheckSum(USHORT *pBuffer, int nSize)
{
	unsigned long ulCheckSum = 0;
	while (nSize > 1)
	{
		ulCheckSum += *pBuffer++;
		nSize -= sizeof(USHORT);
	}
	if (nSize)
	{
		ulCheckSum += *(UCHAR*)pBuffer;
	}

	ulCheckSum = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
	ulCheckSum += (ulCheckSum >> 16);

	return (USHORT)(~ulCheckSum);
}

ULONG CPing::GetTickCountCalibrate()
{
	static ULONG s_ulFirstCallTick = 0;
	static LONGLONG s_ullFirstCallTickMS = 0;

	SYSTEMTIME systemtime;
	FILETIME filetime;
	GetLocalTime(&systemtime);
	SystemTimeToFileTime(&systemtime, &filetime);
	LARGE_INTEGER liCurrentTime;
	liCurrentTime.HighPart = filetime.dwHighDateTime;
	liCurrentTime.LowPart = filetime.dwLowDateTime;
	LONGLONG llCurrentTimeMS = liCurrentTime.QuadPart / 10000;

	if (s_ulFirstCallTick == 0)
	{
		s_ulFirstCallTick = GetTickCount();
	}
	if (s_ullFirstCallTickMS == 0)
	{
		s_ullFirstCallTickMS = llCurrentTimeMS;
	}

	return s_ulFirstCallTick + (ULONG)(llCurrentTimeMS - s_ullFirstCallTickMS);
}
#else

CPing::CPing() {
	m_maxPacketSize = 4;
	m_datalen = 56;
	m_nsend = 0;
	m_nreceived = 0;
	m_icmp_seq = 0;
}

/*У����㷨*/
unsigned short CPing::getChksum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

	/*��ICMP��ͷ������������2�ֽ�Ϊ��λ�ۼ�����*/
	while (nleft>1)
	{
		sum += *w++;
		nleft -= 2;
	}
	/*��ICMP��ͷΪ�������ֽڣ���ʣ�����һ�ֽڡ������һ���ֽ���Ϊһ��2�ֽ����ݵĸ��ֽڣ����2�ֽ����ݵĵ��ֽ�Ϊ0�������ۼ�*/
	if (nleft == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

/*����ICMP��ͷ*/
int CPing::packIcmp(int pack_no, struct icmp* icmp)
{
	int i, packsize;
	struct icmp *picmp;
	struct timeval *tval;

	picmp = icmp;
	picmp->icmp_type = ICMP_ECHO;
	picmp->icmp_code = 0;
	picmp->icmp_cksum = 0;
	picmp->icmp_seq = pack_no;
	picmp->icmp_id = m_pid;
	packsize = 8 + m_datalen;
	tval = (struct timeval *)icmp->icmp_data;
	gettimeofday(tval, NULL);    /*��¼����ʱ��*/
	picmp->icmp_cksum = getChksum((unsigned short *)icmp, packsize); /*У���㷨*/
	return packsize;
}

/*��ȥICMP��ͷ*/
bool CPing::unpackIcmp(char *buf, int len, struct IcmpEchoReply *icmpEchoReply)
{
	int i, iphdrlen;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend, tvrecv, tvresult;
	double rtt;

	ip = (struct ip *)buf;
	iphdrlen = ip->ip_hl << 2;    /*��ip��ͷ����,��ip��ͷ�ĳ��ȱ�־��4*/
	icmp = (struct icmp *)(buf + iphdrlen);  /*Խ��ip��ͷ,ָ��ICMP��ͷ*/
	len -= iphdrlen;            /*ICMP��ͷ��ICMP���ݱ����ܳ���*/
	if (len < 8)                /*С��ICMP��ͷ�����򲻺���*/
	{
		printf("ICMP packets\'s length is less than 8\n");
		return false;
	}
	/*ȷ�������յ����������ĵ�ICMP�Ļ�Ӧ*/
	if ((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == m_pid))
	{

		tvsend = (struct timeval *)icmp->icmp_data;
		gettimeofday(&tvrecv, NULL);  /*��¼����ʱ��*/
		tvresult = tvSub(tvrecv, *tvsend);  /*���պͷ��͵�ʱ���*/
		rtt = tvresult.tv_sec * 1000 + tvresult.tv_usec / 1000;  /*�Ժ���Ϊ��λ����rtt*/
		icmpEchoReply->rtt = rtt;
		icmpEchoReply->icmpSeq = icmp->icmp_seq;
		icmpEchoReply->ipTtl = ip->ip_ttl;
		icmpEchoReply->icmpLen = len;
		return true;
	}
	else {
		return false;
	}
}

/*����timeval�ṹ���*/
struct timeval CPing::tvSub(struct timeval timeval1, struct timeval timeval2)
{
	struct timeval result;
	result = timeval1;
	if (result.tv_usec < timeval2.tv_usec < 0)
	{
		--result.tv_sec;
		result.tv_usec += 1000000;
	}
	result.tv_sec -= timeval2.tv_sec;
	return result;
}

/*��������ICMP����*/
bool CPing::sendPacket()
{
	size_t packetsize;
	while (m_nsend < m_maxPacketSize)
	{
		m_nsend++;
		m_icmp_seq++;
		packetsize = packIcmp(m_icmp_seq, (struct icmp*)m_sendpacket); /*����ICMP��ͷ*/

		if (sendto(m_sockfd, m_sendpacket, packetsize, 0, (struct sockaddr *) &m_dest_addr, sizeof(m_dest_addr)) < 0)
		{
			perror("sendto error");
			continue;
		}
	}
	return true;
}

/*��������ICMP����*/
bool CPing::recvPacket(PingResult &pingResult)
{
	int len;
	extern int errno;
	struct IcmpEchoReply icmpEchoReply;
	int maxfds = m_sockfd + 1;
	int nfd = 0;
	fd_set rset;
	FD_ZERO(&rset);
	socklen_t fromlen = sizeof(m_from_addr);
	struct timeval timeout;
	timeout.tv_sec = 4;
	timeout.tv_usec = 0;

	for (int recvCount = 0; recvCount < m_maxPacketSize; recvCount++)
	{
		//printf("begin recv\n");
		FD_SET(m_sockfd, &rset);
		if ((nfd = select(maxfds, &rset, NULL, NULL, &timeout)) == -1) {
			perror("select error");
			continue;
		}
		if (nfd == 0) {
			//recv time out 
			//printf("request timeout\n");
			icmpEchoReply.isReply = false;
			pingResult.icmpEchoReplys.push_back(icmpEchoReply);
			continue;
		}
		if (FD_ISSET(m_sockfd, &rset)) {
			if ((len = recvfrom(m_sockfd, m_recvpacket, sizeof(m_recvpacket), 0, (struct sockaddr *)&m_from_addr, &fromlen)) <0)
			{
				if (errno == EINTR)
					continue;
				perror("recvfrom error");
				continue;
			}
			icmpEchoReply.fromAddr = inet_ntoa(m_from_addr.sin_addr);
			if (icmpEchoReply.fromAddr != pingResult.ip) {
				//printf("invalid address, discard\n");
				//retry again
				recvCount--;
				continue;
			}
		}
		if (unpackIcmp(m_recvpacket, len, &icmpEchoReply) == false) {
			//retry again
			recvCount--;
			continue;
		}
		icmpEchoReply.isReply = true;
		pingResult.icmpEchoReplys.push_back(icmpEchoReply);
		m_nreceived++;
	}
	return true;
}

bool CPing::getsockaddr(const char * hostOrIp, struct sockaddr_in* sockaddr) {
	struct hostent *host;
	struct sockaddr_in dest_addr;
	unsigned long inaddr = 0l;
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	/*�ж�������������ip��ַ*/
	if (inaddr = inet_addr(hostOrIp) == INADDR_NONE)
	{
		if ((host = gethostbyname(hostOrIp)) == NULL) /*��������*/
		{
			//printf("gethostbyname error:%s\n", hostOrIp);
			return false;
		}
		memcpy((char *)&dest_addr.sin_addr, host->h_addr, host->h_length);
	}
	/*��ip��ַ*/
	else if (!inet_aton(hostOrIp, &dest_addr.sin_addr)) {
		//memcpy( (char *)&dest_addr,(char *)&inaddr,host->h_length);
		//fprintf(stderr, "unknow host:%s\n", hostOrIp);
		return false;
	}
	*sockaddr = dest_addr;
	return true;
}
bool CPing::Ping(std::string host, PingResult& pingResult) {
	return Ping(host, 1, pingResult);
}

bool CPing::Ping(std::string host, int count, PingResult& pingResult) {
	struct protoent *protocol;
	int size = 50 * 1024;
	IcmpEchoReply icmpEchoReply;
	bool ret;

	m_nsend = 0;
	m_nreceived = 0;
	pingResult.icmpEchoReplys.clear();
	m_maxPacketSize = count;
	m_pid = getpid();

	pingResult.dataLen = m_datalen;

	if ((protocol = getprotobyname("icmp")) == NULL)
	{
		perror("getprotobyname");
		return false;
	}
	/*����ʹ��ICMP��ԭʼ�׽���,�����׽���ֻ��root��������*/
	if ((m_sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto))<0)
	{
		//perror("socket error");
		extern int errno;
		pingResult.error = strerror(errno);
		return false;
	}
	/*�����׽��ֽ��ջ�������50K��������ҪΪ�˼�С���ջ����������
	�Ŀ�����,��������pingһ���㲥��ַ��ಥ��ַ,������������Ӧ��*/
	setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	/*��ȡmain�Ľ���id,��������ICMP�ı�־��*/
	if (!getsockaddr(host.c_str(), &m_dest_addr)) {
		pingResult.error = "unknow host " + host;
		return false;
	}
	pingResult.ip = inet_ntoa(m_dest_addr.sin_addr);
	sendPacket();  /*��������ICMP����*/
	recvPacket(pingResult);  /*��������ICMP����*/
	pingResult.nsend = m_nsend;
	pingResult.nreceived = m_nreceived;
	close(m_sockfd);
	return true;

}

#endif