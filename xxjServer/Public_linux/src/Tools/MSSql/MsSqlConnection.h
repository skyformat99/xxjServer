/********************************************************************
    ����ʱ�䣺    2015/09/23  9:34:18 
    �ļ�����        CMsSqlConnection.h
    ���ߣ�        лС��
    
    ���ܣ�       1.����MySql���ݿ�����ʹ��
                2.
                
    ˵����       1. 
                2. 
*********************************************************************/
#ifndef __MSSQLCONNECTION_H_
#define __MSSQLCONNECTION_H_

#include <winsock2.h>
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "adoEOF"), rename("BOF", "adoBOF")
#include "..\MySingleton.h"
#include "..\MySql\SQLDefine.h"
#include "MsSqlBase.h"


class CMsSqlConnection :public MySingleton<CMsSqlConnection>
{
public:
	_ConnectionPtr GetConnection(const DatabaseInfo & dbInfo);
	void ReleaseConnection(_ConnectionPtr & conn);
	CMsSqlConnection();
	~CMsSqlConnection();
private:
	void DestroyConnection(_ConnectionPtr & conn);
	std::string OnGetConnectionStr(const DatabaseInfo & dbinfo);//��ȡ�����ַ���
	

};


#endif // !CMySqlConnection_H_