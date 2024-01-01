#pragma once
#include "EditObjectData.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
/// <summary>
/// 編集したものを元に戻せるように記録する
/// </summary>
class EditLog
{
public:
    EditLog(std::string logFileName);
    /// <summary>
    /// placeDataを後ろからprevNum番目に追加
    /// </summary>
    /// <param name="prevNum">戻りたい場所</param>
    /// <param name="totalEdit">保存したいオブジェクトの総数</param>
    /// <param name="nowEditNum">編集番号</param>
    /// <param name="placeData">保存したい情報</param>
    void SaveEditDataLog(int prevNum,int totalEdit,int nowEditNum, PlacementData placeData);
    /// <summary>
    /// ひとつ前の状態に戻せるか
    /// </summary>
    /// <returns></returns>
    bool CanBackPrevState(int prevNum)const;
    /// <summary>
    /// ひとつ前に編集したものの情報を渡す
    /// </summary>
    /// <param name="prevNum"></param>
    /// <returns></returns>
    PlacementData GetPrevEditData(int prevNum);
    /// <summary>
    /// ひとつ前に編集したオブジェクトの配列番号
    /// </summary>
    /// <returns></returns>
    int GetEditNum()const { return editNum; };
    /// <summary>
    /// 編集したオブジェクトの合計数
    /// </summary>
    /// <returns></returns>
    int GetTotalNum()const { return totalNum; };
private:
    /// <summary>
    /// 保存するためにJsonのValueに登録して返す
    /// </summary>
    /// <param name="totalEdit">編集総数</param>
    /// <param name="editNum">編集配列番号</param>
    /// <param name="editData">編集情報</param>
    /// <param name="allocator">Jsonのアロケーター</param>
    /// <returns></returns>
    rapidjson::Value GetEditPlaceData(int totalEdit,int editNum,PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    /// <summary>
    /// 抜き取るためにJsonのValueに登録して返す
    /// </summary>
    /// <param name="editData">編集情報</param>
    /// <param name="allocator">Jsonのアロケーター</param>
    /// <returns></returns>
    rapidjson::Value GetEditPlaceData(const rapidjson::Value* editData, rapidjson::Document::AllocatorType& allocator)const;
    //スキーマのパス
    const std::string schemaStr = "data/Json/Schema/editLogData.json";
    //ファイルのパス
    std::string fileName;
    // ひとつ前に編集したオブジェクトの配列番号
    int editNum = 0;
    // 編集したオブジェクトの合計数
    int totalNum = 0;
};