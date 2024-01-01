#pragma once
#include <memory>
class MouseInput;
//最短タイムリミット
constexpr int MIN_TIME_LIMIT = 30;
constexpr int STAGE_WIDTH_VALUE = 6000;
/// <summary>
/// 制限時間の変更を行う
/// </summary>
class StageTimeLimitEditor
{
public:
    StageTimeLimitEditor() {};
    ~StageTimeLimitEditor() {};
    /// <summary>
    /// 制限時間の書き換え
    /// </summary>
    void SaveLimitTime();
    /// <summary>
    /// 制限時間の変更
    /// </summary>
    void ChangeTimeLimit(std::weak_ptr<MouseInput> mouse);
    /// <summary>
    /// このステージのタイムリミット
    /// </summary>
    /// <returns></returns>
    int GetTimeLimit()const { return timeLimit; };
private:
    //タイムリミット
    int timeLimit = MIN_TIME_LIMIT;
    //編集ファイル置き場
    const std::string editFilePath = "data/Json/StageData/Stage4/editData";
    //編集内容を保存するファイル名
    const char editFIle[41] = "data/Json/StageData/Stage4/editData.json";
    //スコアを保存するファイル名
    const char scoreFile[42] = "data/Json/StageData/Stage4/scoreData.json";
};

