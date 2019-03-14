#ifndef __IDATABASE_IO_H_
#define __IDATABASE_IO_H_
#include <iostream>
#include <string>
#include <vector>
#include "SQLDefine.h"
#include "DatabaseIO.h"
#include <Poco\Data\Statement.h>
#include <boost/thread.hpp>
#include "../asio/DefineBase.h"
#include <Poco/Data/Session.h>
#include "traits.hpp"//������ȡ
#include <Poco/Data/SessionPool.h>
#include <memory>

class MySesion
{
public:
	MySesion(std::shared_ptr<Poco::Data::SessionPool> & sessionPtr)
	{
		Dequeue();
		m_session = std::shared_ptr<Poco::Data::Session>(new Poco::Data::Session(sessionPtr->get()));
		//��������ݿ⽨���Ự�ɹ�,���������Ϣ
		while(!m_session->isConnected())
		{
			Sleep(1000);
			m_session = std::shared_ptr<Poco::Data::Session>(new Poco::Data::Session(sessionPtr->get()));
		} 
	};
	~MySesion()
	{
		m_session->commit();
		m_session->close();
		Enqueue();
	}

public:
	std::shared_ptr<Poco::Data::Session> m_session;
private:
	void Dequeue()//���������õ�һ����Ϣ
	{
		boost::mutex::scoped_lock oLock(m_oMutex);//������
		while (m_nowSession >= m_maxSession)//����ѭ�����������ж�֮����wait()
		{
			m_cond.wait(m_oMutex);//��ԭ���Ե�unlock m_oMutex ������ȴ�
			//waitִ�����֮����Զ����ּ���
		}

		assert(m_nowSession < m_maxSession);

		++m_nowSession;
	}
	void Enqueue()//����һ��Ԫ��
	{
		{
			boost::mutex::scoped_lock oLock(m_oMutex);//������
			--m_nowSession;
		}

		m_cond.notify_one();//��ʾһ������
	}

	static boost::mutex m_oMutex;
	static boost::condition_variable_any m_cond;//��������
public:
	static MY_UINT32 m_minSession;
	static MY_UINT32 m_maxSession;
	static MY_UINT32 m_nowSession;
};

class IDataBaseObj
{
public://�������
	/*
		���ܣ�
			�������ݿ�,������session��
		����:
			connector:�������ݿ����֣�����ָ�� "SQLite" "MySQL" ��ͨ��ODBC����֧��Oracle, SQLite, DB2, SQLServer��PostgreSQL
			connectionString:�������ݿ��ַ���

	*/
	virtual bool Connection(const std::string& connector, const std::string& connectionString, int minSession = 1, int maxSession = 2, std::size_t timeout = 60U) = 0;
	
	/*
		���ܶϿ�����
	*/
	virtual void UnConnection()=0;
public://��ѯ���
	/*
	���ܣ�
		��ѯ���ݿ�
	������
		strSQL:sql��䣬��ѯ�����
		item:���ز�ѯ�Ľ��
	˵����
		������ֻ�����ڷ���һ�е����(����T������һ��vector����)
	*/
	template<typename T>
	bool SelectSql(const std::string & strSQL, T & item);

	/*
	���ܣ�
		��ѯ���ݿ�
	������
		strSQL:sql��䣬��ѯ�����
		item:���ز�ѯ�Ľ��
		T���û��Զ������� (����ʵ��) META����
		�ṹ������Ҫһ���궨��META�����META�����þ��ǻ�ȡ�����Ԫ��Ϣ���������Ԫ��Ϣ���ǾͿ��Ժܷ����ʵ�����л��ͷ����л��ˡ�
		struct Person
		{
		int age;
		string name;
		string city;

		META(age, name, city)
		};
	˵����
		������ֻ�����ڷ���һ�е����(����T������һ��vector����)
	*/
	template<class T,class = typename std::enable_if<is_user_class<T>::value>::type>
	inline bool SelectSqlEx(const std::string & strSQL, T & t);

