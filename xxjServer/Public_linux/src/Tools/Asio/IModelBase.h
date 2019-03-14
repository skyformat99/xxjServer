/********************************************************************
	����ʱ�䣺	2014/08/07  10:58:17 
	�ļ�����    	IGameBase
	���ߣ�		лС��
	
	���ܣ�		1.ģ����Ϣ��ӿ� ��Ҫ�����߼�����
				2.
				
	˵����	    1. �����߼��ӿڶ���
				2. 
*********************************************************************/
#ifndef _IMODELBASE_H_
#define _IMODELBASE_H_
#include <string>
#include <vector>
#include "GameDefine.h"

//�߼��ӿ�
class IModelBase
{
public:
	bool m_isInit;
	bool m_isDelete;

//	UserInfo m_user;
// 	MY_UINT32 m_userID;
// 	std::string m_name;

	IModelBase(){m_isInit = false;m_isDelete = false;}

public:
	//����
	virtual void OnInit() = 0;

	//�ж��Ƿ�ʱ��
	virtual bool OnTimeOut() = 0;

};

#endif