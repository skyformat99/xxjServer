/********************************************************************
    ����ʱ�䣺    2015/08/06  10:16:23 
    �ļ�����      MyTimes.h
    ���ߣ�        xxj
    
    ����:		1.ʱ����غ���
				2.
                
    ˵��:		1. 
                2. 
*********************************************************************/
#ifndef _MYTIMES_H_
#define _MYTIMES_H_
#include "DefineBase.h"
#include <string>

#define GMT_OFFSET (8 * 60 * 60)
#define WEEK_OFFSET 3 //����4
#define CST_OFFSET (14*60L*60L) //CSTʱ��ƫ��
#define DAY_OFFSET (24*60L*60L) //CSTʱ��ƫ��

class CMyTimes
{
public:
	/*
		��ȡ��ǰʱ�� Unixʱ��� 1970/1/1 8:0:0 ��
	*/
	static MY_UINT32 get_utc();
	static MY_LONGLONG GetUTCTime(bool ismicroseconds);
	static MY_UINT32 Get_current_day_0_0();//��ȡ�����0ʱ0��0��
	static MY_UINT32 Get_current_day_0_0(MY_UINT32 _time);//��ǰʱ���0ʱ0��0��
	static int get_week(MY_UINT32 unCurrentTime);//1~0
	static int get_day(MY_UINT32 unCurrentTime);
	static int get_month(MY_UINT32 unCurrentTime);
	static MY_UINT32 get_day_time(MY_UINT32 unCurrentTime);//��ȡ�����賿ƫ��ʱ��
	static MY_UINT32 Get_Detail_from_str(const char * str);//ʱ��ת����ACE_UINT32,��ʽ����-��-��[�ո�]ʱ:��:��(2015-04-21 12:00:00	
	static MY_UINT32 CSTtoUTC(const char * str);
	static std::string GetTimeStr(MY_UINT32 _time);//��ȡʱ�� ���ظ�ʽ����-��-��[�ո�]ʱ:��:��(2015-04-21 12:00:00
	static std::string GetDayStr(MY_UINT32 _time);//��ȡʱ�� ���ظ�ʽ����-��-��
	static MY_UINT32 Get_day_Offset(MY_UINT32 _time, int offset);//��ȡoffset���һ��
	static int GetSubDay(MY_UINT32 _start,MY_UINT32 _end);
	static MY_UINT32 Get_Hour(MY_UINT32 _time);////��ȡ���� 0��0�� Сʱ
	static MY_UINT32 Get_Month_Offset_0(MY_UINT32 _time, int offset);//��ȡoffset����ǰ��1�� �³�
	
};

#endif