	/*
	���ܣ�
		��ѯ���ݿ�
	������
		strSQL:sql��䣬��ѯ�����
		args:���ز�ѯ�Ľ��
	˵����
		����args�в����б����sql��select�в����б�һ�£�
		���ʹ��select * ��Ҫ�����ݿ��б�һ��
		ʵ����tuple�汾��ֻ�����ڵ�����������
	*/
	template<typename... Args>
	bool SelectSql(const std::string & strSQL, Args& ...args);

	/*
		���ܣ�
			��ѯ���ݿ�
		������
			strSQL:sql��䣬��ѯ�����
			item:���ز�ѯ�Ľ��
		˵����
			����tuple�в����б����sql��select�в����б�һ�£�
			���ʹ��select * ��Ҫ�����ݿ��б�һ��
	*/
	template<typename... Args>
	bool SelectSql(const std::string & strSQL, std::tuple<Args...> & item);

	/*
	���ܣ�
		��ѯ���ݿ⣨���ؼ��ϣ�
	������
		strSQL:sql��䣬��ѯ�����
		items:���ز�ѯ�Ľ��
	˵����
		����tuple�в����б����sql��select�в����б�һ�£�
		���ʹ��select * ��Ҫ�����ݿ��б�һ��
	*/
	template<typename... Args>
	bool SelectSql(const std::string & strSQL, std::vector<std::tuple<Args...>> & items);
	
	/*
	���ܣ�
		��ѯ���ݿ⣨���ؼ��ϣ�
	������
		strSQL:sql��䣬��ѯ�����
		items:���ز�ѯ�Ľ��
		limit:�����������limitΪһ�����,ʹ��ContinueExecute�õ���һ��limit
	˵����
		����tuple�в����б����sql��select�в����б�һ�£�
		���ʹ��select * ��Ҫ�����ݿ��б�һ��
	*/
	template<typename... Args>
	bool SelectSql(const std::string & strSQL, std::vector<std::tuple<Args...>> & items, std::size_t _limit);

	/*
		���ܣ�
			�õ���һ��limit�޶����������һ������ֵ
	*/
	template<typename... Args>
	bool ContinueExecute(std::vector<std::tuple<Args...>> & items);

public://�������
	/*
		���ܣ�
			����һ�����ݵ����ݿ�
		������
			strSQL:sql��䣬����Ҫ�������:�ָ�
			�磺INSERT INTO user_tbl VALUES(:name, :address, :age)
			����:name, :address, :ageΪվλ����
			tuple�в����б����վλ���б�˳��һ��
	*/
	template<typename... Args>
	bool InsertSql(const std::string & strSQL, const std::tuple<Args...> & item);

	/*
	���ܣ�
		����һ�����ݵ����ݿ�
	������
		strSQL:sql��䣬����Ҫ�������:�ָ�
		�磺INSERT INTO user_tbl VALUES(:name, :address, :age)
		����:name, :address, :ageΪվλ����
		tuple�в����б����վλ���б�˳��һ��
	*/
	template<typename... Args>
	bool InsertSql(const std::string & strSQL,const std::vector<std::tuple<Args...>> & items);


public://����(update,delete,����sql����Ҫ����ֵ��)
	/*
		���ܣ�
			ִ��sql���
		������
			strSQL:����sql���
	*/
	virtual bool ExecuteSql(const std::string & strSQL)=0;
	/*
	���ܣ�
	���һ������
	������
	strSQL:����sql���
	statement:���صĽ����
	*/
	virtual MySesion GetSession() = 0;
// 	/*
// 	���ܣ��ͷ�һ������
// 	*/
// 	virtual void ReleaseSession(Poco::Data::Session & session) = 0;
public:
	/*
		���ܣ�
			��ȡ�쳣��Ϣ
		˵����
			���û���쳣�����ؿ�
	*/
	virtual std::string GetLastError() = 0;

	/*
		���ܣ�
			����쳣��Ϣ
	*/
	virtual void ClearErrorInfo() = 0;

// private:
// 	virtual void Init() = 0;//��ʼ��
// 	virtual void UnInit() = 0;//��ע��
};


#endif