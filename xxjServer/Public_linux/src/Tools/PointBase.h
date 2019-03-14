/********************************************************************
    ����ʱ�䣺    2016/10/07  18:36:10 
    �ļ�����      PointBase.h
    ���ߣ�        лС��
    
    ���ܣ�        1.ָ�����������
                 2.
                
    ˵����        1. 
                 2. 
*********************************************************************/

#ifndef  _POINTBASE_H_
#define  _POINTBASE_H_


template <class T>
class CPointBase
{
public:
	T & operator*() const  // never throws
	{
		assert(px != 0);
		return *px;
	}

	T * operator&() const  // never throws
	{
		assert(px != 0);
		return px;
	}

	T * operator->() const  // never throws
	{
		assert(px != 0);
		return px;
	}

	bool IsNull()
	{
		return px == nullptr;
	}
protected:
	T * px = nullptr;
};

#endif