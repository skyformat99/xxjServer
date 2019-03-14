/********************************************************************
����ʱ�䣺    2016/07/18  15:09:11
�ļ�����      MyInit.h
���ߣ�        лС��

���ܣ�        1.//������Ŀ
2.

˵����        1.
2.
*********************************************************************/
#ifndef _MYINIT_H_
#define _MYINIT_H_

#include <Tools/MyIni/MyIniBase.h>
#include <Tools/MySingleton.h>
#include <Tools/DefineBase.h>

#define  __int_ 0
#define  __string_ 1
#define  ___datetime_ 2
typedef struct tagSqlPutInfo
{
	std::string name;
	int type;
}SqlPutInfo;

typedef struct tagSqlInfo
{
	std::string key; //sql�ؼ���
	std::vector<std::string> sql; //sql ִ�����ԣ�ռλ��ʹ��?ռλ
	std::vector<SqlPutInfo> verInput;//����
	std::vector<SqlPutInfo> verOutput;//�����0:int ,1:string,2:datetime
	bool m_isRecordSet;
	tagSqlInfo()
	{
		Clear();
	}
	void Clear()
	{
		key.clear(); //sql�ؼ���
		sql.clear(); //sql ִ�����ԣ�ռλ��ʹ��?ռλ
		verInput.clear();//����
		verOutput.clear();//�����0:int ,1:string,2:datetime
		m_isRecordSet = false;
	}
}SqlInfo;




class CMyIni :public CIniBase, public MySingleton<CMyIni>
{
public:
	CMyIni(void);
	~CMyIni(void);
public:
	bool ReadText();
	bool ParseJson(const std::string & str);
	bool ParseSql(const std::string & str);
	bool ParseDBinfo(CMyJson::JsonRoot & json, DatabaseInfo & dbinfo);

	DatabaseInfo m_dbInfo;//���ݿ���Ϣ
	MY_UINT32 m_timeOut = 0;

	std::string m_serverIP;
	int m_serverPort;
	std::string m_title;
	std::string m_exestart;
	bool m_isInit = false;
	int m_max_min[2];
	std::map<std::string, SqlInfo> m_sqlMap;

	int db_timeOut = 0;

public://���ݿ����ú���

};

#endif