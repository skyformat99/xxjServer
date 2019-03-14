/********************************************************************
    ����ʱ��:     2017/04/19  20:07:40 
    �ļ���:       TimeOut.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.��ʱ�ص�
                2.��λΪ��
                
    ˵��:        1. 
                2. 
*********************************************************************/
#ifndef _TIME_OUT_H_
#define _TIME_OUT_H_
#include "../DefineBase.h"

class CTimeOut
{
public:
	void SetTimeOut(MY_UINT32);
public:
	//�δ�ʱ��ص�
	virtual void OnTimeCallBack() final;

	//��ʱ֮��Ĵ�����
	virtual void OnTimeOut() = 0;
private:
	bool m_isInit = false;
	MY_UINT32 m_TimeOut = 0 ;
	MY_UINT32 m_nowTick = 0;
};

#endif // !_TIME_OUT_H_
