/********************************************************************
    ����ʱ��:     2017/08/22  14:46:29 
    �ļ���:       MyCereal.h
    ����:         лС��
    emal:        346944475@qq.com
    
    ����:        1.�������л���ز���
                2.ʹ��cereal��Ϊ�����׼�
                
    ˵��:        1. ֧�֣�xml�������ƣ�json��ʽ
                2. 
*********************************************************************/
#ifndef MYCEREAL_H_
#define MYCEREAL_H_
#include "include/cereal/types/unordered_map.hpp"
#include "include/cereal/types/memory.hpp"
#include "include/cereal/archives/binary.hpp"
#include "include/cereal/archives/xml.hpp"
#include "include/cereal/archives/json.hpp"
#include "include/cereal/types/string.hpp"
#include <fstream>
#include <Tools/MyTools.h>


//����ʽ����ÿ����Ҫ����
#define META(...) template <class Archive>\
				void serialize(Archive & ar)\
				{\
				ar(__VA_ARGS__);\
				}\

namespace CMyCereal 
{
	//����һ���������л��ļ����ڴ� 
	//�����Ʒ���
	template<typename T>
	inline bool OnLoadBinary(std::string dir,T & out) {
		if (MyTools::FileIsExist(dir)) {
			try
			{
				std::ifstream is(dir, std::ios::binary);
				cereal::BinaryInputArchive archive(is);
				archive(out);
				return true;
			}
			catch (std::exception & e)
			{
				MyTools::PrintError(e.what());
			}
		}
		return false;
	}

	//�����ڴ浽�����ļ�
	//�����Ʒ���
	template<typename T>
	inline bool OnSaveBinary(std::string dir,const T & out) {
		try
		{
			std::ofstream os(dir, std::ios::binary);
			cereal::BinaryOutputArchive archive(os);
			archive(out);
			return true;
		}
		catch (std::exception & e)
		{
			MyTools::PrintError(e.what());
		}
		return false;
	}
}


#endif // !__
