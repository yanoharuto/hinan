#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
#include "Clock.h"
/// <summary>
/// 制限時間等を計測する
/// </summary>
/// <param name="setLimitTime">計測したい時間</param>
Timer::Timer(double setLimitTime)
{
    limitTime = setLimitTime;
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// 設定時間を過ぎたか
/// </summary>
/// <returns>過ぎたらTrue</returns>
bool Timer::IsOverLimitTime()const
{
    return  limitTime - GetElaspedTime() < 0;
}
/// <summary>
/// 経過時間
/// </summary>
/// <returns>何秒経ったか</returns>
double Timer::GetElaspedTime()const
{    
    double elaspedTime = Clock::GetNowGameTime() - startTime;
    return elaspedTime;
}
/// <summary>
/// タイマーに設定された時間
/// </summary>
/// <returns>タイマーに設定された時間</returns>
double Timer::GetLimitTime() const
{
    return limitTime;
}
/// <summary>
/// 残り時間を所得
/// </summary>
/// <returns>あと何秒時間が残っているか</returns>
double Timer::GetRemainingTime() const
{
    return limitTime - GetElaspedTime();
}
