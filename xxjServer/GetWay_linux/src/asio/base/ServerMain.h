/********************************************************************
    ����ʱ�䣺    2015/08/10  10:40:08 
    �ļ�����      ServerRoot.h
    ���ߣ�        xxj
    
    ����:		1.����������ģ��
				2.
                
    ˵��:		1. asio ����ģ��
                2. 
*********************************************************************/
#ifndef __SERVER_MAIN_H_
#define __SERVER_MAIN_H_
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/noncopyable.hpp>
#include <Tools/MySingleton.h>

class CServerMain:public MySingleton<CServerMain>
{
public:
	void OnStart();
	void OnStop();
private:
	void StartServer(std::string ip, unsigned short port);
	boost::asio::io_service m_ioService;
	boost::thread m_mainThrd;//���߳�

};

#endif