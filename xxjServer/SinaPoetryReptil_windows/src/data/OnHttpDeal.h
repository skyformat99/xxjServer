/********************************************************************
    ����ʱ�䣺    2016/10/14  16:52:13 
    �ļ�����      OnHttpDeal.h
    ���ߣ�        лС��
    
    ���ܣ�        1.HttpRequest��
                2.
                
    ˵����        1. 
                2. 
*********************************************************************/
#ifndef _ONHTTPDEAL_H_
#define _ONHTTPDEAL_H_
#include <Tools/MySingleton.h>
#include <Tools/Libcurl/MyHttpTools.h>
#include <Tools/TimerDeal/TimeOut.h>
#include <Tools/Json/MyJson.h>

class MyHttpDeal:public CTimeOut,public MySingleton<MyHttpDeal>
{
public:
	virtual void OnTimeOut();
	void OnAnalyzeUrl(std::string & html);
	MY_UINT32 AnalyzeDateTime(const std::string & str );
protected:
	std::string OnGetPicUrls(CMyJson::JsonRoot & json, std::string original_pic);
private:
	CMyHttpTools m_myHttpTools;
};

#endif