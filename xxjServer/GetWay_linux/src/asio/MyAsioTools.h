#ifndef __MYASIOTOOLS_H_
#define __MYASIOTOOLS_H_
#include <string>
#include <vector>
#include <boost/smart_ptr/scoped_array.hpp>
#include <Tools/Asio/IAsioTools.h>


class CMyAsioTools:public IAsioTools
{
public:
	CMyAsioTools();
public:
	std::string Serializing(const std::string & str);//���л�
	std::vector<std::string> UnSerializingString(const char * data, int size);//�����л� �ַ���

};
#endif