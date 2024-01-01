#include <iostream>
#include <cassert>
#include <vector>
#include "EditLog.h"
#include "Utility.h"
#include "writer.h"
#include "JsonFileLoader.h"
EditLog::EditLog(std::string logFileName)
{
    fileName = logFileName;
}
/// <summary>
/// placeDataを後ろからprevNum番目に追加
/// </summary>
/// <param name="prevNum">戻りたい場所</param>
/// <param name="totalEdit">保存したいオブジェクトの総数</param>
/// <param name="nowEditNum">編集番号</param>
/// <param name="placeData">保存したい情報</param>
void EditLog::SaveEditDataLog(int prevNum, int totalEdit,int nowEditNum, PlacementData placeData)
{
    auto json = new JsonFileLoader(fileName+Utility::JSON_FILE,schemaStr);
    if (json->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
    {
        //ドキュメント作成
        rapidjson::Document jsonDoc;
        jsonDoc.SetObject();
        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
        rapidjson::Value myArray(rapidjson::kArrayType);
        const rapidjson::Value& list = json->GetLoadArray("arrangeData");
        
        //過去のログも再度書き込む
        for (auto array = list.Begin(); array != list.End(); array++)
        {
            myArray.PushBack(GetEditPlaceData(array,allocator), allocator);
        }
        myArray.PushBack(GetEditPlaceData(totalEdit, nowEditNum, placeData, allocator), allocator);

        //編集内容をsaveFileNameのファイルに書き込む
        jsonDoc.AddMember("arrangeData", myArray, allocator);
        
        //ファイルの中身を全部消した状態で書き込む
        std::ofstream ofs(fileName + Utility::JSON_FILE);
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        jsonDoc.Accept(writer);
        SAFE_DELETE(json);
    }
}
/// <summary>
/// ひとつ前の状態に戻せるか
/// </summary>
/// <returns></returns>
bool EditLog::CanBackPrevState(int prevNum) const
{
    auto json = new JsonFileLoader(fileName + Utility::JSON_FILE, schemaStr);
    if (json->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
    {
        //ドキュメント作成
        rapidjson::Document jsonDoc;
        jsonDoc.SetObject();
        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
        const rapidjson::Value& list = json->GetLoadArray("arrangeData");
        auto alocator = list.End() - prevNum;
        
        //一番最初の状態になっていないか
        return alocator!=list.Begin();
    }
    return false;
}

/// <summary>
/// ひとつ前に編集したものの情報を渡す
/// </summary>
/// <param name="prevNum"></param>
/// <returns></returns>
PlacementData EditLog::GetPrevEditData(int prevNum)
{
    auto json = new JsonFileLoader(fileName + Utility::JSON_FILE, schemaStr);
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    //配列にして詰め込む
    rapidjson::Value myArray(rapidjson::kArrayType);
    const rapidjson::Value& list = json->GetLoadArray("arrangeData");
    auto array = list.End();
    array -= prevNum;
    totalNum = array->FindMember("totalEdit")->value.GetInt();
    editNum = array->FindMember("editNum")->value.GetInt();
    PlacementData editPlaceData;
    editPlaceData.objKind = array->FindMember("objNum")->value.GetInt();
    editPlaceData.collectNum = array->FindMember("collectNum")->value.GetInt();
    editPlaceData.posX = array->FindMember("x")->value.GetFloat();
    editPlaceData.posZ = array->FindMember("z")->value.GetFloat();
    editPlaceData.dirX = array->FindMember("dirX")->value.GetFloat();
    editPlaceData.dirZ = array->FindMember("dirZ")->value.GetFloat();
    return editPlaceData;
}
/// <summary>
/// 保存するためにJsonのValueに登録して返す
/// </summary>
/// <param name="totalEdit">編集総数</param>
/// <param name="editNum">編集配列番号</param>
/// <param name="editData">編集情報</param>
/// <param name="allocator">Jsonのアロケーター</param>
/// <returns></returns>
rapidjson::Value EditLog::GetEditPlaceData(int totalEdit, int editNum, PlacementData editData, rapidjson::Document::AllocatorType& allocator) const
{
    //編集内容をメンバに登録
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember("totalEdit", totalEdit, allocator);
    objValue.AddMember("editNum", editNum, allocator);
    objValue.AddMember("objKind", editData.objKind, allocator);
    objValue.AddMember("collectNum", editData.collectNum, allocator);
    objValue.AddMember("x", editData.posX, allocator);
    objValue.AddMember("z", editData.posZ, allocator);
    objValue.AddMember("dirX", editData.dirX, allocator);
    objValue.AddMember("dirZ", editData.dirZ, allocator);
    return objValue;
}  
/// <summary>
/// 抜き取るためにJsonのValueに登録して返す
/// </summary>
/// <param name="editData">編集情報</param>
/// <param name="allocator">Jsonのアロケーター</param>
/// <returns></returns>
rapidjson::Value EditLog::GetEditPlaceData(const rapidjson::Value* editData, rapidjson::Document::AllocatorType& allocator) const
{
    //編集内容をメンバに登録
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember("totalEdit", editData->FindMember("totalEdit")->value.GetInt(), allocator);
    objValue.AddMember("editNum", editData->FindMember("editNum")->value.GetInt(), allocator);
    objValue.AddMember("objNum", editData->FindMember("objNum")->value.GetInt(), allocator);
    objValue.AddMember("collectNum", editData->FindMember("collectNum")->value.GetInt(), allocator);
    objValue.AddMember("x", editData->FindMember("x")->value.GetFloat(), allocator);
    objValue.AddMember("z", editData->FindMember("z")->value.GetFloat(), allocator);
    objValue.AddMember("dirX", editData->FindMember("dirX")->value.GetFloat(), allocator);
    objValue.AddMember("dirZ", editData->FindMember("dirZ")->value.GetFloat(), allocator);
    return objValue;
}
