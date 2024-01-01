#include "StopTimer.h"
#include "Clock.h"
/// <summary>
/// �v���J�n
/// </summary>
/// <param name="setLimitTime">�v������</param>
StopTimer::StopTimer(double setLimitTime)
    :Timer(setLimitTime)
{
    stopFlag = false;
    stopTime = 0;
}
///<summary>
/// ������x�ŏ��ɐݒ肵���v�����ԕ��v���J�n
///</summary>
void StopTimer::Reset()
{
    //�v���J�n���Ԃ�������
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// �^�C�}�[��~
/// </summary>
void StopTimer::Stop()
{
    if(!stopFlag)
    {
        stopTime = Clock::GetNowGameTime() - startTime;
        stopFlag = true;
    }
}
/// <summary>
/// �o�ߎ���
/// </summary>
/// <returns>���b�o������</returns>
double StopTimer::GetElaspedTime()const
{
    //��~��Ȃ�c�莞�Ԃ͒�~�����Ƃ��̎c�莞��
    if (stopFlag) 
    {
        return stopTime;
    }
    //�c�莞��
    double elaspedTime = Clock::GetNowGameTime() - startTime;
    return elaspedTime;
}