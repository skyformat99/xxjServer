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

generic <typename T> where T : gcnew()
ref class MySingleton
{
public:
	static T Instance()
	{
		return instance;
	}
protected:
	MySingleton()
	{
		assert(false&&"not allowed init from base config");//��������
	};
	~MySingleton(){ };
private:
	static T instance = gcnew T;
	
};

/*
//���� ��̬����
#define DECLARE_SINGLETON_MEMBER(_Ty)\
	template <> boost::shared_ptr<_Ty> MySingleton<_Ty>::_instance;
*/


#endif