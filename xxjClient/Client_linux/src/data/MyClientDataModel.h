/********************************************************************
    ����ʱ��:     2017/04/07  15:03:10 
    �ļ���:       MyClientDataModel.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.������������ݽӿڵ����ݻص��ӿ�
                2.
                
    ˵��:        1. 
                2. 
*********************************************************************/
#ifndef MY_CLIENTDATAMODEL_H_
#define MY_CLIENTDATAMODEL_H_
#include <Tools/Asio/ISocketBase.h>
#include <Tools/MySingleton.h>

class CMyClientDataModel:public ISocketBase,public MySingleton<CMyClientDataModel>
{
public:
	//��ȡ�����ļ�
	virtual void OnRead(std::vector<MsgInfo> & ver);

	//��ȡ�����ļ�
	virtual void OnRead(std::vector<std::string> & ver);

	//�����¼�
	virtual bool OnSend(const boost::scoped_array<char> & str, MY_UINT32 len);

	//���ӳɹ�����
	virtual void OnConnect();

	//�Ͽ�
	virtual void DisConnect();

	//д���
	virtual void OnWriteDown();

	//�����л�
	virtual void UnSerializing(const char * data, int size);
};
#endif
