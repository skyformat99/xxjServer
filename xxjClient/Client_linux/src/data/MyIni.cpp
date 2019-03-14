#include "MyIni.h"
#include <fstream> 
#include <iostream>
#include <Tools/Json/MyJson.h>
#include <Tools/Asio/ISocketBase.h>
#include "MyClientDataModel.h"

CMyIni::CMyIni(void)
{
	m_serverPort = 0;
}

CMyIni::~CMyIni(void)
{
}

bool CMyIni::ReadText()
{
	//����Ǹ��ܴ�Ķ��д洢���ı����ļ�������ô����  
	char buf[1024];                //��ʱ�����ȡ�������ļ�����  
	std::string str;  
	std::ifstream infile;  
	infile.open("config.json");  
	if(infile.is_open())          //�ļ��򿪳ɹ�,˵������д�������  
	{  
		while(infile.good() && !infile.eof())  
		{  
			memset(buf,0,1024);  
			infile.getline(buf,1024); 
			str.append(buf); 
			str.append("\n");
		}  
		infile.close();  

		return ParseJson(str);
	}  
	else
	{
		std::cout<<"����config.json�ļ�ʧ��"<<std::endl;
		std::cin.get();
		return false;
	}
}

bool CMyIni::ParseJson( const std::string & str )
{
	//m_verTOaddress.clear();
	//std::vector<std::string>().swap(m_verTOaddress);
	CMyJson::JsonRoot json;
	CMyJson::InitJson(str,json);
	m_serverIP = CMyJson::GetStrValue(json,"serverIP");
	m_serverPort = CMyJson::GetValue<int>(json,"serverPort");
	for (unsigned i=0;i<json["opKey"].size();i++)
	{
		m_opMap[json["opKey"][i].asString()] = json["opvalue"][i].asInt();
	}
	m_title = CMyJson::GetStrValue(json,"title");;
	m_exestart = CMyJson::GetStrValue(json,"exestart");;

	CMyClientDataModel::instance()->isLog = CMyJson::GetValue<bool>(json,"isLog");

	return true;
}
