#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "DxLib.h"
#include "Object.h"
#include "AssetManager.h"
//Jsonで使うスコアのパラメータのメンバの名前
//ゴールドランク
constexpr char GOLDSCORE_MEMBER[] = "gold";
//シルバーランク
constexpr char SILVERSCORE_MEMBER[] = "silver";
//ブロンズランク
constexpr char BROWNZESCORE_MEMBER[] = "bronze";
//最高記録
constexpr char HIGHSCORE_MEMBER[] = "firstScore";
//二番目の記録
constexpr char SECONDSCORE_MEMBER[] = "secondScore";
//三番目の記録
constexpr char THIRDSCORE_MEMBER[] = "thirdScore";

class StageSelect;
class ResultScore;
class StopTimer;
class ScoreRecordWriter;
/// <summary>
/// 遊ぶステージのデータを渡す
/// </summary>
class StageDataManager :public AssetManager
{
public:
    /// <summary>
    /// ステージの情報管理者
    /// </summary>
    StageDataManager();
    struct ScoreBorder;
    /// <summary>
    /// 所得するステージの変更
    /// </summary>
    /// <param name="select">今選んでいるステージを教えてもらう</param>
    static void ChangeStageData(StageSelect* const select);
    /// <summary>
    /// ステージの総数
    /// </summary>
    /// <returns>ステージの総数が返ってくる</returns>
    static int GetStageTotalNumber();
    /// <summary>
    /// 遊ぶステージのスコアのボーダーラインを返す
    /// </summary>
    /// <returns>現在遊んでいるステージのスコアの線引きを纏めたもの</returns>
    static StageDataManager::ScoreBorder GetScoreBorder();
    /// <summary>
    /// 初期位置の初期位置の書いてあるファイルのパス文字列情報
    /// </summary>
    /// <returns>初期位置の書いてあるファイルのパス</returns>
    static std::string GetPlaceStrData();
    /// <summary>
    /// ゲームの制限時間のタイマーを作成
    /// </summary>
    /// <returns>ゲーム制限時間タイマー</returns>
    static std::shared_ptr<StopTimer> CreateGameTimer();
    /// <summary>
    /// スコアの記録更新役を渡す
    /// </summary>
    /// <returns>スコアの記録更新役</returns>
    static ScoreRecordWriter* GetScoreRecordWriter();
    /// <summary>
   /// ステージごとに設定しているデータ
   /// </summary>
    enum class StageData
    {
        //横幅
        width,
        //縦幅
        length,
        //障害物の位置のファイルパス
        editFilePath,
        //制限時間
        gameTime,
        //ステージのスコア
        stageScoreFilePath
    };
    /// <summary>
    /// スコアの線引き
    /// </summary>
    enum class StageScore
    {
        //一番目にいいスコア
        goldScore,
        //二番目にいいスコア
        silverScore,
        //三番目にいいスコア
        bronzeScore,
        //遊んだ中で最高スコア
        highScore,
        //二番目にいいスコア
        secondScore,
        //3番目にいいスコア
        thirdScore
    };
    /// <summary>
    /// スコアの階級
    /// </summary>
    struct  ScoreBorder
    {
        //一番目にいいスコア
        int gold;
        //二番目にいいスコア
        int silver;
        //三番目にいいスコア
        int bronze;
        //遊んだ中で最高スコア
        int highScore;
        //二番目にいいスコア
        int second;
        //3番目にいいスコア
        int third;
    };
private:

    /// <summary>
    /// 各ステージのデータを取ってくる
    /// </summary>
    /// <param name="dataKind">欲しいステージのデータの種類</param>
    /// <returns>ステージの制限時間や縦幅横幅、初期位置の入ったファイルのパスなどが返ってくる</returns>
    static std::string GetSelectStageData(StageData dataKind);
    /// <summary>
    /// 全ステージ一覧を読み取る
    /// </summary>
    static void LoadStageData();
    //ステージのデータ
    static std::vector<std::string> dataVector;
    //各ステージのデータのパス
    static std::string fileAddres;
    //幅
    static int stageWidth;
    //長さ
    static int stageLength;
    //各ステージのデータのスキーマ
    const static std::string stageDataSchema;
    //各ステージのスコアのスキーマ
    const static std::string scoreDataSchema;
    //配置情報のスキーマ
    const static std::string arrangeDataSchema;
};