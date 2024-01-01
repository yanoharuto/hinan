#include <iostream>
#include <cassert>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include <fstream>
#include "StageTimeLimitEditor.h"
#include "MouseInput.h"
#include "writer.h"
#include "Utility.h"

/// <summary>
/// 制限時間の変更
/// </summary>
void StageTimeLimitEditor::ChangeTimeLimit(std::weak_ptr<MouseInput> mouse)
{
    timeLimit += mouse.lock()->GetWheelIncreaseValue();//ホイールが上に回したら1秒増える

    if (timeLimit < MIN_TIME_LIMIT)//最低タイムリミット
    {
        timeLimit = MIN_TIME_LIMIT;
    }
}

/// <summary>
/// 制限時間を保存する
/// </summary>
/// <param name="limitTime"></param>
void StageTimeLimitEditor::SaveLimitTime()
{
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    //編集内容をsaveFileNameのファイルに書き込む
    jsonDoc.AddMember("width", STAGE_WIDTH_VALUE, allocator);
    jsonDoc.AddMember("length", STAGE_WIDTH_VALUE, allocator);
    jsonDoc.AddMember("editFilePath", editFIle, allocator);
    jsonDoc.AddMember("gameTime", timeLimit, allocator);
    jsonDoc.AddMember("stageScoreFilePath", scoreFile, allocator);
    //ファイルの中身を全部消した状態で書き込む
    std::ofstream ofs(editFilePath + Utility::JSON_FILE);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    jsonDoc.Accept(writer);
}