/********************************************************************
����ʱ�䣺    2016/06/05  07:05:44
�ļ�����      ConnectionPool.h
���ߣ�        лС��

���ܣ�        1. ���ݿ����ӳ�
2.

˵����        1. �������ݿ����ӹ���
2.
*********************************************************************/
#ifndef MYSQLCONN_POLL_H
#define MYSQLCONN_POLL_H
#include "../MySingleton.h"
#include "../Queue/MyQueue.hpp"
#include "../MySql/MySqlConnection.h"
#include "MySqlBase.h"
#include <string>


class MySqlConnPool :public MySingleton<MySqlConnPool>
{
public:
	/*
	���ܣ�
	�������ݿ�,������session��
	����:
	host:���ݿ��ַ
	port:�˿ں�
	Database:���ݿ���
	user:�û���
	PWD:�û�����
	*/
	bool ConnectionMySql(const std::string& host, const std::string& port, const std::string & Database, const std::string& user,
		const std::string &PWD, int minSession = 1, int maxSession = 2, std::size_t timeout = 60U);

	bool ConnectionMySql(DatabaseInfo info, int minSession = 1, int maxSession = 2, std::size_t timeout = 60U);

	//����һ��
	void OnReleaseOne(sql::Connection *,unsigned int creatTime);

	//��ȡһ��
	Connection GetConnection(); //������ݿ�����
public:
	MySqlConnPool(){};
	~MySqlConnPool();

	bool m_isLoop = true;
private:
	bool m_isInit = false;
	CMyQueue<Connection> m_queue;
	void OnDestroy(sql::Connection *& px);
private:
	DatabaseInfo db_info;
	int minSession = 0;
	int maxSession = 0;
	std::size_t timeout = 60U; /*= 60U*/
};


class CMyConnectionEx :public CMysqlBase, public CPointBase<sql::Connection>, public boost::noncopyable
{
public:
	CMyConnectionEx(const Connection & info)
	{
		px = info.con;
		m_creatTime = info.m_creatTime;
	}

	//��ֹsql ע��
	sql::SQLString EscapeString(const sql::SQLString & src){
		sql::mysql::MySQL_Connection * myConn = dynamic_cast<sql::mysql::MySQL_Connection *> (px);
		return myConn->escapeString(src);
	}

	~CMyConnectionEx()
	{
		OnRelease();
	}

	void OnDestroy()
	{
		if (px)
		{
			px->commit();
			CMySqlConnection::instance()->ReleaseConnection(px);
			px = nullptr;
		}
	}

	//�������ݿ�����
	void OnRelease()
	{
		MySqlConnPool::instance()->OnReleaseOne(px, m_creatTime);
	}

	void setOutTime()
	{
		m_creatTime = CMyTimes::get_utc() - 24 * 3600;
	}
private:
	//sql::Connection * px = nullptr;
	unsigned int m_creatTime = 0;
};
#endif

