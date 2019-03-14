/********************************************************************
	����ʱ�䣺	2015/04/25  0:49:21
	�ļ�����	ServerApp.h
	���ߣ�		лС��
	
	���ܣ�		1.asio������ 
				2.���ڽ������� �� ������ʼ����
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef __SERVERAPP_H_
#define __SERVERAPP_H_

#include "../MyClient.h"

class CserverApp
{
	typedef boost::shared_ptr<CMyClient> Session_ptr;
public:
	CserverApp(boost::asio::io_service& ioservice, boost::asio::ip::tcp::endpoint& endpoint);
	~CserverApp();
public:
	void OnAccept();//�ȴ�����
	void Handle_accept(const boost::system::error_code& error, Session_ptr& session);
private:
	boost::asio::io_service& m_ioservice;
	boost::asio::ip::tcp::acceptor acceptor_;
};

#endif // !__SERVERAPP_H_
