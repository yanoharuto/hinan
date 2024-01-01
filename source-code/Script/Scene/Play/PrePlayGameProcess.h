#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "UIManager.h"

class NumUI;
class Timer;
class CountDown;
class PlayManual;
class ReusableTimer;
class CollectItemObserver;
/// <summary>
/// レース前の処理やってくれる
/// </summary>
class PrePlayGameProcess
{
public:
    /// <summary>
    /// 操作説明やカウントダウン。音などを準備
    /// </summary>
    /// <param name="collectObserver">何個回収するか教えてもらう</param>
    PrePlayGameProcess(std::weak_ptr<CollectItemObserver> collectObserver);
    /// <summary>
    /// カウントダウンなどを解放
    /// </summary>
    ~PrePlayGameProcess();
    /// <summary>
    /// カウントダウンの更新
    /// </summary>
    void Update();
    /// <summary>
    /// 遊び方とカウントダウンの描画
    /// </summary>
    void Draw() const;
    /// <summary>
    /// 処理が終了したか
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess();
private:
    //収集物のアイコン
    UIData collectIconUIData;
    //操作説明のUI
    std::unique_ptr<PlayManual> playManual;
    //ゲームの目標
    UIData gamePuroseUIData;
    //収集アイテムの集める数
    std::unique_ptr<NumUI> collectItemNum;
    //コマ送り用タイマー
    std::unique_ptr<ReusableTimer> frameByFrameTimer;
    //カウントダウン用のタイマー
    std::shared_ptr<Timer> countDownTimer;
    //ゲームを始める前のカウントダウン
    std::unique_ptr<CountDown> countDown;
    //処理終了したか
    bool processEnd = false;
    //収集アイテムアイコンのコマ割り番号
    int iconGHIndex = 0;
    //ゲームの目標説明をしている間は周りを白くする
    int fadeValue = 0;
    //収集アイテムの数
    int remainingCollectNum = 0;
    //スタートのカウントダウンは5秒
    const float startTimerLimit = 5;
};