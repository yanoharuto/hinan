#pragma once
#include "Timer.h"
/// <summary>
/// 止めることが出来るタイマー
/// </summary>
class StopTimer final : public Timer
{
public:
    /// <summary>
    /// 計測開始
    /// </summary>
    /// <param name="setLimitTime">計測時間</param>
    StopTimer(double setLimitTime);
    ///<summary>
    /// もう一度最初に設定した計測時間分計測開始
    ///</summary>
    void Reset();
    /// <summary>
    /// タイマー停止
    /// </summary>
    void Stop();
    /// <summary>
    /// 経過時間
    /// </summary>
    /// <returns>何秒経ったか</returns>
    double GetElaspedTime()const override;
private:
    //停止中か
    bool stopFlag = false;
    //停止したときの残り時間
    double stopTime;
};