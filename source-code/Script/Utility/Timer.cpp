#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
#include "Clock.h"
/// <summary>
/// �������ԓ����v������
/// </summary>
/// <param name="setLimitTime">�v������������</param>
Timer::Timer(double setLimitTime)
{
    limitTime = setLimitTime;
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// �ݒ莞�Ԃ��߂�����
/// </summary>
/// <returns>�߂�����True</returns>
bool Timer::IsOverLimitTime()const
{
    return  limitTime - GetElaspedTime() < 0;
}
/// <summary>
/// �o�ߎ���
/// </summary>
/// <returns>���b�o������</returns>
double Timer::GetElaspedTime()const
{    
    double elaspedTime = Clock::GetNowGameTime() - startTime;
    return elaspedTime;
}
/// <summary>
/// �^�C�}�[�ɐݒ肳�ꂽ����
/// </summary>
/// <returns>�^�C�}�[�ɐݒ肳�ꂽ����</returns>
double Timer::GetLimitTime() const
{
    return limitTime;
}
/// <summary>
/// �c�莞�Ԃ�����
/// </summary>
/// <returns>���Ɖ��b���Ԃ��c���Ă��邩</returns>
double Timer::GetRemainingTime() const
{
    return limitTime - GetElaspedTime();
}
