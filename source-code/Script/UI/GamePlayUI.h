#pragma once
#include <iostream>
#include <memory>
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class PlayerObserver;
class EndCountDown;
class EnemyGenerator;
class CollectCompass;
class PlayManual;
class CollectItemObserver;
class ReusableTimer;
/// <summary>
/// 遊んでいるときのUI
/// </summary>
class GamePlayUI final
{
public:
    /// <summary>
    /// プレイヤーや制限時間、収集アイテムの数などを表示できるようにする
    /// </summary>
    /// <param name="player">プレイヤーの位置</param>
    /// <param name="timer">制限時間</param>
    /// <param name="collectItemObserver">収集アイテム情報</param>
    GamePlayUI(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer, std::shared_ptr<CollectItemObserver> collectItemObserver);
    /// <summary>
    /// 各UIを解放
    /// </summary>
    ~GamePlayUI();
    /// <summary>
    /// ミニマップの更新や収集アイテムの枚数を更新
    /// </summary>
    void Update();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const;
private:
    //最初の収集アイテムの枚数
    int allCollectNum = 0;
    // プレイヤーが所得した枚数
    int nowGetCollectNum = 0;
    //残りの収集アイテム数を表示するか
    bool isDrawGetNum = false;
    //残りの収集アイテム数を表示する時間
    float remainingNumDrawTime = 2.0f;
    //残った収集アイテムの数の表示時間を計る
    std::unique_ptr<ReusableTimer> remainingNumDrawTimer = nullptr;
    //ゲーム残り時間タイマー
    std::unique_ptr<TimerUI> gameTimerUI;
    //ミニマップ
    std::unique_ptr<MiniMap> minimapUI;
    //最初の収集アイテムの枚数を描画するクラス
    std::unique_ptr<NumUI> firstCollectNumUI;
    //ゲットした収集アイテムの枚数を描画
    std::unique_ptr<NumUI> getNumUI;
    //残った収集アイテムの数
    std::unique_ptr<NumUI> remainingNumUI;
    //残り収集アイテムについてのフレーズ
    UIData remainingFrazeUIData;
    //数字の間に置くスラッシュ
    UIData frameUIData;  
    //カウントダウン
    std::unique_ptr<EndCountDown> countDown;
    //プレイヤーの位置とか収集アイテムの所得数などを教えてくれる奴
    std::weak_ptr<PlayerObserver> playerObserver;
    //収集アイテムの方向とかを教えてくれる
    std::unique_ptr<CollectCompass> collectCompass;
    //プレイヤーの操作方法
    std::unique_ptr<PlayManual> playManual;
};