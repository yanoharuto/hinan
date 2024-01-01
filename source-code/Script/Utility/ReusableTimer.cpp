#include "ReusableTimer.h"
#include "Clock.h"
/// <summary>
/// 計測開始
/// </summary>
/// <param name="setLimitTime">計測する時間</param>
ReusableTimer::ReusableTimer(double setLimitTime)
    :Timer(setLimitTime)
{
 
}
///<summary>
/// もう一度最初に設定した計測時間分計測開始
///</summary>
void ReusableTimer::Reuse()
{
    //計測開始時間を初期化
    startTime = Clock::GetNowGameTime();
}
