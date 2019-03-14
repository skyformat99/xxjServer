/********************************************************************
    ����ʱ�䣺    2015/08/06  14:52:15 
    �ļ�����      SignalSlotTrivial.h
    ���ߣ�        xxj
    
    ����:		1.�źŲ�
				2.�����¼��ص�
                
    ˵��:		1. 
                2. 
*********************************************************************/
#ifndef SIGNALSLOTTRIVIAL_H_
#define SIGNALSLOTTRIVIAL_H_
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <memory>
#include <vector>
#include <boost/function.hpp>

// template<typename Signature>
// class SignalTrivial;

class SignalTrivial: boost::noncopyable
{
 public:
  typedef boost::function<void ()> Functor;

  //���һ��
  void connect(Functor& func)
  {
    functors_.push_back(func);
  }

  void call()
  {
	//ע�⣺���̰߳�ȫ�� ��Ҫ�ɸ��ԵĻص����ư�ȫ��
    std::vector<Functor>::iterator it = functors_.begin();
    for (; it != functors_.end(); ++it)
    {
      (*it)();
    }
  }

  void Clear()
  {
	  functors_.clear();
  }

 private:
	std::vector<Functor> functors_;
};

#endif 
