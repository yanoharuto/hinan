#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include "EditObjectData.h"
#include "InitObjKind.h"
class StageDataEditor;

constexpr int STAGE_WIDTH_VALUE = 6000;
using namespace ObjectInit;
/// <summary>
/// 編集したものをファイルに保存する
/// </summary>
class EditDataSaver
{
public:
    EditDataSaver() {};
    ~EditDataSaver() {};
    /// <summary>
    /// 編集した情報を保存する
    /// </summary>
    /// <param name="placeVector">編集した情報を纏めたVector</param>
    void SaveEditData(std::string fileName,std::vector<PlacementData> placeVector);
private:
    /// <summary>
    /// 編集した情報を保存する
    /// </summary>
    /// <param name="editData">編集した情報</param>
    /// <param name="saveFileName">保存するファイル</param>
    void SaveEditDataForCSV(std::string fileName,std::vector<PlacementData> editData)const;
    /// <summary>
    /// 引数の編集情報をJsonに保存できるようにする
    /// </summary>
    /// <param name="editData">編集情報</param>
    /// <param name="allocator">編集のために必要なallocator</param>
    /// <returns>Jsonに保存できるようにしたもの</returns>
    rapidjson::Value GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    /// <summary>
    /// Json形式で保存する
    /// </summary>
    /// <param name="editData">編集したい情報纏め</param>
    /// <param name="saveFileName">保存先のファイルの名前</param>
    void SaveEditDataForJSON(std::string fileName, std::vector<PlacementData> editData)const;
    //ステージ名
    const std::string stageFilePath = "data/Json/StageData/Stage4/stageData";
};