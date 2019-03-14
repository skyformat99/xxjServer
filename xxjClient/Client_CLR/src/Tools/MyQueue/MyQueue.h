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
#include "../ClientTypeDefine.h"

#define  MAX_SEND_COUNT 10000

generic<typename TYPE>
ref class CMyQueue
{
private:
	System::Threading::Mutex^ m_mutex;

	Queue<TYPE>^ m_queue;
public:
	CMyQueue()
	{
		m_mutex = gcnew System::Threading::Mutex();
		m_queue = gcnew Queue<TYPE>();
	};
	~CMyQueue() {};
public:
	TYPE Dequeue(bool isWait) {//���������õ�һ����Ϣ
		if (isWait)
		{
			while (empty())
			{
				System::Threading::Thread::Sleep(10);
			}
		}

		m_mutex->WaitOne();
		if (empty())
		{
			m_mutex->ReleaseMutex();
			return Dequeue(isWait);
		}
		else {
		
			TYPE temp = m_queue->Dequeue();
			m_mutex->ReleaseMutex();
			return temp;
		}

	};
	void Enqueue(TYPE  e) {//����һ��Ԫ��
		m_mutex->WaitOne();
		m_queue->Enqueue(e);
		m_mutex->ReleaseMutex();
	};
	inline bool Empty()  { return empty(); }
	inline size_t Size() { return size(); };//���г���
protected:
// 	TYPE pop();//��һ������
// 	void push( const TYPE &val );//ѹ��һ������
	size_t size() {//���г���
		return m_queue->Count;
	};
	bool empty() {//�п�
		return Size() == 0;
	};
};



#endif