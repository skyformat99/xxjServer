#ifndef RANDOM_H_
#define RANDOM_H_
#include <vector>
#include<boost/random.hpp>
using std::vector;
class CMyRand{
private:
	boost::mt19937 rng;//�����������
public:
	CMyRand();
  /*
  �õ��Ĵ��������ΧΪ[min,max)
  */
  unsigned int GetRand(const unsigned int min,const unsigned int max);//�õ�һ���������
  /*
  �õ��Ĵ��������ΧΪ[0,max)
  */
  unsigned int GetRand(const unsigned int max);//�õ�һ���������
  /*
  �õ��Ĵ���double������ΧΪ[min,max)
  �õ�С�������λ
  */
  double GetDoubleRand(const double max,const double min=0);//�õ�һ�����double��
};
#endif