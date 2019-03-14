#ifndef MYJSON_WIN_H_
#define MYJSON_WIN_H_
#include "./include/json.h"


//Json ��ز���
class CMyJson
{
public:
	typedef Json::Value JsonRoot;//����Json����
	//��ʼ��JSONͷ
	JsonRoot CreatJson(unsigned int id)
	{
		Json::Value json;
		json["ID"] = Json::Value(id);
		return json;
	}
public://д�����
	//����һ��json����
	template<typename T>
	void AddValue(JsonRoot & json,const std::string strKey,const T & v) const
	{
		json[strKey] = Json::Value(v);
	}

	//����һ��json���� ƫ�ػ�
	template<>
	void AddValue(JsonRoot & json,const std::string strKey,const JsonRoot & jsonChild) const
	{
		json[strKey] = jsonChild;
	}

	//����һ��json���� ƫ�ػ�
	template<>
	void AddValue(JsonRoot & json,const std::string strKey,const unsigned long & v) const
	{
		char str[20];
		memset(str,0,20);
		sprintf_s(str,20,"%lu",v);
		json[strKey] = Json::Value(str);
	}

	//����һ��json���� ƫ�ػ�
	template<>
	void AddValue(JsonRoot & json,const std::string strKey,const __int64 & v) const
	{
		char str[70];
		memset(str,0,70);
		//_i64toa(v,str,69);
		sprintf_s(str,70,"%I64d",v);
		json[strKey] = Json::Value(str);
	}

	//Ϊ��������һ��Ԫ��
	template<typename T>
	void AddArrayValue(JsonRoot & json,const std::string strKey,const T & v) const
	{
		json[strKey].append(v);
	}

	template<>
	void AddArrayValue(JsonRoot & json,const std::string strKey,const unsigned long & v) const
	{
		char str[20];
		memset(str,0,20);
		sprintf_s(str,20,"%lu",v);
		json[strKey].append(str);
	}

	template<>
	void AddArrayValue(JsonRoot & json,const std::string strKey,const __int64 & v) const
	{
		char str[70];
		memset(str,0,70);
		sprintf_s(str,70,"%I64d",v);
		json[strKey].append(str);
	}


	//��һ���ַ����г�ʼ��json
	bool InitJson(const std::string str,JsonRoot & json) const
	{
		Json::Reader reader;
		json.clear();
		if (reader.parse(str,json))
			return true;
		else
			return false;
	}
public://��ȡ���
	//��ȡһ��json����
	template<typename T>
	T GetValue(const JsonRoot & json,const std::string strKey) const
	{
		if (!json[strKey].isNull())
			return json[strKey];
		else
			return NULL;
	}

	template<>
	std::string GetValue(const JsonRoot & json,const std::string strKey)const
	{
		if (!json[strKey].isNull())
			return json[strKey].asString();
		else
			return "";
	}

	template<>
	int GetValue(const JsonRoot & json,const std::string strKey)const
	{
		if (!json[strKey].isNull())
			return json[strKey].asInt();
		else
			return 0;
	}

	template<>
	bool GetValue(const JsonRoot & json,const std::string strKey)const
	{
		if (!json[strKey].isNull())
			return json[strKey].asBool();
		else
			return false;
	}

	template<>
	unsigned int GetValue(const JsonRoot & json,const std::string strKey)const
	{
		if (!json[strKey].isNull())
			return json[strKey].asUInt();
		else
			return 0;
	}

	void GetStrValue(const JsonRoot & json,const std::string strKey,std::string & v)
	{
		if (!json[strKey].isNull())
			v = json[strKey].asString();
		else
			v = "";
	}

	std::string GetStrValue(const JsonRoot & json,const std::string strKey)
	{
		if (!json[strKey].isNull())
			return json[strKey].asString();
		else
			return "";
	}

	std::string GetJsonStr(const JsonRoot & json) const
	{
		// ת��Ϊ�ַ���������ʽ��   
		//return json.toStyledString();  
		// ����޸�ʽjson�ַ���   
		Json::FastWriter writer;  
		return writer.write(json);  
	}

	std::string GetJsonFormatStr(const JsonRoot & json) const
	{
		// ת��Ϊ�ַ���������ʽ��   
		return json.toStyledString();  
		// ����޸�ʽjson�ַ���   
// 		Json::FastWriter writer;
// 		return writer.write(json);
	}
};

#endif

// ������� (����)
// {
//     "uploadid": "UP000000",
// 		"code": "0",
// 		"msg": "",
// 		"files":
//     [
// 	{
// 		"code": "0",
//             "msg": "",
//             "filename": "1D_16-35_1.jpg",
//             "filesize": "196690",
//             "width": "1024",
//             "height": "682",
//             "images":
// 		[
// 		{
// 			"url": "fmn061/20111118",
// 				"type": "large",
// 				"width": "720",
// 				"height": "479"
// 		},
// 		{
// 				"url": "fmn061/20111118",
//                     "type": "main",
//                     "width": "200",
//                     "height": "133"
// 			}
//             ]
// 	}
//     ]
// }
// ������أ�������
// int ParseJsonFromFile(const char* filename)
// {
// 	// ����json��Json::Reader
// 	Json::Reader reader;
// 	// Json::Value��һ�ֺ���Ҫ�����ͣ����Դ����������͡���int, string, object, array...
// 	Json::Value root;       
// 	
// 	std::ifstream is;
// 	is.open (filename, std::ios::binary );  
// 	if (reader.parse(is, root))
// 	{
// 		std::string code;
// 		if (!root["files"].isNull())  // ���ʽڵ㣬Access an object value by name, create a null member if it does not exist.
// 			code = root["uploadid"].asString();
// 		
// 		// ���ʽڵ㣬Return the member named key if it exist, defaultValue otherwise.
// 		code = root.get("uploadid", "null").asString();
// 		
// 		// �õ�"files"���������
// 		int file_size = root["files"].size();
// 		
// 		// ��������
// 		for(int i = 0; i < file_size; ++i)
// 		{
// 			Json::Value val_image = root["files"][i]["images"];
// 			int image_size = val_image.size();
// 			for(int j = 0; j < image_size; ++j)
// 			{
// 				std::string type = val_image[j]["type"].asString();
// 				std::string url = val_image[j]["url"].asString();
// 			}
// 		}
// 	}
// 	is.close();
// 	return 0;
// }