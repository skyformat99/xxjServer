/********************************************************************
	����ʱ�䣺	2015/04/25  0:37:22
	�ļ�����	MyClient.h
	���ߣ�		лС��
	
	���ܣ�		1. ��Ҫ�߼��࣬�����ﴦ�����о�����Ϣ
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef __MYCLIENT_H_
#define __MYCLIENT_H_

#include <Tools/Asio/ClientSession.h>
#include <Tools/Json/MyJson.h>
#include <Tools/Asio/IAsioTools.h>
#include <Tools/Asio/ServerConnection.h>


class CMyClient:public ClientSession
{
public:
	CMyClient(boost::asio::io_service & ioservice);
	~CMyClient();
public://IGameBase �ӿ�
	//��ȡ�����ļ�
	virtual void OnRead(std::vector<MsgInfo> & ver);

	//��ȡ�����ļ�
	virtual void OnRead(std::vector<std::string> & ver);

	//�����¼�
	virtual bool OnSend(const boost::scoped_array<char> & str,MY_UINT32 len);

	//д���
	virtual void OnWriteDown();

	//���ӳɹ�����
	virtual void OnConnect();
	//�Ͽ�
	virtual void DisConnect();

	//�����л�
	virtual void UnSerializing(const char * data, int size);
private://���л����
	MY_UINT32 m_loginTime = 0;
	std::vector<std::string> m_verMsg;
	boost::shared_ptr<IAsioTools> m_myAsioTools = nullptr;
	void WriteResult(const std::string & str);//���Ͳ��������Ϣ

public://IModelBase�ӿ�
	virtual void OnInit();
	virtual bool OnTimeOut();
public://������Ϣ
	bool DealMsg(MsgInfo & Msg);//��Ϣ��������ʼ
	void OnDealMessage(std::string str);
private:
	void OnDestroye();//�����Լ�

};

#endif // !__MYCLIENT_H_
