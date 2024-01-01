#include <iostream>
#include <cassert>
#include <vector>
#include "EditDataSaver.h"
#include "Utility.h"
#include "writer.h"
#include "StageDataEditor.h"

/// <summary>
/// 編集した情報を保存する
/// </summary>
/// <param name="limitTime">制限時間</param>
/// <param name="placeVector">編集した情報を纏めたVector</param>
void EditDataSaver::SaveEditData(std::string fileName, std::vector<PlacementData> placeVector)
{
    SaveEditDataForJSON(fileName,placeVector);
}

/// <summary>
/// 編集した情報を保存する
/// </summary>
/// <param name="editData">編集した情報</param>
/// <param name="saveFileName">保存するファイル</param>
void EditDataSaver::SaveEditDataForCSV(std::string fileName, std::vector<PlacementData> editData) const
{
    //配置した収集アイテムを保存
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        std::ofstream writing_file;
        auto data = editData[i];
        // ファイルを開いて
        writing_file.open(fileName + Utility::CSV_FILE, std::ios::app);
        //区切り文字
        std::string colon = ",";
        //オブジェクトの種類と
        writing_file << std::to_string(data.objKind) + colon << std::endl;
        //何番目の収集アイテムの時か
        writing_file << std::to_string(data.collectNum) + colon << std::endl;
        //位置
        writing_file << std::to_string(data.posX) + colon << std::endl;
        writing_file << std::to_string(data.posZ) + colon << std::endl;
        //向き
        writing_file << std::to_string(data.dirX) + colon << std::endl;
        writing_file << std::to_string(data.dirZ) + colon << std::endl;
        writing_file.close();
    }
}
/// <summary>
/// 引数の編集情報をJsonに保存できるようにする
/// </summary>
/// <param name="editData">編集情報</param>
/// <param name="allocator">編集のために必要なallocator</param>
/// <returns>Jsonに保存できるようにしたもの</returns>
rapidjson::Value EditDataSaver::GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator) const
{
    //編集内容をメンバに登録
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember(OBJNUM_MEMBER, editData.objKind, allocator);
    objValue.AddMember(COLLECTNUM_MEMBER, editData.collectNum, allocator);
    objValue.AddMember(POSX_MEMBER, editData.posX, allocator);
    objValue.AddMember(POSZ_MEMBER, editData.posZ, allocator);
    objValue.AddMember(DIRX_MEMBER, editData.dirX, allocator);
    objValue.AddMember(DIRZ_MEMBER, editData.dirZ, allocator);
    return objValue;
}
/// <summary>
/// Json形式で保存する
/// </summary>
/// <param name="editData">編集したい情報纏め</param>
/// <param name="saveFileName">保存先のファイルの名前</param>
void EditDataSaver::SaveEditDataForJSON(std::string fileName, std::vector<PlacementData> editData)const
{
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    //配列にして詰め込む
    rapidjson::Value myArray(rapidjson::kArrayType);
    //配置した収集アイテムを保存
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        rapidjson::Value objValue;
        objValue.SetObject();
        editData[i].SetEditPlaceData(objValue, allocator);
        myArray.PushBack(objValue,allocator);
    }
    //編集内容をsaveFileNameのファイルに書き込む
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);
    //ファイルの中身を全部消した状態で書き込む
    std::ofstream ofs(fileName + Utility::JSON_FILE);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    jsonDoc.Accept(writer);
}