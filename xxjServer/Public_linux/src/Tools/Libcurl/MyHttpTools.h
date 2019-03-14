/********************************************************************
    ����ʱ�䣺    2016/11/20  13:57:08 
    �ļ�����      CMyHttpTools.h
    ���ߣ�        лС��
    
    ���ܣ�        1.httpTools
                 2.http����
                
    ˵����        1. �������
                 2. 
*********************************************************************/
#ifndef MYHTTPTOOLS_H_
#define MYHTTPTOOLS_H_
#include <string>
#include <tuple>

class CMyHttpTools
{
public:
	CMyHttpTools();
	~CMyHttpTools();
public:
	/**
	* ����һ��url������ֵ(ͬ����������ʽ)
	* ����:
	* url:����ĵ�ַ
	* strFields:����Ĳ���,���������&�ָ�:��:A=a&B=b&C=c
	* isPost:�Ƿ���post����falseΪget����
	*����ֵ:
	*tuple<0> :�����Ƿ���ȷ���
	*tuple<1> :��������ȷ����֮�󷵻ص�����
	*/
	std::tuple<bool, std::string> OnOpenHttp(const std::string & url, const std::string & strFields = "",bool isPost = true,size_t timeOutSecond = 60L );
	/**
	* ����һ����ȫhttps���ݲ�����ֵ(ͬ����������ʽ)
	* ����:
	* url:����ĵ�ַ
	* strFields:����Ĳ���,���������&�ָ�:��:A=a&B=b&C=c
	* isPost:�Ƿ���post����falseΪget����
	*����ֵ:
	*tuple<0> :�����Ƿ���ȷ���
	*tuple<1> :��������ȷ����֮�󷵻ص�����
	*/
	std::tuple<bool, std::string> OnOpenHttps(const std::string & url, const std::string & strFields = "", bool isPost=true, size_t timeOutSecond = 60L);

	/** 
	* ��rest json ��ʽ��������
	* ����:
	* url:����ĵ�ַ
	* strFields:����Ĳ���,json�ַ���
	* isPost:�Ƿ���post����falseΪget����
	*����ֵ:
	*tuple<0> :�����Ƿ���ȷ���
	*tuple<1> :��������ȷ����֮�󷵻ص�����
	*/
	std::tuple<bool, std::string> OnOpenHttpByjson(const std::string & url, const std::string & strJson = "{}", bool isPost = true, size_t timeOutSecond = 60L);


};


#endif
