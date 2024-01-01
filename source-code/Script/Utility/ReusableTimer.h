#pragma once
#include "Timer.h"
/// <summary>
/// もう一度時間を計測できるタイマー
/// </summary>
class ReusableTimer final: public Timer
{
public:
    /// <summary>
    /// 計測開始
    /// </summary>
    /// <param name="setLimitTime">計測する時間</param>
    ReusableTimer(double setLimitTime);
    ///<summary>
    /// もう一度最初に設定した計測時間分計測開始
    ///</summary>
    void Reuse();
};