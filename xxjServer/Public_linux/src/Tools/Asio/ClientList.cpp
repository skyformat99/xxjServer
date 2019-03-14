#include "ClientList.h"

CClientList::CClientList():m_mapClient(new std::map<MY_UINT32,Session_ptr>)
{
	m_isStop = true;
}

CClientList::~CClientList()
{

}

void CClientList::AddOneClient( const Session_ptr & _ptr )
{
	//����ȫ�̳���
	boost::mutex::scoped_lock writeLock(m_mutex);//д�� �ǵݹ���(����������)
	if(!m_mapClient.unique())//���������ڶ�
	{
		m_mapClient.reset(new std::map<MY_UINT32,Session_ptr>(*m_mapClient));
	}

	//----ɾ���ϵ�
	std::map<MY_UINT32,Session_ptr>::iterator it = m_mapClient->find(_ptr->m_user.m_id);
	if (it != m_mapClient->end())
	{
		(*it).second->Socket().close();//�ر�����
		(*it).second->m_isDelete = true;
	}
	//-----------------------------------------end
	assert(m_mapClient.unique());
	(*m_mapClient)[_ptr->m_user.m_id] = _ptr;

	std::cout<<"m_mapClient:"<<m_mapClient->size()<<std::endl;
}

bool CClientList::DeleteOnClient( Session_ptr & _ptr )
{
	//����ȫ�̳���
	boost::mutex::scoped_lock writeLock(m_mutex);//д�� �ǵݹ���(����������)
	if(!m_mapClient.unique())//���������ڶ�
	{
		m_mapClient.reset(new std::map<MY_UINT32,Session_ptr>(*m_mapClient));
	}
	assert(m_mapClient.unique());

	std::map<MY_UINT32,Session_ptr>::iterator it = m_mapClient->find(_ptr->m_user.m_id);
	if (it != m_mapClient->end())
	{
		(*it).second->Socket().close();//�ر�����
		(*it).second->m_isDelete = true;
		m_mapClient->erase(it);
		return true;
	}
	else
		return false;
}

void CClientList::SendMsgToBroadcast( const MsgInfo & info )
{
	m_broadcastQue.Enqueue(info);
	//��֯����
// 	CMyJson::JsonRoot json = m_myJsonOp.CreatJson(MSG_SEND_ALL_MSG_ID);
// 	m_myJsonOp.AddValue(json,"uID",info.m_user.m_id);
// 	m_myJsonOp.AddValue(json,"name",info.m_user.m_name);
// 	m_myJsonOp.AddValue(json,"text",info.text);
// 	std::string strMsg = m_myJsonOp.GetJsonStr(json);
// 	CMyAsioTools tools;
// 	std::string  strSend= tools.Serializing(strMsg);
// 
// 	boost::shared_ptr<std::map<MY_UINT32,Session_ptr> > temp;
// 	{
// 		boost::mutex::scoped_lock writeLock(m_mutex);//д�� �ǵݹ���(����������)
// 		temp = m_mapClient;
// 		assert(!m_mapClient.unique());
// 	}
// 
// 	//��������
// 	std::map<MY_UINT32,Session_ptr>::iterator c_it = temp->begin();
// 	while(c_it != temp->end())
// 	{
// 		c_it->second->OnSend(strSend);//������Ϣ
// 		c_it++;
// 	}
// 
// 	
// 	std::cout<<"send total:"<<temp->size()<<std::endl;
}

