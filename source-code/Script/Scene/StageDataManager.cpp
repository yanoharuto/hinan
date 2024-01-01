#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "JsonFileLoader.h"
#include "StageSelect.h"
#include "StopTimer.h"
#include "ResultScore.h"
#include "ScoreRecordWriter.h"
//ステージのファイルの名前
std::string StageDataManager::fileAddres = "-1";
//各ステージのデータのスキーマ
const std::string StageDataManager::stageDataSchema = "stageDataSchema.json";
//各ステージのスコアのスキーマ
const std::string StageDataManager::scoreDataSchema = "scoreDataSchema.json";
//配置に必要なスキーマ
const std::string StageDataManager::arrangeDataSchema = "arrangeDataSchema.json";
//ステージのデータ
std::vector<std::string> StageDataManager::dataVector;
//ステージの横幅
int StageDataManager::stageWidth;
//ステージの縦幅
int StageDataManager::stageLength;

StageDataManager::StageDataManager()
{
}
/// <summary>
/// 所得するステージの変更
/// </summary>
/// <param name="select">今選んでいるステージを教えてもらう</param>
void StageDataManager::ChangeStageData(StageSelect* const select)
{
    if (dataVector.empty())
    {
        LoadStageData();
    }
    //選んでいるステージのアドレスを保存
    fileAddres = dataVector[select->GetSelectStageNum()];

    stageWidth = STR_TO_I(GetSelectStageData(StageData::width));

    stageLength = STR_TO_I(GetSelectStageData(StageData::length));
}
/// <summary>
/// ステージの数
/// </summary>
/// <returns></returns>
int StageDataManager::GetStageTotalNumber()
{
    return dataVector.size();
}

/// <summary>
/// 各ステージのデータを取ってくる
/// </summary>
/// <param name="dataKind">欲しいステージのデータの種類</param>
/// <returns>ステージの制限時間や縦幅横幅、初期位置の入ったファイルのパスなどが返ってくる</returns>
std::string StageDataManager::GetSelectStageData(StageData dataKind)
{
    std::vector<std::string> setStageInitDataVec;
    if (IsExistJsonFile())
    {
        auto fileLoader = new JsonFileLoader(fileAddres, stageDataSchema);
        setStageInitDataVec.push_back(std::to_string(fileLoader->GetLoadInt("width")));
        setStageInitDataVec.push_back(std::to_string(fileLoader->GetLoadInt("length")));
        setStageInitDataVec.push_back(fileLoader->GetLoadString("editFilePath"));
        setStageInitDataVec.push_back(std::to_string(fileLoader->GetLoadInt("gameTime")));
        setStageInitDataVec.push_back(fileLoader->GetLoadString("stageScoreFilePath"));
    }
    else
    {
        //今選択中のステージの情報を所得
        auto fileLoader = new CSVFileLoader(fileAddres);
        setStageInitDataVec = fileLoader->GetStringData();
        SAFE_DELETE(fileLoader);
    }
    //引数の情報を返す
    return setStageInitDataVec[CAST_I(dataKind)];
}
/// <summary>
/// 遊ぶステージのスコアのボーダーラインを返す
/// </summary>
/// <returns>現在遊んでいるステージのスコアの線引きを纏めたもの</returns>
StageDataManager::ScoreBorder StageDataManager::GetScoreBorder()
{
    ScoreBorder scoreBorder = {};//ステージのスコアの線引き
    std::vector<std::string> scoreStrInfoVec;
    if (IsExistJsonFile())//jsonで読み込む
    {
        auto fileLoader = new JsonFileLoader(GetSelectStageData(StageData::stageScoreFilePath), scoreDataSchema);
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(GOLDSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(SILVERSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(BROWNZESCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(HIGHSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(SECONDSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(THIRDSCORE_MEMBER)));
    }
    else//ｃｓｖで読み込む
    {
        auto fileLoader = new CSVFileLoader(GetSelectStageData(StageData::stageScoreFilePath));
        //ステージ情報文字列コンテナ
        scoreStrInfoVec = fileLoader->GetStringData();
        SAFE_DELETE(fileLoader);
    }
    //所得
    scoreBorder.gold = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::goldScore)]);
    scoreBorder.silver = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::silverScore)]);
    scoreBorder.bronze = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::bronzeScore)]);
    scoreBorder.highScore = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::highScore)]);
    scoreBorder.second = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::secondScore)]);
    scoreBorder.third = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::thirdScore)]);
    return scoreBorder;
}
/// <summary>
/// 初期位置の文字列情報
/// </summary>
/// <returns>初期位置の書いてあるファイルのパス</returns>
std::string StageDataManager::GetPlaceStrData()
{
    ///今選択しているステージの初期位置の入ったファイルのパス
    std::string selectStageFirstPlaceFilePath;
    //各オブジェクトの初期位置のファイルまでのパスを所得
    selectStageFirstPlaceFilePath = GetSelectStageData(StageData::editFilePath);
    return selectStageFirstPlaceFilePath;
}
/// <summary>
/// ゲームの制限時間のタイマーを作成
/// </summary>
/// <returns>ゲーム制限時間タイマー</returns>
std::shared_ptr<StopTimer> StageDataManager::CreateGameTimer()
{
    double gameLimitTime = STR_TO_F(GetSelectStageData(StageData::gameTime));
    return std::make_shared<StopTimer>(gameLimitTime);
}
/// <summary>
/// スコアの記録更新役を渡す
/// </summary>
/// <returns>スコアの記録更新役</returns>
ScoreRecordWriter* StageDataManager::GetScoreRecordWriter()
{
    return new ScoreRecordWriter(GetSelectStageData(StageData::stageScoreFilePath),GetScoreBorder());
}
/// <summary>
/// 全ステージ一覧を読み取る
/// </summary>
void StageDataManager::LoadStageData()
{
    dataVector = GetAssetList(AssetList::stageData);
    fileAddres = dataVector[0];//とりあえず先頭のステージを渡す
}
