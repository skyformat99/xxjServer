
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
#include "GameDefine.h"
#include "../Tools/MyQueue/MyQueue.h"


public ref class CMyClientDataModel
{
public:
	//��ʼ��
	void OnInit();
public:
	//��ȡ�����ļ�
	void OnRead(PTR(MsgInfo) ver);

	//�����¼�
	virtual bool OnSend(array<Byte>^ str, MY_UINT32 len);

	//���ӳɹ�����
	virtual void OnConnect();

	//�Ͽ�
	virtual void DisConnect();

	//д���
	virtual void OnWriteDown();

	//�����л�
	virtual void UnSerializing(const char * data, int size);


//��Ϣ���
public:
	void OnEnqueue(MsgQueueInfo^ info);
	CMyQueue<MsgQueueInfo^>^ s_myqueue;
private:

	void OnTestSend();
};
#endif
