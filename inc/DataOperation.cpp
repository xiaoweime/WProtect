#include "DataOperation.h"
#include <time.h>


//template <class T> 
T * upset(T * t,int nSize)  //把数据乱序后返回  其他类无法调用 需要增加一个接口
{
	T *temp=new T[nSize];
	int nowsize=nSize;
	while (nowsize)
	{
		int rd=rand()%nowsize;
		temp[nSize-nowsize]=t[rd];
		nowsize--;
		for (int i = 0; i < nowsize - rd; i++)
		{
			t[rd+i]=t[rd+1+i];
		}
	}
	memcpy(t,temp,nSize * sizeof(T));
	return t;
}
