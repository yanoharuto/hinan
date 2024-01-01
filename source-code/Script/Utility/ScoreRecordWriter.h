#pragma once
#include <fstream>
#include "StageDataManager.h"
class ResultScore;
/// <summary>
/// スコアを更新してファイルに書き移す
/// </summary>
class ScoreRecordWriter
{
public:
    /// <summary>
    /// スコアの記録を所得
    /// </summary>
    /// <param name="filePath">スコアのファイルのパス</param>
    /// <param name="scoreBorder">そのステージのスコアの記録の線引き</param>
    ScoreRecordWriter(std::string filePath,StageDataManager::ScoreBorder scoreBorder);
    /// <summary>
    /// スコアの記録の更新
    /// </summary>
    /// <param name="score">現在遊んでいるステージの記録を教えてもらう</param>
    void UpdateScoreRecord(ResultScore* const score);
private:
    //遊んでいるステージのスコアの記録の線引き
    StageDataManager::ScoreBorder border;
    //borderから文字列に変換した
    std::string borderString;
    //記録すファイルのパス
    std::string scoreRecordFilePath;
};

