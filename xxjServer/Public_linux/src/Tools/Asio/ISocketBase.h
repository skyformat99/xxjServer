/********************************************************************
	����ʱ�䣺	2014/08/07  10:58:17 
	�ļ�����    	IGameBase
	���ߣ�		лС��
	
	���ܣ�		1.ͨ�Žӿ���
				2.
				
	˵����	    1. MyClient.h ��ʹ��Asio ʵ�֣�����ֻ�Ƕ�����һ������
				2. 
*********************************************************************/
#ifndef IGAMEBASE_H_
#define IGAMEBASE_H_
#include <string>
#include <vector>
#include "GameDefine.h"
#include <boost/smart_ptr/scoped_array.hpp>

// #ifndef interface
// #define interface class
// #endif // !interface


//ͨ�Žӿ�
class ISocketBase
{
public:
	bool isLog = true;
public:
	//��ȡ�����ļ�
	virtual void OnRead(std::vector<MsgInfo> & ver) = 0;

	//��ȡ�����ļ�
	virtual void OnRead(std::vector<std::string> & ver) = 0;

	//�����¼�
	virtual bool OnSend(const boost::scoped_array<char> & str,MY_UINT32 len) = 0;

	//���ӳɹ�����
	virtual void OnConnect() = 0;

	//�Ͽ�
	virtual void DisConnect() = 0;

	//д���
	virtual void OnWriteDown()=0;

	//�����л�
	virtual void UnSerializing(const char * data, int size) = 0;
};

#endif