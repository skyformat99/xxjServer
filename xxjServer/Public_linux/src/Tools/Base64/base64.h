/********************************************************************
    ����ʱ��:     2018/10/27  16:25:19 
    �ļ���:       base64.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.base64�����
                2.
                
    ˵��:        1. 
                2. 
*********************************************************************/

#pragma once
#include<string>

class CMyBase64
{
public:
	//����
	static std::string Encode(const std::string& input );
	//����
	static std::string Decode(const std::string& input);
};


