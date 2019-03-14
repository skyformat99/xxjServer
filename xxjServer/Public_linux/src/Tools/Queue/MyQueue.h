/********************************************************************
	����ʱ�䣺	2014/08/15  16:26:54 
	�ļ�����		MyQueue.h
	���ߣ�		лС��
	
	���ܣ�		1. �̰߳�ȫ����
				2.
				
	˵����	    1. ���߳�״̬�µİ�ȫ����
				2. 
*********************************************************************/
#ifndef MYQUEUE_H_
#define MYQUEUE_H_
#include <queue>//std queue
#include <vector>
//#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#define  MAX_SEND_COUNT 10000

template<typename TYPE>
class CMyQueue
{
private:
	std::queue<TYPE> theQueue_;
	boost::mutex m_oMutex;
	boost::condition_variable_any m_cond;//��������
public:
	CMyQueue(){};
	~CMyQueue(){};
public:
	void Dequeue(std::vector<TYPE> & ver,bool isWait = true);//isWait:Ϊ��ʱ�Ƿ�ȴ�
	TYPE Dequeue(bool isWait = true);//���������õ�һ����Ϣ
	void Enqueue(const TYPE & e);//����һ��Ԫ��
	inline bool Empty()  { return empty(); }
	inline size_t Size() { return size(); };//���г���
	void Clear();//���Ԫ��
protected:
// 	TYPE pop();//��һ������
// 	void push( const TYPE &val );//ѹ��һ������
	size_t size();//���г���
	bool empty();//�п�
};

#endif