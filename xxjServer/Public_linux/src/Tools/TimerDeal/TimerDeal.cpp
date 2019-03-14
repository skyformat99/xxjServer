#include "TimerDeal.h"
#include <boost/bind.hpp>
#ifdef _WIN32
#include <windows.h>
#else
#endif

//#include "../../data/MyIni.h"
//#include "../../data/OnDo.h"

void CTimerDeal::OnStart()
{
// 	//���Ĭ�ϻص�
//  	AddOneCall(boost::bind(&ConTimeCallBack::OnTimerCallBack, ConTimeCallBack::instance()));
//  	AddOneCall(boost::bind(&ConTimeCallBack::OnTimerCall, ConTimeCallBack::instance()));//����ʱ��
 	m_thread = boost::thread(boost::bind(&CTimerDeal::ThreadRun,this));
 	boost::thread::native_handle_type type = m_thread.native_handle();
#ifdef _WIN32
	::SetThreadPriority(type, THREAD_PRIORITY_TIME_CRITICAL);//������ȼ�
#else
#endif
	
	m_thread.yield();
}

void CTimerDeal::OnStop()
{
	if (m_dt)
	{
		m_dt->cancel();
	}
	m_io.stop();
	//m_thread.join(); 
}

void CTimerDeal::OnCall(const boost::system::error_code& e,  boost::asio::deadline_timer& t)
{
	if (!e)
	{
		if (t.expires_at() <= boost::asio::deadline_timer::traits_type::now())
		{
// 			if(IGameBase::isLog)
// 				std::cout<<"OnCall\n";

			m_singnalTrivial.call();//��ʼִ�г�ʱ�ص�

			//������һ��ʱ�� ��ʼ
			t.expires_from_now(boost::posix_time::seconds(1));  
			t.async_wait(boost::bind(&CTimerDeal::OnCall,this,boost::asio::placeholders::error,boost::ref(t))); 
		}
	}
	else
	{
// 		if (CMyIni::instance()->m_isLog)
// 			std::cout<<"cancel!!\n";
	}

}

void CTimerDeal::AddOneCall( SignalTrivial::Functor func )
{
	m_singnalTrivial.connect(func);
}

void CTimerDeal::OnClear()
{
	m_singnalTrivial.Clear();
}

void CTimerDeal::ThreadRun()
{  
	boost::asio::deadline_timer dt(m_io, boost::posix_time::seconds(1)); 
	m_dt = &dt;
	dt.async_wait(boost::bind(&CTimerDeal::OnCall,this,boost::asio::placeholders::error,boost::ref(dt)));  
	m_io.run();
}

