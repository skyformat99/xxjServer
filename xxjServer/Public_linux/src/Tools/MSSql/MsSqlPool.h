/********************************************************************
����ʱ�䣺    2016/06/05  07:05:44
�ļ�����      ConnectionPool.h
���ߣ�        лС��

���ܣ�        1. ���ݿ����ӳ�
2.

˵����        1. �������ݿ����ӹ���
2.
*********************************************************************/
#ifndef MSSQLCONN_POLL_H
#define MSSQLCONN_POLL_H
#include "../MySingleton.h"
#include "../Queue/MyQueue.h"
#include "MsSqlBase.h"
#include <string>
#include <xutility>


class MsSqlConnPool :public MySingleton<MsSqlConnPool>
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
	db_timeout:���ӳس�ʱʱ��
	*/
	bool ConnectionMySql(const std::string& host, const std::string& port, const std::string & Database, const std::string& user,
		const std::string &PWD, int minSession = 1, int maxSession = 2, std::size_t timeout = 60U, std::size_t db_timeout = 0U);

	//����һ��
	void OnReleaseOne(_ConnectionPtr con,unsigned int creatTime);

	//��ȡһ��
	ConnectionMS GetConnection(); //������ݿ�����
public:
	MsSqlConnPool(){};
	~MsSqlConnPool();

private:
	bool m_isInit = false;
	CMyQueue<ConnectionMS> m_queue;
	void OnDestroy(_ConnectionPtr & px);
private:
	DatabaseInfo db_info;
	int minSession = 0;
	int maxSession = 0;
	std::size_t timeout = 60U; /*= 60U*/
	std::size_t db_timeOut = 0U;
};



class CMsConnectionEx :public CMSsqlBase, public CPointBase<CMsConnectionEx>, public boost::noncopyable
{
public:
	CMsResultSet executeQuery(const std::string & sql);
public:
	CMsConnectionEx(ConnectionMS & info)
	{
		px_back = info.con;
		m_creatTime = info.m_creatTime;
		px = this;
	}

	//��ֹsql ע��
	// 	sql::SQLString EscapeString(const sql::SQLString & src){
	// 		return src;
	// 		sql::mysql::MySQL_Connection * myConn = dynamic_cast<sql::mysql::MySQL_Connection *> (px);
	// 		return myConn->escapeString(src);
	// 	}

	~CMsConnectionEx()
	{
		OnRelease();
	}

	void OnDestroy()
	{
		if (px_back)
		{
			CMsSqlConnection::instance()->ReleaseConnection(px_back);
			px = nullptr;
		}
	}

	//�������ݿ�����
	void OnRelease()
	{
		MsSqlConnPool::instance()->OnReleaseOne(px_back, m_creatTime);
	}


private:
	unsigned int m_creatTime = 0;
	_ConnectionPtr px_back = nullptr;
};

#endif

