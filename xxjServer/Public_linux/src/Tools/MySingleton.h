/********************************************************************
	����ʱ�䣺	2014/08/07  11:35:23 
	�ļ�����    	MySingleton.h
	���ߣ�		лС��
	
	���ܣ�		1.
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef MYSINGLETION_H_
#define MYSINGLETION_H_
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/once.hpp>

template <class T>
class MySingleton : boost::noncopyable
{
public:
	//��ȡ���Ψһʵ��
	static inline boost::shared_ptr<T> instance()
	{
		boost::call_once(&MySingleton::Init, _once);

		return _instance;
	}

	static void Init()
	{
		//if (CMyIni::isLog)
		//	std::cout<<"Init()\n";
		_isNew = true;
		_instance = boost::shared_ptr<T>(new T);
		_isNew = false;
		_instance->OnInit();
	}

	//ȫ�ֳ�ʼ��Ψһʵ��
	virtual void OnInit() {}

	//�ͷ����Ψһʵ��
	static void destroy()
	{
		if (!_instance)
			return;

		_instance.reset();
	}
protected:
	MySingleton()
	{
		if (!_isNew)
			assert(false&&"not allowed init from base config");//��������
	};
	~MySingleton(){ destroy(); };

	static boost::shared_ptr<T> _instance;
	static boost::once_flag _once;
	static bool _isNew;
	
};

template <class T>
bool MySingleton<T>::_isNew = false;

template<typename T>
boost::once_flag MySingleton<T>::_once = BOOST_ONCE_INIT;
template<typename T>
boost::shared_ptr<T> MySingleton<T>::_instance;

/*
//���� ��̬����
#define DECLARE_SINGLETON_MEMBER(_Ty)\
	template <> boost::shared_ptr<_Ty> MySingleton<_Ty>::_instance;
*/


#endif