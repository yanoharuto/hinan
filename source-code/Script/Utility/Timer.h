#pragma once
/// <summary>
/// 決められた時間進んだりする
/// </summary>
class Timer
{
public:
    /// <summary>
    /// 制限時間等を計測する
    /// </summary>
    /// <param name="setLimitTime">計測したい時間</param>
    Timer(double setLimitTime);
    /// <summary>
    /// 設定時間を過ぎたか
    /// </summary>
    /// <returns>過ぎたらTrue</returns>
    bool IsOverLimitTime()const;
    /// <summary>
    /// 経過時間
    /// </summary>
    /// <returns>何秒経ったか</returns>
    virtual double GetElaspedTime()const;
    /// <summary>
    /// タイマーに設定された時間
    /// </summary>
    /// <returns>タイマーに設定された時間を返す</returns>
    double GetLimitTime()const;
    /// <summary>
    /// 残り時間を所得
    /// </summary>
    /// <returns>あと何秒時間が残っているか</returns>
    double GetRemainingTime()const;
protected:
    //制限時間
    double limitTime = 0;
    //計測開始時間
    double startTime = 0;
};