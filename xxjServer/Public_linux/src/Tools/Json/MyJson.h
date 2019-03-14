#ifndef MYJSON_H_
#define MYJSON_H_
#include "./include/json.h"
#include <stdint.h>
#include <string.h>


//Json ��ز���
namespace CMyJson
{
	//�������
	typedef JsonXXJ::Value JsonRoot;//����Json����
	//��ʼ��JSONͷ
	inline JsonRoot CreatJson(unsigned int id)
	{
		JsonXXJ::Value json;
		json["ID"] = JsonXXJ::Value(id);
		return json;
	}
	//д�����
	//����һ��json����
	template<typename T>
	inline void AddValue(JsonRoot & json, const std::string strKey, const T & v)
	{
		json[strKey] = JsonXXJ::Value(v);
	}

	//����һ��json���� ƫ�ػ�
	template<>
	inline void AddValue(JsonRoot & json, const std::string strKey, const JsonRoot & jsonChild)
	{
		json[strKey] = jsonChild;
	}

	//����һ��json���� ƫ�ػ�
	template<>
	inline void AddValue(JsonRoot & json, const std::string strKey, const unsigned long & v)
	{
		char str[20];
		memset(str,0,20);
#ifdef _WIN32
		sprintf_s(str, 20, "%lu", v);
#else
		sprintf(str, "%lu", v);
#endif // _WIN32
		
		json[strKey] = JsonXXJ::Value(str);
	}

	//����һ��json���� ƫ�ػ�
	template<>
	inline void AddValue(JsonRoot & json, const std::string strKey, const int64_t & v)
	{
		char str[70];
		memset(str,0,70);
		//_i64toa(v,str,69);
#ifdef _WIN32
		sprintf_s(str, 70, "%I64d", v);
#else
		sprintf(str, "%I64d", v);
#endif // _WIN32
		
		json[strKey] = JsonXXJ::Value(str);
	}

	//��ʼ��һ������
	inline void InitArray(JsonRoot & json, const std::string strKey)
	{
		json[strKey].resize(0);
	}

	//Ϊ��������һ��Ԫ��
	template<typename T>
	inline void AddArrayValue(JsonRoot & json, const std::string strKey, const T & v)
	{
		json[strKey].append(v);
	}

	template<>
	inline void AddArrayValue(JsonRoot & json, const std::string strKey, const unsigned long & v)
	{
		char str[20];
		memset(str,0,20);
#ifdef _WIN32
		sprintf_s(str, 20, "%lu", v);
#else
		sprintf(str, "%lu", v);
#endif // _WIN32
		json[strKey].append(str);
	}

	template<>
	inline void AddArrayValue(JsonRoot & json, const std::string strKey, const int64_t & v)
	{
		char str[70];
		memset(str,0,70);
#ifdef _WIN32
		sprintf_s(str, 70, "%I64d", v);
#else
		sprintf(str, "%I64d", v);
#endif // _WIN32
		json[strKey].append(str);
	}


	//��һ���ַ����г�ʼ��json
	inline bool InitJson(const std::string str, JsonRoot & json)
	{
		//�����ϸ�ģʽ���÷Ƿ���json����ʱֱ�ӷ���false�����Զ��ݴ�
		JsonXXJ::Reader reader(JsonXXJ::Features::strictMode());
		json.clear();
		if (reader.parse(str,json))
			return true;
		else
			return false;
	}
	//��ȡ���
	//��ȡһ��json����
	template<typename T>
	inline T GetValue(const JsonRoot & json, const std::string strKey)
	{
		
		if (!json[strKey].isNull())
			return json[strKey];
		else
			return T();
	}

	template<>
	inline double GetValue(const JsonRoot & json, const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asDouble();
		else
			return 0.0f;
	}

	template<>
	inline std::string GetValue(const JsonRoot & json, const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asString();
		else
			return "";
	}

	template<>
	inline int GetValue(const JsonRoot & json, const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asInt();
		else
			return 0;
	}

	template<>
	inline bool GetValue(const JsonRoot & json, const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asBool();
		else
			return false;
	}

	template<>
	inline unsigned int GetValue(const JsonRoot & json, const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asUInt();
		else
			return 0;
	}

	inline void GetStrValue(const JsonRoot & json, const std::string strKey, std::string & v)
	{
		if (!json[strKey].isNull())
			v = json[strKey].asString();
		else
			v = "";
	}

	inline std::string GetStrValue(const JsonRoot & json, const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asString();
		else
			return "";
	}

	inline std::string GetJsonStr(const JsonRoot & json)
	{
		// ת��Ϊ�ַ���������ʽ��   
		//return json.toStyledString();  
		// ����޸�ʽjson�ַ���   
		JsonXXJ::FastWriter writer;  
		return writer.write(json);  
	}

	inline std::string GetJsonFormatStr(const JsonRoot & json)
	{
		// ת��Ϊ�ַ���������ʽ��   
		return json.toStyledString();  
		// ����޸�ʽjson�ַ���   
// 		Json::FastWriter writer;
// 		return writer.write(json);
	}
};

#endif