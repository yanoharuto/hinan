#include "ReusableTimer.h"
#include "Clock.h"
/// <summary>
/// �v���J�n
/// </summary>
/// <param name="setLimitTime">�v�����鎞��</param>
ReusableTimer::ReusableTimer(double setLimitTime)
    :Timer(setLimitTime)
{
 
}
///<summary>
/// ������x�ŏ��ɐݒ肵���v�����ԕ��v���J�n
///</summary>
void ReusableTimer::Reuse()
{
    //�v���J�n���Ԃ�������
    startTime = Clock::GetNowGameTime();
}
