#ifndef HGL_TIME_INCLUDE
#define HGL_TIME_INCLUDE

#include<hgl/type/DataType.h>

namespace hgl   //ʱ��
{
    int GetTimeZone();																				///<����ʱ����ʱ��(��λ����)

    uint64 GetMilliStartTime();																		///<ȡ�ú����������ʱ��(��λ��1/1000��)
    uint64 GetMicroStartTime();																		///<ȡ��΢���������ʱ��(��λ��1/1000000��)
    double GetDoubleStartTime();																	///<ȡ�����������ʱ��(��λ����)

    uint64 GetTime();																				///<ȡ�õ�ǰʱ��(��λ��1/1000��)
    uint64 GetMicroTime();																			///<ȡ�õ�ǰʱ��(��λ��1/1000000��)
    double GetDoubleTime();																			///<ȡ�õ�ǰʱ��(��λ����)

    double GetLocalDoubleTime();																	///<ȡ�ñ��ص�ǰʱ��(��λ����)

    void WaitTime(double);																			///<�ȴ�һ��ʱ��(��λ����)
}//namespace hgl

#endif//HGL_TIME_INCLUDE
