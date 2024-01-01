#pragma once
#include <iostream>
#include <memory>
#define SCORE_KIND_NUM 4
class PlayerObserver;
class Timer;
/// <summary>
/// 最終的なスコアの保存役
/// </summary>
class ResultScore
{
public:
    /// <summary>
    /// ゲームクリアしたときのスコアを計算する
    /// </summary>
    /// <param name="player">集めたアイテムの数を教えてもらう</param>
    /// <param name="timer">クリアタイムを所得する</param>
    ResultScore(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer);
    //スコアの種類
    enum class ScoreKind
    {
        //残り時間ボーナス
        timeBonus = 0,
        //収集アイテムボーナス
        collectBonus = 1,
        //合計
        total = 2
    };
    /// <summary>
    /// スコア所得
    /// </summary>
    /// <param name="scoreKind">欲しいスコアの種類</param>
    /// <returns>引数のスコア量</returns>
    int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// スコアの倍率を所得
    /// </summary>
    /// <param name="scoreKind">欲しいスコアの種類</param>
    /// <returns>引数のスコアの倍率</returns>
    int GetScoreBonus(ScoreKind scoreKind);
    /// <summary>
    /// ハイスコアが更新されたか
    /// </summary>
    /// <returns>ハイスコアが更新されていたらTrue</returns>
    bool IsUpdateHiScore();
    /// <summary>
    /// ステージのハイスコアを文字列にしたもの
    /// </summary>
    /// <returns>ステージのハイスコアを文字列にしたもの</returns>
    int GetUpdateScore()const;
private:
    /// <summary>
    /// スコアを確定させる
    /// </summary>
    /// <param name="remainingTime">クリアタイム所得</param>
    /// <param name="getCollectNum">プレイヤーの所得した収集アイテム数</param>
    void FixScore(int remainingTime, int getCollectNum);
    //残り時間のスコア
    int timeScore = 0;
    //収集アイテムを集めたスコア
    int collectScore = 0;
    //ハイスコア更新フラグ
    bool isUpdateHighScore = false;
    //スコア記録更新したときのスコア
    int updateScore;
    //残り時間のボーナス
    static const int clearTimeBonus;
    //コインはボーナス
    static const int getCollectBonus;
};

