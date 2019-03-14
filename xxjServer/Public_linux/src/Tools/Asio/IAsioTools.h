#ifndef __IASIOTOOLS_H_
#define __IASIOTOOLS_H_
#include <vector>
//#include <boost/smart_ptr/scoped_array.hpp>
#include "../Asio/DefineBase.h"
#include "../Asio/GameDefine.h"
#include <memory>
#define MAX_RESERVE_SIZE 1024*8  //�����ճߴ�
#define MAX_HEAD_LEN sizeof(MY_UINT32)//tlv ��l���ȡ�  
#define MAX_HEAD_STR "%04d" 

class IAsioTools
{
public:
	IAsioTools();
	~IAsioTools();
public://������
	virtual MY_UINT32 SerializingBinary(const MsgInfo & msg, boost::scoped_array<char> & _dir);//���л�
	virtual MY_UINT32 SerializingBinary(const MsgInfo & msg, std::shared_ptr<char> & _dir);//���л�
	virtual MY_UINT32 SerializingBinary(const MsgInfo & msg, char * _dir);//���л�
	virtual std::vector<MsgInfo> UnSerializingBinary(const char * data, int size);//�����л� ������
public://�ַ���
	std::string Serializing(const std::string & str);//���л�
	std::vector<std::string> UnSerializingString(const char * data, int size);//�����л� �ַ���

protected:
	char _Data[2 * MAX_RESERVE_SIZE];
	MY_UINT32 _len;

protected:
	void writeUInt(void * _dir, MY_UINT32 v, MY_UINT32 & offset);
	void writeArray(void * _dir,const unsigned char * _src,MY_UINT32 len, MY_UINT32 & offset);
	void writeInt(void * _dir, int v, MY_UINT32 & offset);
	void writeString(void * _dir, const void * _src, MY_UINT32 len, MY_UINT32 & offset);

	void ReadUInt(void * _dir, const void * _src, MY_UINT32 & offset);
	void ReadArray(void * _dir, const void * _src,MY_UINT32 len, MY_UINT32 & offset);
	void ReadString(void * _dir, const void * _src, MY_UINT32 len, MY_UINT32 & offset);
	void Rmemcpy(void * _Dst, const void * _Src, size_t _Size);
protected:
	virtual bool UnSerializingMsg(boost::scoped_array<char> & _src, MY_UINT32 size, MsgInfo & info);

//�Զ�����Ϣ����
//ʹ��MyStream��
};



#endif