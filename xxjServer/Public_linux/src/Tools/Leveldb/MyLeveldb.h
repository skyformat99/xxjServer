/********************************************************************
    ����ʱ��:     2018/10/27  16:59:40 
    �ļ���:       MyLeveldb.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.leveldb���ݿ����
                2.
                
    ˵��:        1. 
                2. 
*********************************************************************/

#pragma once
#include "../MySingleton.h"
#include <cassert>
#include <leveldb/db.h>
class CMyLeveldb:public MySingleton<CMyLeveldb>
{
public:
	virtual void OnInit() {}

	//��ʼ�����ݿ�
	bool OnInit(const std::string & dbname);

	//���һ������(�Զ�����)
	bool OnAdd(const std::string & key, const std::string & v);

	//��ȡһ������
	bool OnGet(const std::string & key, std::string & v);

	//ɾ��һ������
	bool OnDelete(const std::string & key);


	~CMyLeveldb();
private:
	bool m_isInit = false;
	leveldb::DB * m_db = nullptr;
};