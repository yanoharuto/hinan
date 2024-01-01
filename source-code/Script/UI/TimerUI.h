#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "UIManager.h"
class Timer;
class NumUI;
/// <summary>
/// 残り時間を描画する
/// </summary>
class TimerUI
{
public:
    /// <summary>
    /// 残り時間のセットと数字画像の読み込み
    /// </summary>
    /// <param name="setTimer">残り時間タイマー</param>
    TimerUI(std::weak_ptr<Timer> setTimer);
    /// <summary>
    /// タイマーのロック解除 UI削除
    /// </summary>
    ~TimerUI();
    //残り時間を描画する
    void Draw();
private:
    //数字のフォント画像
    UIData frameUIData;
    //小数点
    UIData pointUIData;
    //タイマーの枠の横位置
    int frameX;
    //残り時間を所得する用
    std::weak_ptr<Timer> timer;
    //数字を描画する
    std::unique_ptr<NumUI> numUI = nullptr;
};