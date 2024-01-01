#pragma once
#include <iostream>
#include <memory>
class PlayerObserver;
class GamePlayUI;
class CollectItemObserver;
class StopTimer;
class Timer;
/// <summary>
/// ゲーム中の処理役
/// </summary>
class PlayGameProcess
{
public:
    /// <summary>
    /// BGMとゲーム終了タイマーを起動
    /// </summary>
    /// <param name="player">UIにプレイヤー情報を渡す</param>
    /// <param name="collectItemObserver">UIに収集アイテム情報を渡す</param>
    PlayGameProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<CollectItemObserver> const collectItemObserver);
    /// <summary>
    /// UIとタイマーの解放
    /// </summary>
    ~PlayGameProcess();
    /// <summary>
    /// 遊んでいるときの更新
    /// </summary>
    /// <param name="collectObserver">収集アイテムの残り数を教えてもらう</param>
    void Update(std::weak_ptr<CollectItemObserver> const collectObserver);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const;
    /// <summary>
    /// ゲーム部分の処理の終了
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const
    {
        return isEndProcess;
    };
    /// <summary>
    /// ゲームの残り時間タイマーを渡す
    /// </summary>
    /// <returns> ゲームの残り時間タイマーを渡す</returns>
    std::shared_ptr<Timer> GetGameTimer();
    
private:
    //制限時間のタイマー
    std::shared_ptr<StopTimer> timer;
    //遊んでいるときのUI
    GamePlayUI* playUI;
    //処理終了フラグ
    bool isEndProcess = false;
    //最初の更新フラグ
    bool isFirstUpdate = true;
};