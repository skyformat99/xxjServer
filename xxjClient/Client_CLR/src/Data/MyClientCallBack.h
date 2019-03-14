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
#ifndef MY_CLIENTCALLBACK_H_
#define MY_CLIENTCALLBACK_H_
#include "GameDefine.h"

namespace MyClientCallBack {
	public delegate void OnVoidCallBack();//�պ������ض���
	public delegate void OnENetStateCallBack(ENetState e);//����״̬�ı�ص�

	public ref class CMyClientCallBack
	{

	public:
		//OnVoidCallBack^ theConnectCallBack = nullptr;
		OnENetStateCallBack^ theENetStateCallBack = nullptr;
	public:
		//����״̬�ı�ص�
		inline void OnSetENetStateCallBack(OnENetStateCallBack^ e) { theENetStateCallBack = e;}
		inline void OnDealENetStateCallBack(ENetState e)
		{
			if (theENetStateCallBack)
				theENetStateCallBack(e);
		}

	};
}


#endif
