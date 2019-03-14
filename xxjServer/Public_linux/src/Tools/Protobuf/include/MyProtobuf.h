/********************************************************************
    ����ʱ��:     2016/12/19  15:10:15 
    �ļ���:       MyProtobuf.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.
                2.
                
    ˵��:        1. 
                2. 
*********************************************************************/
#ifndef MYPROTOBUF_H_
#define MYPROTOBUF_H_
#include <boost/any.hpp>
#include "../../MySingleton.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <map>
#include <iostream>
#include "../../DefineBase.h"
//#include "../../../test/query.pb.h"


class CMyProtobuf:public MySingleton<CMyProtobuf>
{
public:
	//����pb�ķ��䣬ͨ��Э���ִ���̬����һ��Э��
	template <typename T> 
	std::shared_ptr<T> OnCreatMessage(const std::string& typeName);

	//ע���ͷ�
	//ʹ�����·�ʽת��  
	//std::shared_ptr<DeriveClass> ptr = std::dynamic_pointer_cast<DeriveClass>(ptrBase);  
	std::shared_ptr<google::protobuf::Message> OnCreatMessage(const std::string& typeName);

};

//��Ϣ�ַ���
class ProtobufDispatcher
{
public:
	typedef std::function<void()> Functor;

	//ProtobufDispatcher(std::function<void(std::shared_ptr<google::protobuf::Message> message)> discardProtobufMessage)
	//	: defaultCallback_(discardProtobufMessage)
	ProtobufDispatcher(){}

	template<typename T>
	void OnMessage(std::shared_ptr<T> & message) const;


	template<typename T>
	void OnRegisterMessageCallback(const std::function<void(std::shared_ptr<google::protobuf::Message>&)>& callback);

	std::map<const google::protobuf::Descriptor*, boost::any> callbacks_;
	//std::function<void(std::shared_ptr<google::protobuf::Message>&)> defaultCallback_;
};



#endif