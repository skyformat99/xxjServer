
/********************************************************************
    ����ʱ�䣺    2015/11/02  15:05:44 
    �ļ�����      ConnectionPool.h
    ���ߣ�        лС��
    
    ���ܣ�        1. ���ݿ����ӳ�
                 2.
                
    ˵����        1. �������ݿ����ӹ���
                 2. 
*********************************************************************/
#ifndef __CONNECTIONPOOL_H_
#define __CONNECTIONPOOL_H_

#define  __MYSQL	//MySql��Ҫ�����˺�
//#define  __ODBC		//ODBC��Ҫ�����˺�

#include "MyIni.h"
#include <map>
#include <boost/thread.hpp>

#include <Tools/MyTimes.h>
class ConnectionPool :public MySingleton < ConnectionPool >
{
public:
	ConnectionPool();
	~ConnectionPool();
	/*
		��ʼһ���¼�:
		info:ormֵ
		json:����
	*/
	std::string OnDo(const SqlInfo & info, const CMyJson::JsonRoot & json = CMyJson::JsonRoot());

private:
	void Init();
private:
	std::string BuildSql(const std::vector<std::string> & sql, const std::vector<SqlPutInfo> & verInput, const CMyJson::JsonRoot & json);
	std::string GetSql(const SqlPutInfo & info, const CMyJson::JsonRoot & json);
};
#endif


