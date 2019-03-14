/********************************************************************
    ����ʱ��:     2017/04/21  10:21:43 
    �ļ���:       MySqlite3.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.sqlite3���ݻ�����
                2.
                
    ˵��:        1. 
                2. 
*********************************************************************/
#ifndef _SQLITE3_BASE_H_
#define _SQLITE3_BASE_H_
#include <map>
#include <string>
#include <boost/thread.hpp>
#include "src/sqlite3.h"
#include "../PointBase.h"
#include "../MySingleton.h"


class Sqlite3db:public CPointBase<sqlite3>
{
public:
	explicit Sqlite3db(sqlite3 * db);
	~Sqlite3db();
	sqlite3 * Get();
public:
	void OnDestory();

};

class  Sqlite3Mgr:public MySingleton<Sqlite3Mgr>
{
public:
	bool ConnectionSqlite(const std::string & db);
	std::shared_ptr<Sqlite3db> GetConnection(const std::string & db); //��ȡһ��//������ݿ�����
	bool ReleaseConnection(const std::string & db);
protected:
	bool IsHaveBuild(const std::string & db);
	std::tuple<bool,std::shared_ptr<Sqlite3db>> BuildOneDB(const std::string &db);
private:
	boost::mutex m_oMutex;
	std::map<std::string, std::shared_ptr<Sqlite3db>> m_db_mgr;

};

#endif