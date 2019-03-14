/********************************************************************
    ����ʱ�䣺    2015/08/06  14:56:24 
    �ļ�����      TimerDeal.h
    ���ߣ�        xxj
    
    ����:		1.��ʱ��
				2.û��ִ��һ�� ����SignalTrivial
                
    ˵��:		1. 
                2. 
*********************************************************************/
#ifndef TIMERDEAL_H_
#define TIMERDEAL_H_
#include "../MySingleton.h"
#include "../SingnalTrivial/SignalSlotTrivial.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>

class CTimerDeal:public MySingleton<CTimerDeal>
{
public:
	CTimerDeal():m_dt(NULL){}
	void OnStart();
	void OnStop();
	void AddOneCall(SignalTrivial::Functor func);
	void OnClear();
private:
	void OnCall(const boost::system::error_code& e,  boost::asio::deadline_timer & t);
	void ThreadRun() ;
	SignalTrivial m_singnalTrivial;
	boost::thread m_thread;
	boost::asio::io_service m_io;
	boost::asio::deadline_timer * m_dt;
};

#endif