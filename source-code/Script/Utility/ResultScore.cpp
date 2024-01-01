#include <fstream>
#include <sstream>
#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "PlayerObserver.h"
#include "StageDataManager.h"
#include "ScoreRecordWriter.h"
#include "StopTimer.h"
//収集アイテムゲットボーナス
const int ResultScore::getCollectBonus = 500;
//残り時間のボーナス
const int ResultScore::clearTimeBonus = 50;
/// <summary>
/// ゲームクリアしたときのスコアを計算する
/// </summary>
/// <param name="player">集めたアイテムの数を教えてもらう</param>
/// <param name="timer">クリアタイムを所得する</param>
ResultScore::ResultScore(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer)
{
    //残り時間
    int scoreTime = timer.lock()->IsOverLimitTime() ? 0 : static_cast<int>(timer.lock()->GetRemainingTime());
    //スコアを計算して確定させる
    FixScore(scoreTime, player.lock()->GetCollectCount());
}
/// <summary>
/// スコア所得
/// </summary>
/// <param name="scoreKind">欲しいスコアの種類</param>
/// <returns>引数の種類のスコア量</returns>
int ResultScore::GetScore(ScoreKind scoreKind)
{
    switch (scoreKind)//引数の種類のスコアの量を返す
    {
    case ResultScore::ScoreKind::timeBonus:
        return timeScore;
        break;
    case ResultScore::ScoreKind::collectBonus:
        return collectScore;
        break;
    case ResultScore::ScoreKind::total:
        return timeScore + collectScore;
        break;
    default:
        return 0;
        break;
    }
}
/// <summary>
/// スコアの倍率を所得
/// </summary>
/// <param name="scoreKind">欲しいスコアの種類</param>
/// <returns>引数のスコアの倍率</returns>
int ResultScore::GetScoreBonus(ScoreKind scoreKind)
{
    switch (scoreKind)//引数の種類のスコアの倍率を返す
    {
    case ResultScore::ScoreKind::timeBonus:
        return clearTimeBonus;
        break;
    case ResultScore::ScoreKind::collectBonus:
        return getCollectBonus;
        break;
    default:
        return -1;
        break;
    }
}
/// <summary>
/// ハイスコアが更新されたか
/// </summary>
/// <returns>ハイスコアが更新されていたらTrue</returns>
bool ResultScore::IsUpdateHiScore()
{
    return isUpdateHighScore;
}
/// <summary>
/// ステージのハイスコアを文字列にしたもの
/// </summary>
/// <returns>ステージのハイスコアを文字列にしたもの</returns>
int ResultScore::GetUpdateScore() const
{
    return updateScore;
}
/// <summary>
/// スコアを確定させる
/// </summary>
/// <param name="remainingTime">クリアタイム所得</param>
/// <param name="getCollectNum">プレイヤーの所得した収集アイテム数</param>
void ResultScore::FixScore(int remainingTime, int getCollectNum)
{
    //スコアの記録線引き
    StageDataManager::ScoreBorder score = StageDataManager::GetScoreBorder();
    //制限時間を超過してたら0
    timeScore = remainingTime * clearTimeBonus; 
    //収集アイテムを取ってたらボーナス
    collectScore = getCollectNum * getCollectBonus;
    //得点
    updateScore = timeScore + collectScore;
    //↑二つが過去のハイスコアより多かったらTrue
    isUpdateHighScore = updateScore > score.highScore;
    //スコアが更新されたなら
    if (updateScore > score.third)
    {
        ScoreRecordWriter* scoreRecordWriter = StageDataManager::GetScoreRecordWriter();
        //スコアの記録を更新
        scoreRecordWriter->UpdateScoreRecord(this);
        SAFE_DELETE(scoreRecordWriter);
    }
}