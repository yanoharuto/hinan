#pragma once
//fps
#define FLAME 60
/// <summary>
/// ゲーム内の時間を更新
/// </summary>
class Clock
{
public:
    /// <summary>
    /// ゲーム開始の瞬間を保存
    /// </summary>
    Clock();
    /// <summary>
    /// タイマーを更新する
    /// </summary>
    void Update();
    /// <summary>
    /// ゲームの経過時間を1000m秒にして渡す
    /// </summary>
    /// <returns></returns>
    static double GetNowGameTime();
private:
    //1000m秒
    double timeD;
    //普通の経過秒数
    static double gameTime;
};