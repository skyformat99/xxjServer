
/********************************************************************
    ����ʱ��:     2017/12/04  20:33:03 
    �ļ���:       MyAes.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.AES�����㷨
                2.
                
    ˵��:        1. 
                2. 
*********************************************************************/
#include <string>

// ����
const unsigned char g_key[] =
{
	0x2b, 0x7e, 0x15, 0x16,
	0x28, 0xae, 0xd2, 0xa6,
	0xab, 0xf7, 0x15, 0x88,
	0x09, 0xcf, 0x4f, 0x3c
};

class CMyAesTools
{
public:
	//����
	int Encrypt(std::string S, unsigned char * & des);

	//����
	std::string Decrypt(unsigned char *& des, int len);
};