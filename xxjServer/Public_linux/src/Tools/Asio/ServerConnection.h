/********************************************************************
	����ʱ�䣺	2014/08/07  10:58:17 
	�ļ�����    ServerConnection
	���ߣ�		лС��
	
	���ܣ�		1.ͨ�Žӿ���
				2.ֻ�����¼ʱ����ʱ������ߵ�
				
	˵����	    1. �����������ӵĿͻ���������Ϣ
				2. 
*********************************************************************/
#ifndef _SERVERCONNECTION1_H_
#define _SERVERCONNECTION1_H_
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>
#include "DefineBase.h"
#include "../MySingleton.h"
#include "ClientSession.h"




//ͨ�Žӿ�
class CServerConnectionData:public MySingleton<CServerConnectionData>
{
public:
	typedef boost::shared_ptr<ClientSession> Session_ptr;
	CServerConnectionData():m_verConnection(new std::vector<Session_ptr>),m_timeDida(0){}
	~CServerConnectionData();
public:	
	boost::mutex m_mutex;
	boost::shared_ptr<std::vector<Session_ptr> > m_verConnection;
	void AddOneConnection(const Session_ptr & _ptr);
	bool DeleteOneConnection(const Session_ptr & _ptr);
	bool DeleteOneNoSoket(Session_ptr & _ptr);//ɾ��һ�����棬���ǲ�ɾ��socket
	//void SendAllMessage(const std::string strMsg);//������Ϣ
public:
	//ִ�лص��¼�
	void OnTimerCallBack();//�����̳߳���
	MY_UINT32 m_timeDida;//ʱ��ص�
};

#endif