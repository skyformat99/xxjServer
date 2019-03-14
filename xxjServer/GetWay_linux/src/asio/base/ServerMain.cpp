#include "ServerMain.h"
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/foreach.hpp>
#include "ServerApp.h"
#include <Tools/MyTools.h>
#include "../../data/MyIni.h"


void CServerMain::StartServer(std::string ip, unsigned short port)
{
		try
		{
			//�����õ���inet4 boost::asio::ip::tcp::v4()Ĭ�����п������� boost::asio::ip::address_v4::from_string("127.0.0.1")���ؿ�����
			//boost::asio::ip::tcp::v4() ������������
			boost::asio::ip::tcp::endpoint endPoint(
				boost::asio::ip::address_v4::from_string(ip), port);
			//�նˣ����Կ���sockaddr_in����ɺ󣬾�Ҫaccept��

			CserverApp sa(m_ioService,endPoint);//��ʼ����

			std::vector<boost::shared_ptr<boost::thread> > _listThread;//����io�߳�
			//����10����(io)�߳�
			for (int i = 0; i < MAX_IO_THREAD; ++i)
			{
				boost::shared_ptr<boost::thread> pTh(new boost::thread(
					boost::bind(&boost::asio::io_service::run,&m_ioService)));
				_listThread.push_back(pTh);
			}

			m_ioService.run();//�����շ��߼�

			//���������߳�
			BOOST_FOREACH(const boost::shared_ptr<boost::thread> & it,_listThread)
			{
				it->join();//�ȴ��߳̽���
			}
		}
		catch (std::exception & e)
		{
			std::vector<std::string> ver;
			ver.push_back(boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) +"\t"+e.what());
			MyTools::PrintToFile("MsgLog/error.txt",ver,false);
			std::cout << "error��" <<e.what()<< std::endl;//���������
		}
} 

void CServerMain::OnStop()
{
	//CClientList::instance()->OnStop();

	m_ioService.stop();//ֹͣ
	m_mainThrd.join();
	//CClientList::instance()->OnClear();
}

void CServerMain::OnStart()
{
	m_mainThrd = boost::thread(boost::bind(&CServerMain::StartServer, this,
		CMyIni::instance()->m_serverIP,
		CMyIni::instance()->m_serverPort));//������ͻ��������߳�
	m_mainThrd.yield();//�Զ�����

	//CClientList::instance()->OnStart();
}

