/********************************************************************
	����ʱ�䣺	2015/05/17  22:37:13
	�ļ�����		SQLDefine.h
	���ߣ�		xxj
	
	���ܣ�		1. ��������
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef __SQLDEFINE_H_
#define __SQLDEFINE_H_
#include <string>

class DBDataBuf : public std::streambuf
{
public:
	DBDataBuf(char * d, size_t s) {
		setg(d, d, d + s);
	}
};

// typedef struct tagDatabaseInfo
// {
// 	std::string name;
// 	std::string host;
// 	std::string user;
// 	std::string password;
// 	std::string port;
// }DatabaseInfo;

// #define  __SQLLITE  //SQLite���ݿ��迪��˺�
// #define  __MYSQL	//MySql��Ҫ�����˺�
// #define  __ODBC		//ODBC��Ҫ�����˺�


#endif