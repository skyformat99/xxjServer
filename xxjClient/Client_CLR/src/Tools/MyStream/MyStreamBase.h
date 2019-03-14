/********************************************************************
    ����ʱ��:     2017/05/25  15:06:23 
    �ļ���:       MyStreamBase.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.���������л��������л�������
                2.������
                
    ˵��:        1. ֧��map,vector,string���������ͣ�
                2. ��֧��ָ�����л������л�
*********************************************************************/
#ifndef __MYSTREAM_BASE_H_
#define __MYSTREAM_BASE_H_
//#include <cliext/vector>

#include "../ClientTypeDefine.h"

public ref class CMyStreamBase
{
public:
	CMyStreamBase();
//���л�
public:
	void OnSetBuffer(PTR(array<Byte>) src, MY_UINT32 len);
	bool IsEnd();

	MY_UINT32 OnGetBuffer(REF(PTR(array<Byte>)) ptr);
	PTR(array<Byte>) OnGetBuffer();

//�����л�
public:
	MY_UINT32 Size();
	void Clear();
	//���л�
public:
	PTR(CMyStreamBase) Push(const void * _Src, size_t _Size);

	PTR(CMyStreamBase) PushString(PTR(string) val);

	generic<typename T>
	PTR(CMyStreamBase) Push(T val);

	generic<typename T>
	PTR(CMyStreamBase) Push(PTR(array<T>) val);//��Ӧvector

	generic<typename T>
	PTR(CMyStreamBase) Push(PTR(List<T>) val);//��ӦSet

	generic<typename T,typename P>
	PTR(CMyStreamBase) Push(Dictionary<T,P>^ val);//��Ӧmap
//�����л�
public:
	PTR(CMyStreamBase) Pop(void * _Src, size_t _Size);

	generic<typename T>
	PTR(CMyStreamBase) Pop(REF(T) val);

	generic<typename T>
	PTR(CMyStreamBase) PopString(REF(T) val);

	generic <typename T>
	PTR(CMyStreamBase) Pop(REF(PTR(array<T>)) val);//��Ӧvector

	generic<typename T>
	PTR(CMyStreamBase) Pop(REF(PTR(List<T>)) val);//��ӦSet

	generic<typename T, typename P>
	PTR(CMyStreamBase) Pop(Dictionary<T, P>^ % val);//��Ӧmap

private:
	void Memcpy(void * _Des, size_t _Size);//�����л�
	void Memcpy(const void * _Src, size_t _Size);//���л�
	PTR(List<Byte>) m_ver;
	MY_UINT32 m_indexPop = 0;
};



#endif // !__MYSTREAM_BASE_H_
