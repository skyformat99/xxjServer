/********************************************************************
	����ʱ�䣺	2015/04/29  23:52:54
	�ļ�����	testsql.h
	���ߣ�		лС��
	
	���ܣ�		1. ���ݿ������Ŀ
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#include <iostream>
//#define  __SQLLITE  //SQLite���ݿ��迪��˺�
//#define  __MYSQL	//MySql��Ҫ�����˺�
#define  __ODBC		//ODBC��Ҫ�����˺�

//ע�⣬��Ҫ��������ͷ
#include "ODBCDatabase.h"
#include "DatabaseIO.hpp"//��ģ�涨�庯��
#include "..\MyTools.h"
#include <Poco/Data/RecordSet.h>


using namespace std;
int main(int argc, char *argv[])
{
	try
	{
		CODBCDatabaseIO database;//sqlserver����
		//bool isConnect = database.ConnectionODBC("LENOVO-PC", "test", "sa", "123456", 1, 10, 60);//����һ�����ݿ����ӳ���С��1�������10����ʱ60��
		bool isConnect = database.ConnectionODBC("10_131_171_47\\SQLEXPRESS", "test", "xxj", "123", 1, 10, 60);//����һ�����ݿ����ӳ���С��1�������10����ʱ60��

// 		//��Ҫ�����__SQLLITE��SQLDefine.h�У�
// 		CDatabaseIO database;//sqlite����
// 		bool isConnect = database.Connection("Sqlite", "database.db",1,10,60);//����һ�����ݿ����ӳ���С��1�������10����ʱ60��
		
// 		//��Ҫ�����__MySql��SQLDefine.h�У�
// 		CODBCDatabaseIO database;//sqlite����
// 		bool isConnect = database.ConnectionMySql("192.168.70.8", "3306", "test", "root", "123456", 1, 10, 60);
// 		//bool isConnect = database.Connection("MySql", "host=192.168.70.8;port=3306;user=root;password=123456;db=log_test_db;compress=true;auto-reconnect=true", 1, 10, 60);//����һ�����ݿ����ӳ���С��1�������10����ʱ60��

		std::string str = "SELECT * FROM log_tab";
		
		bool bResult = false;
		{
			std::string strTemp = "SELECT max_license_id FROM log_tab where id = 1";
			int item;
			bResult = database.SelectSql(strTemp, item);//��ѯһ�����ݣ���ѯ���ֻ��һ����¼

			strTemp = "SELECT max_license_id,utc_time FROM log_tab";// "SELECT max_license_id,utc_time FROM log_tab";
			Poco::Data::Statement query(database.GetSession());
			query << strTemp;
			query.execute();
			Poco::Data::RecordSet rs(query);
			bool more = rs.moveFirst();
			while (more) {
				std::cout << "id:" << rs["id"].convert<int>() << " ";
				std::cout << "name:" << rs["name"].convert<std::string>() << " ";
				std::cout << "age:" << rs["age"].convert<int>() << " ";
				std::cout << "text:" << rs["text"].convert<std::string>() << " ";
				std::cout << "num:" << rs["num"].convert<int>() << " ";
				std::cout << "utc_time:" << rs["utc_time"].convert<std::string>() << " ";
				std::cout << std::endl;
				more = rs.moveNext();
			}

			Sleep(60000);
			return 0;
			std::vector<int> items;
			bResult = database.SelectSql(strTemp, items);//��ѯһ�����ݣ���ѯ����ж�������
		}

//		�Զ����ȡ
// 		{
// 			std::string strTemp = "SELECT max_license_id FROM log_tab where id = 1";
// 			int item;
// 			bResult = database.SelectSql(strTemp, item);//��ѯһ�����ݣ���ѯ���ֻ��һ����¼
// 
// 			strTemp = "call XXXX(100);";// "SELECT max_license_id,utc_time FROM log_tab";
// 			Poco::Data::Statement query(database.GetSession());
// 			query << strTemp;
// 			query.execute();
// 			Poco::Data::RecordSet rs(query);
// 			bool more = rs.moveFirst();
// 			while (more) {
// 				std::cout << "max_license_id:" << rs["max_license_id"].convert<int>() << " ";
// 				std::cout << "utc_time:" << rs["utc_time"].convert<std::string>() << " ";
// 				std::cout << std::endl;
// 				more = rs.moveNext();
// 			}
// 
// 			std::vector<int> items;
// 			bResult = database.SelectSql(strTemp, items);//��ѯһ�����ݣ���ѯ����ж�������
// 		}

		{
			std::string strTemp = "SELECT * FROM user_tbl where id = 1";
			//ʵ����tuple�汾��ֻ�����ڵ�����������-----------new
			struct AA
			{
				int a;
				std::string b;
				int c;
				std::string d;
				int e;
			}aa;
			bResult = database.SelectSql(strTemp, aa.a, aa.b, aa.c, aa.d, aa.e);//��ѯһ�����ݣ���ѯ����ж�����¼
			//--------------------------------------------------------------------------------new

			std::tuple<int, std::string, int, std::string, int> item;
			bResult = database.SelectSql(strTemp, item);//��ѯһ�����ݣ���ѯ���ֻ��һ����¼
			//test out put
			std::cout << std::get<0>(item) << std::endl;
			std::cout << std::get<1>(item).c_str() << std::endl;
			std::cout << std::get<2>(item) << std::endl;
			std::cout << std::get<3>(item).c_str() << std::endl;
			std::cout << std::get<4>(item) << std::endl;
		}

		
		{
			str = "SELECT * FROM user_tbl";
			std::vector<std::tuple<int, std::string, int, std::string, int>> items;
			bResult = database.SelectSql(str, items);//��ѯ�������ݣ���ѯ����ж�����¼
			//test out put
			for (auto vpk : items)
			{
				std::cout << std::get<0>(vpk) << ",";
				std::cout << std::get<1>(vpk).c_str() << ",";
				std::cout << std::get<2>(vpk) << ",";
				std::cout << std::get<3>(vpk).c_str() << ",";
				std::cout << std::get<4>(vpk) << std::endl;
			}
		}

		
		{
			std::vector<std::tuple<int, std::string, int, std::string, int>> items;
			bResult = database.SelectSql(str, items, 5);//��ѯ�������ݣ�������5����¼ ��1��
			//test out put
			for (auto vpk:items)
			{
				std::cout << std::get<0>(vpk) << ",";
				std::cout << std::get<1>(vpk).c_str() << ",";
				std::cout << std::get<2>(vpk) << ",";
				std::cout << std::get<3>(vpk).c_str() << ",";
				std::cout << std::get<4>(vpk) << std::endl;
			}


			//items.clear();
			while (database.ContinueExecute(items))//��ѯ�������ݣ���������һ��5����¼//�����ó� ��2��
			{
				for (auto vpk : items)
				{
					std::cout << std::get<0>(vpk) << ",";
					std::cout << std::get<1>(vpk).c_str() << ",";
					std::cout << std::get<2>(vpk) << ",";
					std::cout << std::get<3>(vpk).c_str() << ",";
					std::cout << std::get<4>(vpk) << std::endl;
				}
				//items.clear();
			}

			//˵������1����2������2�������루1�����ò���������
		}

		{//insert
			
			std::string strTemp = "INSERT INTO user_tbl(name,age,text,num) VALUES(?,?,?,?)";
			std::tuple<std::string, int, std::string, int> item;
			item = std::make_tuple("xxj", 111, "xxj", 100);
			bResult = database.InsertSql(strTemp, item);//����һ����¼��tuple��˳�������(name,age,text,num)��˳��һ��
			
// 			strTemp = "INSERT INTO user_tbl VALUES(:id,:name,:age,:text,:num)";
// 			std::tuple<int,std::string, int, std::string, int> item1;
// 			item1 = std::make_tuple(30,"xxj", 111, "xxj", 100);
// 			bResult = database.InsertSql(strTemp, item1);//����һ����¼��tuple ������˳����������ݿ����˳��һ��

			strTemp = "INSERT INTO user_tbl(name,age,text,num) VALUES(?,?,?,?)";
			std::vector<std::tuple<std::string, int, std::string, int>> items;
			items.push_back(item);
			std::get<0>(item) = "����";
			items.push_back(item);
			items.push_back(item);
			items.push_back(item);
			items.push_back(item);
			std::get<0>(item) = "����..n";
			items.push_back(item);
			bResult = database.InsertSql(strTemp, items);//����������ݣ�ע��tuple������˳��
		}

		{
			std::string strTemp = "UPDATE user_tbl SET name = 'xxj' WHERE id = 0";
			bResult = database.ExecuteSql(strTemp);//ִ��һ����䣬����

			strTemp = "DELETE FROM user_tbl WHERE id = 15";
			bResult = database.ExecuteSql(strTemp);//ִ��һ����䣬ɾ��
		}

		if (!bResult)//�쳣��ȡ
		{
			std::cerr << database.GetLastError()<<std::endl;//��ȡ����������
		}

	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cin.get();
	return 0;
}
