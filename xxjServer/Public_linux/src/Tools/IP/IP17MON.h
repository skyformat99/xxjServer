/********************************************************************
����ʱ�䣺    2016/03/24  20:48:44
�ļ�����      IP17MON.h
���ߣ�        лС��

���ܣ�        1.��Ҫ���ڽ���ip��ַ
			 2.

˵����        1.�������ص�ַ��http://www.ipip.net/download.html
2.

*********************************************************************/
#ifndef __IP17MON_H_
#define __IP17MON_H_
#include <string>
#include <vector>
typedef struct tapIpInfo{
	std::string Country;//����
	std::string Region;//���� 
	std::string City; //����
	std::string SrcIp;  //ip��Ϣ
}IpInfo;

class CMyIpMon
{
public:
	CMyIpMon();
	~CMyIpMon();

private:
public:
	bool init(const std::string strPathToDataFile = "./17monipdb.dat");
	IpInfo find(const std::string & strIP);
private:
	std::vector<char> vecDataFile;
	char *pIPIndex, *pIPData;
};

#endif // !__IP17MON_H_
