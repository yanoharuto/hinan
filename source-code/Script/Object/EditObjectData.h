#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <rapidjson.h>
#include <document.h>
#include "writer.h"
#include "DxLib.h"
//初期化データの種類の数
#define EDIT_ARRANGEMENT_DATA_KIND_NUM 6
//Jsonで使うオブジェクト識別番号の文字列
constexpr char OBJNUM_MEMBER[] = "objNum";
//収集アイテムが何個取られたときに出てくるかを表すパラメーター
constexpr char COLLECTNUM_MEMBER[] = "collectNum";
//X座標
constexpr char POSX_MEMBER[] = "x";
//Z座標
constexpr char POSZ_MEMBER[] = "z";
//X方向
constexpr char DIRX_MEMBER[] = "dirX";
//Z方向
constexpr char DIRZ_MEMBER[] = "dirZ";
//上記の要素をまとめた配列
constexpr char ARRANGEDATA_MEMBER[] = "arrangeData";
/// <summary>
/// 保存したい情報の種類
/// </summary>
enum class EditArrangementDataKind
{
    //保存するオブジェクトの種類
    objectKindNum = 0,
    //出てくるタイミングの収集アイテムの数
    appearCollectNum = 1,
    //初期座標X
    positionX = 2,
    //初期座標Y
    positionZ = 3,
    //初期向きX
    directionX = 4,
    //初期向きZ
    directionZ = 5,
};
/// <summary>
/// 保存したい情報
/// </summary>
struct PlacementData
{
    //オブジェクトの種類
    int objKind = 0;
    //何番目の収集アイテムのタイミングか
    int collectNum = 0;
    //ポジションX
    float posX = 0;
    //ポジションZ
    float posZ = 0;
    //方向X
    float dirX = 0;
    //方向Z
    float dirZ = 0;
    /// <summary>
    /// 保存するためにJsonのValueに登録して返す
    /// </summary>
    /// <param name="allocator">Jsonのアロケーター</param>
    /// <returns></returns>
    void SetEditPlaceData(rapidjson::Value& objValue, rapidjson::Document::AllocatorType& allocator) const
    {
        objValue.AddMember(OBJNUM_MEMBER, objKind, allocator);
        objValue.AddMember(COLLECTNUM_MEMBER, collectNum, allocator);
        objValue.AddMember(POSX_MEMBER, posX, allocator);
        objValue.AddMember(POSZ_MEMBER, posZ, allocator);
        objValue.AddMember(DIRX_MEMBER, dirX, allocator);
        objValue.AddMember(DIRZ_MEMBER, dirZ, allocator);
    }
    /// <summary>
    /// Jsonの値から変換して場所データにする
    /// </summary>
    /// <returns></returns>
    void ConversionJsonToPlacementData(const rapidjson::Value* objValue)
    {
        objKind = objValue->FindMember(OBJNUM_MEMBER)->value.GetInt();
        collectNum = objValue->FindMember(COLLECTNUM_MEMBER)->value.GetInt();
        posX = objValue->FindMember(POSX_MEMBER)->value.GetFloat();
        posZ = objValue->FindMember(POSZ_MEMBER)->value.GetFloat();
        dirX = objValue->FindMember(DIRX_MEMBER)->value.GetFloat();
        dirZ = objValue->FindMember(DIRZ_MEMBER)->value.GetFloat();
    }
};