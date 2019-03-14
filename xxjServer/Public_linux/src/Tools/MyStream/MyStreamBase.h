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
#include <string>
#include <boost/smart_ptr/scoped_array.hpp>
#include <vector>
#include <map>
#include <set>

#include "../DefineBase.h"
class CMyStreamBase
{
//���л�
public:
	void OnSetBuffer(boost::scoped_array<unsigned char> & src, MY_UINT32 len);
	void OnSetBuffer(boost::scoped_array<signed char> & src, MY_UINT32 len);
	bool IsEnd();
//�����л�
public:
	MY_UINT32 Size();
	void Clear();
	
	MY_UINT32 OnGetBuffer(boost::scoped_array<unsigned char> & ptr);
	MY_UINT32 OnGetBuffer(boost::scoped_array<signed char> & ptr);
	std::vector<unsigned char> OnGetBuffer();
//���л�
public:
	template <typename T>
	CMyStreamBase & Push(const T & val);

	CMyStreamBase & Push(const std::string & val);
	template <typename T>
	CMyStreamBase & Push(const std::vector<T> &val);
	template <typename T, typename P>
	CMyStreamBase & Push(const std::map<T, P> &val);
	template <typename T>
	CMyStreamBase & Push(const std::set<T> &val);

	template<typename T>
	CMyStreamBase& operator<<(const T & roData);

//�����л�
public:
	template <typename T>
	CMyStreamBase & Pop(T & val);

	CMyStreamBase & Pop(std::string & val);

	template <typename T>
	CMyStreamBase & Pop(std::vector<T> &val);
	template <typename T, typename P>
	CMyStreamBase & Pop(std::map<T, P> &val);
	template <typename T>
	CMyStreamBase & Pop(std::set<T> &val);
	template<typename T>
	CMyStreamBase& operator>>(T & roData);

private://��ֹ��
	template <typename T>
	CMyStreamBase & Push(const T * val) = delete;
	template <typename T>
	CMyStreamBase & Push(T * val) = delete;
	template<typename T>
	CMyStreamBase& operator<<(const T * roData) = delete;
	template<typename T>
	CMyStreamBase& operator<<(T * roData) = delete;


	template <typename T>
	CMyStreamBase & Pop(const T * val) = delete;//error
	template <typename T>
	CMyStreamBase & Pop(T * val) = delete;//error
	template <typename T>
	CMyStreamBase & Pop(const T & val) = delete;//error
	template<typename T>
	CMyStreamBase& operator>>(T * roData)=delete;
private:
	void Memcpy(void * _Des, size_t _Size);//�����л�
	void Memcpy(const void * _Src, size_t _Size);//���л�
	std::vector<unsigned char> m_ver;
	MY_UINT32 m_indexPop = 0;
};
#endif // !__MYSTREAM_BASE_H_
