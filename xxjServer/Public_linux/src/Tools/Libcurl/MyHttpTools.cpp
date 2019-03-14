#include "MyHttpTools.h"
#include "curl/curl.h"
#include <iostream>
#include <algorithm>


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
	char * p = (char *)buffer;
	std::string *fptr = (std::string*)userp;
	fptr->append(p, nmemb);
	return nmemb;
}


CMyHttpTools::CMyHttpTools()
{
}

CMyHttpTools::~CMyHttpTools()
{
}

std::tuple<bool, std::string> CMyHttpTools::OnOpenHttp(const std::string & url, const std::string & strFields, bool isPost, size_t timeOutSecond)
{
	CURL *curl;
	CURLcode res;
	std::string strBack;
	std::string postFields = strFields;
	//struct curl_slist *http_header = NULL;
	std::string str_url = url;
	if (!isPost && postFields.length()>0)
	{
		str_url.append("?").append(postFields);
	}

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, str_url.c_str());//URL��ַ
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());//POST����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//�Է��ص����ݽ��в����ĺ�����ַ
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBack);//����WRITEFUNCTION�ĵ��ĸ�����ֵ
	curl_easy_setopt(curl, CURLOPT_POST, isPost?1:0);//����Ϊ��0��ʾ���β���ΪPOST
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);//����Ϊ��0��ִ��ʱ��ӡ������Ϣ
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);//����Ϊ��0����Ӧͷ��Ϣͬ��Ӧ��һ�𴫸�WRITEFUNCTION
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0);//����Ϊ��0����Ӧͷ��ϢLocation
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/Users/token/curlpostLogin.cookie");//���ö�Ӧ��COOKIEFILE·������·���ļ�����һ����Ҫ�����������ʵ�ʴ���
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOutSecond);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	if (res != CURLE_OK)
	{
#ifdef _DEBUG
		switch (res)
		{
		case CURLE_UNSUPPORTED_PROTOCOL:
			std::cerr << "��֧�ֵ�Э��,��URL��ͷ��ָ��\n";
			//fprintf(stderr, "��֧�ֵ�Э��,��URL��ͷ��ָ��\n");
		case CURLE_COULDNT_CONNECT:
			std::cerr << "�������ӵ�remote�������ߴ���\n";
		case CURLE_HTTP_RETURNED_ERROR:
			std::cerr << "http���ش���\n";
		case CURLE_READ_ERROR:
			std::cerr << "�������ļ�����\n";
		default:
			std::cerr << "����ֵ:" << res << std::endl;
		}
#endif
		return std::tuple<bool,std::string>(false, "");
	}

	return std::tuple<bool, std::string>(true, strBack);
}

std::tuple<bool, std::string> CMyHttpTools::OnOpenHttps(const std::string & url, const std::string & strFields, bool isPost, size_t timeOutSecond)
{
	CURL *curl;
	CURLcode res;
	std::string strBack;
	std::string postFields = strFields;
	//struct curl_slist *http_header = NULL;
	std::string str_url = url;
	if (!isPost&& postFields.length()>0)
	{
		str_url.append("?").append(postFields);
	}

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // ����֤����  
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);  // ��֤���м��SSL�����㷨�Ƿ����  
	curl_easy_setopt(curl, CURLOPT_URL, str_url.c_str());//URL��ַ
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());//POST����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//�Է��ص����ݽ��в����ĺ�����ַ
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBack);//����WRITEFUNCTION�ĵ��ĸ�����ֵ
	curl_easy_setopt(curl, CURLOPT_POST, isPost ? 1 : 0);//����Ϊ��0��ʾ���β���ΪPOST
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);//����Ϊ��0��ִ��ʱ��ӡ������Ϣ
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);//����Ϊ��0����Ӧͷ��Ϣͬ��Ӧ��һ�𴫸�WRITEFUNCTION
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0);//����Ϊ��0����Ӧͷ��ϢLocation
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/Users/token/curlpostLogin.cookie");//���ö�Ӧ��COOKIEFILE·������·���ļ�����һ����Ҫ�����������ʵ�ʴ���
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOutSecond);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	if (res != CURLE_OK)
	{
#ifdef _DEBUG
		switch (res)
		{
		case CURLE_UNSUPPORTED_PROTOCOL:
			std::cerr << "��֧�ֵ�Э��,��URL��ͷ��ָ��\n";
			//fprintf(stderr, "��֧�ֵ�Э��,��URL��ͷ��ָ��\n");
		case CURLE_COULDNT_CONNECT:
			std::cerr << "�������ӵ�remote�������ߴ���\n";
		case CURLE_HTTP_RETURNED_ERROR:
			std::cerr << "http���ش���\n";
		case CURLE_READ_ERROR:
			std::cerr << "�������ļ�����\n";
		default:
			std::cerr << "����ֵ:" << res << std::endl;
		}
#endif
		return std::tuple<bool, std::string>(false, "");
	}

	return std::tuple<bool, std::string>(true, strBack);
}

std::tuple<bool, std::string> CMyHttpTools::OnOpenHttpByjson(const std::string & url, const std::string & strJson, bool isPost, size_t timeOutSecond)
{
	CURL *curl;
	CURLcode res;
	std::string strBack;
	std::string postFields = strJson;
	//struct curl_slist *http_header = NULL;
	std::string str_url = url;
	if (!isPost && postFields.length() > 0)
	{
		str_url.append("?").append(postFields);
	}

	//curl = curl_slist_append(nullptr,"Content-Type:application/json;charset=UTF-8");
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, str_url.c_str());//URL��ַ
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());//POST����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//�Է��ص����ݽ��в����ĺ�����ַ
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBack);//����WRITEFUNCTION�ĵ��ĸ�����ֵ
	curl_easy_setopt(curl, CURLOPT_POST, isPost ? 1 : 0);//����Ϊ��0��ʾ���β���ΪPOST
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);//����Ϊ��0��ִ��ʱ��ӡ������Ϣ
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);//����Ϊ��0����Ӧͷ��Ϣͬ��Ӧ��һ�𴫸�WRITEFUNCTION
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0);//����Ϊ��0����Ӧͷ��ϢLocation
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/Users/token/curlpostLogin.cookie");//���ö�Ӧ��COOKIEFILE·������·���ļ�����һ����Ҫ�����������ʵ�ʴ���
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOutSecond);
	curl_slist *plist = curl_slist_append(NULL,"Content-Type:application/json;charset=UTF-8");// ����http���͵���������ΪJSON 
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
	res = curl_easy_perform(curl);
	curl_slist_free_all(plist);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	
	if (res != CURLE_OK)
	{
#ifdef _DEBUG
		switch (res)
		{
		case CURLE_UNSUPPORTED_PROTOCOL:
			std::cerr << "��֧�ֵ�Э��,��URL��ͷ��ָ��\n";
			//fprintf(stderr, "��֧�ֵ�Э��,��URL��ͷ��ָ��\n");
		case CURLE_COULDNT_CONNECT:
			std::cerr << "�������ӵ�remote�������ߴ���\n";
		case CURLE_HTTP_RETURNED_ERROR:
			std::cerr << "http���ش���\n";
		case CURLE_READ_ERROR:
			std::cerr << "�������ļ�����\n";
		default:
			std::cerr << "����ֵ:" << res << std::endl;
		}
#endif
		return std::tuple<bool, std::string>(false, "");
	}

	return std::tuple<bool, std::string>(true, strBack);
}
