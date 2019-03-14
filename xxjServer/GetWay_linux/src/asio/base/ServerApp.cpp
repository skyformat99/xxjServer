#include "ServerApp.h"




CserverApp::CserverApp(boost::asio::io_service& ioservice, boost::asio::ip::tcp::endpoint& endpoint)
:m_ioservice(ioservice)
,acceptor_(ioservice, endpoint,false)//false ���ö˿ڲ��ɸ���
{
	std::cout<<"strat!"<<std::endl;
	std::cout<<"listen [ip:port]:"<<endpoint<<std::endl;

	OnAccept();
}

CserverApp::~CserverApp()
{

}

void CserverApp::Handle_accept(const boost::system::error_code& error, Session_ptr& session)
{
	if (!error)
	{
		if (!m_ioservice.stopped())
		{
			session->OnConnect();//֪ͨ����
			session->Start();//ʵ�ֶ�ÿ���ͻ��˵����ݴ���
			CServerConnectionData::instance()->AddOneConnection(session);

			OnAccept();
		}
	}
	else
	{
		session->DisConnect();
	}
}

void CserverApp::OnAccept()
{
	//ÿһ��session����һ���ͻ���
	if (!m_ioservice.stopped())
	{
		Session_ptr new_session(new CMyClient(m_ioservice));
		acceptor_.async_accept(new_session->Socket(),
			boost::bind(&CserverApp::Handle_accept, this, boost::asio::placeholders::error,
			new_session));
	}
}