void CClientList::SendMsgToOne( const MsgInfo & info )
{
	m_oneQue.Enqueue(info);
	//��֯����
// 	CMyJson::JsonRoot json = m_myJsonOp.CreatJson(MSG_SEND_TO_MSG_ID);
// 	m_myJsonOp.AddValue(json,"uID",info.m_user.m_id);
// 	m_myJsonOp.AddValue(json,"name",info.m_user.m_name);
// 	m_myJsonOp.AddValue(json,"text",info.text);
// 	std::string strMsg = m_myJsonOp.GetJsonStr(json);
// 	CMyAsioTools tools;
// 	std::string  strSend= tools.Serializing(strMsg);
// 	//
// 
// 	boost::shared_ptr<std::map<MY_UINT32,Session_ptr> > temp;
// 	{
// 		boost::mutex::scoped_lock writeLock(m_mutex);//д�� �ǵݹ���(����������)
// 		temp = m_mapClient;
// 		assert(!m_mapClient.unique());
// 	}
// 
// 	//��������
// 	std::map<MY_UINT32,Session_ptr>::iterator c_it = temp->find(info.toID);
// 	if (c_it != temp->end())
// 	{
// 		c_it->second->OnSend(strSend);
// 	}

}

void CClientList::OnStartBroadcast()
{
	std::vector<MsgInfo> ver;
	CMyAsioTools tools;
	boost::scoped_array<char> _buffer;
	MY_UINT32 size = 0;
	std::string strSend;
	while(!m_isStop)
	{
		strSend.clear();
		ver.clear();
		m_broadcastQue.Dequeue(ver);//ȡ��һ������

		boost::shared_ptr<std::map<MY_UINT32,Session_ptr> > temp;
		{
			boost::mutex::scoped_lock writeLock(m_mutex);//д�� �ǵݹ���(����������)
			temp = m_mapClient;
			assert(!m_mapClient.unique());
		}


		for (size_t i=0;i<ver.size();i++)
		{
			boost::scoped_array<char> _temp;
			MY_UINT32 len = tools.Serializing(ver.at(i),_temp);

			//��������
			std::map<MY_UINT32,Session_ptr>::iterator c_it = temp->begin();
			while(c_it != temp->end())
			{
				c_it->second->OnSend(_temp,len);//������Ϣ
				c_it++;
			}
		}

		//std::cout<<"send total:"<<temp->size()<<std::endl;
	}
}

void CClientList::OnStartOne()
{
	CMyAsioTools tools;
	while(!m_isStop)
	{
		MsgInfo info = m_oneQue.Dequeue();

		boost::scoped_array<char> _temp;
		MY_UINT32 len = tools.Serializing(info,_temp);
		//

		boost::shared_ptr<std::map<MY_UINT32,Session_ptr> > temp;
		{
			boost::mutex::scoped_lock writeLock(m_mutex);//д�� �ǵݹ���(����������)
			temp = m_mapClient;
			assert(!m_mapClient.unique());
		}

		//����������
		std::map<MY_UINT32,Session_ptr>::iterator c_it = temp->find(info.toID);
		if (c_it != temp->end())
		{
			c_it->second->OnSend(_temp,len);
		}

		//����������
		c_it = temp->find(info.m_user.m_id);
		if (c_it != temp->end())
		{
			c_it->second->OnSend(_temp,len);
		}


	}
}

void CClientList::OnStart()
{
	m_isStop = false;

	m_broadcastThrd = boost::thread(boost::bind(&CClientList::OnStartBroadcast,this));//������ͻ��������߳�
	m_broadcastThrd.yield();//�Զ�����

	m_oneThrd = boost::thread(boost::bind(&CClientList::OnStartOne,this));//������ͻ��������߳�
	m_oneThrd.yield();//�Զ�����
}

void CClientList::OnStop()
{
	m_isStop = true;

	m_broadcastThrd.interrupt();//�ж�
	m_oneThrd.interrupt();//�ж�
	m_broadcastThrd.join();
	m_oneThrd.join();
}

void CClientList::OnClear()
{
	//��������
	std::map<MY_UINT32,Session_ptr>::iterator c_it = m_mapClient->begin();
	while(c_it != m_mapClient->end())
	{
		(*c_it).second->CloseSocket();//�ر�����
		(*c_it).second->m_isDelete = true;
		c_it++;
	}

	m_mapClient->clear();
}



