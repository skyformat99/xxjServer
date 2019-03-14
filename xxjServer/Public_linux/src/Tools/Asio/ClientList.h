/********************************************************************
	����ʱ�䣺	2014/08/07  10:58:17 
	�ļ�����    ServerConnection
	���ߣ�		лС��
	
	���ܣ�		1.�û��б�
				2.�Ѿ���¼����û��б�
				
	˵����	    1. Ҫ���ȵ�¼���
				2. 
*********************************************************************/
#ifndef _CLIENTLIST_H_
#define _CLIENTLIST_H_
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <map>
#include "../MySingleton.h"
//#include "MyClient.h"
#include "../Queue/MyQueue.h"


//ͨ�Žӿ�
class CClientList:public MySingleton<CClientList>
{
public:
	typedef boost::shared_ptr<ClientSession> Session_ptr;
	CClientList();
	~CClientList();
public:	
	boost::mutex m_mutex;
	boost::shared_ptr<std::map<MY_UINT32,Session_ptr> > m_mapClient;
	void AddOneClient(const Session_ptr & _ptr);
	bool DeleteOnClient(Session_ptr & _ptr);

	void SendMsgToBroadcast(const MsgInfo & info);//������Ϣ �㲥
	void SendMsgToOne(const MsgInfo & info);//������Ϣ ˽������

	void OnStart();
	void OnStop();
	void OnClear();
protected:
	void OnStartBroadcast();
	void OnStartOne();
private:
	bool m_isStop;
	boost::thread m_broadcastThrd;//�㲥�߳�
	boost::thread m_oneThrd;//˽�������߳�
	CMyQueue<MsgInfo> m_broadcastQue;
	CMyQueue<MsgInfo> m_oneQue;

private:
	//CMyJson m_myJsonOp;
};

#endif