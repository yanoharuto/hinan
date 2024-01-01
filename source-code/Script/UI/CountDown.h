#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "DxLib.h"
#include "UIManager.h"
class Timer;
/// <summary>
/// カウントダウンのUI
/// </summary>
class CountDown
{
public:
    /// <summary>
    /// カウントダウンのUI
    /// </summary>
    /// <param name="setTimer">このタイマーの残り時間の3秒前からカウントダウンする</param>
    CountDown(std::weak_ptr<Timer> setTimer);
    /// <summary>
    /// タイマーの解放 UI削除
    /// </summary>
    ~CountDown();
    /// <summary>
    /// タイマーを進ませてUIの数字を変更する
    /// </summary>
    void Update();
    /// <summary>
    /// カウントダウンの数字の描画
    /// </summary>
    virtual void DrawUI()const;
    /// <summary>
    /// カウントダウンが終わったか
    /// </summary>
    /// <returns></returns>
    bool IsCountDownEnd()const;
    /// <summary>
    /// カウントダウンの音が鳴り終わったか
    /// </summary>
    /// <returns></returns>
    bool IsPlayCountDownSound()const;
protected:
    //カウントダウンを数えるタイマー
    std::weak_ptr<Timer> timer;
    //カウントダウンのUI
    UIData countDownUIData;
    //終わり時のUI
    UIData endUIData;
    //カウントダウンが終わったか
    bool isCountDownEnd = false;
    //カウントダウン効果音を鳴らしたか
    bool isPlayedCountSE = false;
    //カウントダウンUIの画像を変更するための添え字
    int uiHIndex = -1;
};