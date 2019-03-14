/********************************************************************
    ����ʱ�䣺    2015/08/08  16:22:27 
    �ļ�����      GameDefine.h
    ���ߣ�        xxj
    
    ����:		1.��Ϣ����
				2.
                
    ˵��:		1. 
                2. 
*********************************************************************/
#ifndef __GAMEDEFINE_H_
#define __GAMEDEFINE_H_
#include "../Tools/ClientTypeDefine.h"
//#using <System.dll>

#ifndef interface
#define interface class
#endif

public ref class MsgBaseHead
{
public:
	MY_UINT32 unMsgID;

	MsgBaseHead()
	{
		Clear();
	}
	void Clear()
	{
		unMsgID = 0;
	}
};

public ref class MsgInfo
{
public:
	MsgBaseHead m_head;//��Ϣͷ
	array<Byte>^ m_body;
	MY_UINT32 m_body_len;
	
	MsgInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_head.Clear();
		m_body_len = 0;
		m_body = QNEW array<Byte>(0);
	}
};
//"uID"

ref class MsgQueueInfo
{
public:
	array<Byte>^ data;
	MY_UINT32 len;
};

public enum class ENetState
{
	EConnect = 0,//���ӳɹ����
	EDesConnect,//����ʧ�ܱ��
	EWriteDown,//д���
	ERead,//������Ϣ
};

#endif
