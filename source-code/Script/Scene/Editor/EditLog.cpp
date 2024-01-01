#include "EditLog.h"
#include "Utility.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include "istreamwrapper.h"
#include "JsonFileLoader.h"
/// <summary>
/// 編集するファイルの名前と編集総数を保存　
/// </summary>
/// <param name="logFileName">ファイルの名前</param>
/// <param name="firstTotalEditNum">編集総数</param>
EditLog::EditLog(std::string logFileName, int firstTotalEditNum)
    :JsonWriter(logFileName)
{
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    rapidjson::Value myArray(rapidjson::kArrayType);
    //編集内容をsaveFileNameのファイルに書き込む
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);
    //ファイルの中身を全部消した状態で書き込む
    Write(&jsonDoc);
    firstTotalNum = firstTotalEditNum;
}
/// <summary>
/// placeDataを後ろからprevNum番目に追加
/// </summary>
/// <param name="prevNum">戻りたい場所</param>
/// <param name="totalEdit">保存したいオブジェクトの総数</param>
/// <param name="nowEditNum">編集番号</param>
/// <param name="placeData">保存したい情報</param>
void EditLog::SaveEditDataLog(int prevNum, int totalEdit, int nowEditNum, PlacementData placeData)
{
    auto json = new JsonFileLoader(fileName, schemaStr);
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    //読み込んだ内容を譲渡
    rapidjson::Value myArray(rapidjson::kArrayType);
    json->MoveValue(myArray,ARRANGEDATA_MEMBER);
    //過去のデータをさかのぼっていた時に記録したら
    if (!myArray.Empty() && prevNum != 0)
    {
        myArray.Erase(myArray.End() - prevNum, myArray.End());//さかのぼったところまで保存
    }
    //追記したいものを追加
    myArray.PushBack(GetEditPlaceData(totalEdit, nowEditNum, placeData, allocator), allocator);

    //編集内容をsaveFileNameのファイルに書き込む
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);

    //ファイルの中身を全部消した状態で書き込む
    Write(&jsonDoc);
    SAFE_DELETE(json);
}
/// <summary>
/// ひとつ前の状態に戻せるか
/// </summary>
/// <param name="prevNum">戻りたい場所</param>
/// <returns>戻れるかどうか</returns>
bool EditLog::CanBackPrevState(int prevNum) const
{
    auto json = new JsonFileLoader(fileName , schemaStr);
    if (json->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
    {
        const rapidjson::Value& list = json->GetLoadArray(ARRANGEDATA_MEMBER);
        //遡れないならfalse
        return prevNum < list.Size();
    }
    return false;
}
/// <summary>
/// 再編集の時のLogを反映させたとき記録を入れ替える
/// </summary>
/// <param name="prevNum">入れ替え先</param>
/// <param name="editData">入れ替え前のデータ</param>
/// <param name="placeData">入れ替え後のデータ</param>
void EditLog::UpdateReEditData(int prevNum,EditData editData, PlacementData placeData)
{
    //再編集の情報と入れ替えたいときのみ
    if (editData.editAction != EditActionKind::reEdit)return;

    auto json = new JsonFileLoader(fileName, schemaStr);
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    //読み込んだ内容を譲渡
    rapidjson::Value myArray(rapidjson::kArrayType);
    json->MoveValue(myArray, ARRANGEDATA_MEMBER);
    //再編集した場合、前に戻ったり先に戻ったりした場合、入れ替える
    if (!myArray.Empty())
    {
        prevNum = myArray.Size() - prevNum - 1;   
        myArray[prevNum].FindMember(OBJNUM_MEMBER)->value = placeData.objKind;
        myArray[prevNum].FindMember(COLLECTNUM_MEMBER)->value = placeData.collectNum;
        myArray[prevNum].FindMember(POSX_MEMBER)->value = placeData.posX;
        myArray[prevNum].FindMember(POSZ_MEMBER)->value = placeData.posZ;
        myArray[prevNum].FindMember(DIRX_MEMBER)->value = placeData.dirX;
        myArray[prevNum].FindMember(DIRZ_MEMBER)->value = placeData.dirZ;
    }
    //編集内容をsaveFileNameのファイルに書き込む
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);

    //ファイルの中身を全部消した状態で書き込む
    Write(&jsonDoc);
    SAFE_DELETE(json);
}
/// <summary>
/// ひとつ前に編集したものの情報を渡す
/// </summary>
/// <param name="prevNum">戻りたい段階数 0なら一番最後のログを所得　負の数はない</param>
/// <returns></returns>
EditLog::EditData EditLog::GetPrevEditData(int prevNum)
{
    auto json = new JsonFileLoader(fileName, schemaStr);//ログをさかのぼる
    auto& list = json->GetLoadArray(ARRANGEDATA_MEMBER);
    auto arrayValue = list.End() - prevNum - 1;

    //ログに残したオブジェクトの情報
    EditData editPlaceData;
    editPlaceData.data.ConversionJsonToPlacementData(arrayValue);
    editPlaceData.editNum = arrayValue->FindMember(EDIT_MEMBER)->value.GetInt();
    //編集の総量をひとつ前と比較
    int editNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();
    //ひとつ前の編集総数　初期値はNewした時の初期編集総数
    int prevTotalNum = firstTotalNum;
    //リストの先頭じゃないなら編集総数を所得
    if (arrayValue != list.Begin())
    {
        arrayValue--;
        prevTotalNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();
    }
    editPlaceData.editAction = EditActionKind::addData;//新規作成されたデータを所得
    if (editNum == prevTotalNum)//再編集前の情報を所得
    {
        editPlaceData.editAction = EditActionKind::reEdit;
        editPlaceData.data.ConversionJsonToPlacementData(arrayValue);
    }
    else if (editNum < prevTotalNum)//削除されたデータを所得
    {
        editPlaceData.editAction = EditActionKind::deleteData;
    }
    SAFE_DELETE(json);
    return editPlaceData;
}
/// <summary>
/// ひとつ前の状態のときに一つ先の状態に戻す
/// </summary>
/// <param name="prevNum">戻りたい段階数 0なら一番最後のログを所得　負の数はない</param>
/// <returns></returns>
EditLog::EditData EditLog::GetStepEditData(int prevNum)
{
    auto json = new JsonFileLoader(fileName, schemaStr);//ログをさかのぼる
    auto& list = json->GetLoadArray(ARRANGEDATA_MEMBER);
    auto arrayValue = list.End() - prevNum - 1;
    //ログに残したオブジェクトの情報
    EditData editPlaceData;
    editPlaceData.data.ConversionJsonToPlacementData(arrayValue);
    editPlaceData.editNum = arrayValue->FindMember(EDIT_MEMBER)->value.GetInt();
    //編集の総量をひとつ先と比較
    int editNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();    
    //復元先の編集総数
    int destinationTotalNum = firstTotalNum;
    //リストの先頭じゃないなら編集総数を所得
    if (arrayValue != list.Begin())
    {
        arrayValue--;
        destinationTotalNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();
    }
    editPlaceData.editAction = EditActionKind::deleteData;//少ないなら削除したものの情報を所得

    //先のデータの方が多いなら追加したものの情報を所得
    if (editNum > destinationTotalNum)
    {
        editPlaceData.editAction = EditActionKind::addData;
    }
    else if (editNum == destinationTotalNum)//同じなら再編集後の情報を所得
    {
        editPlaceData.editAction = EditActionKind::reEdit;
    }
    SAFE_DELETE(json);
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
    objValue.AddMember(TOTALNUM_MEMBER, totalEdit, allocator);
    objValue.AddMember(EDIT_MEMBER, editNum, allocator);
    editData.SetEditPlaceData(objValue,allocator);
    return objValue;
}  