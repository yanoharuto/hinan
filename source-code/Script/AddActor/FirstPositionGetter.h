#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "Object.h"

/// <summary>
/// 初期位置をファイルからとってきて変換する
/// </summary>
class FirstPositionGetter
{
public:
    /// <summary>
    /// 選択されているステージのオブジェクトの初期位置を渡す
    /// </summary>
    /// <param name="kind">オブジェクトの種類によって読み込む情報を変更する</param>
    /// <returns>そのオブジェクトの位置をまとめたコンテナ</returns>
    static std::vector<PlacementData> GetPlaceData(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 引数のファイルから読み取って初期位置を渡す
    /// </summary>
    /// <param name="fileName">配置情報ファイルの名前</param>
    /// <returns>配置情報のコンテナ</returns>
    static std::vector<PlacementData> GetPlaceData(std::string fileName);
    /// <summary>
    /// 選択されたステージの初期位置を渡す
    /// </summary>
    /// <returns>配置情報のコンテナ</returns>
    static std::vector<PlacementData> GetPlaceData();
private:
    /// <summary>
    /// CSVで所得した初期位置を構造体に変換
    /// </summary>
    /// <param name="objNum">抜き取りたいオブジェクトの番号</param>
    /// <param name="placeStrData">全体の初期位置文字列データ</param>
    /// <returns></returns>
    static std::vector<PlacementData> CSVConvertFirstData(int objNum,std::string placeStrData);
    /// <summary>
    /// Csvで所得した初期位置を構造体に変換
    /// </summary>
    /// <param name="placeStrData">全体の初期位置文字列データ</param>
    /// <returns></returns>
    static std::vector<PlacementData> CSVConvertFirstData(std::string placeStrData);
    /// <summary>
    /// Jsonで所得した初期位置を構造体に変換
    /// </summary>
    /// <param name="objNum">抜き取りたいオブジェクトの番号</param>
    /// <param name="placeStrData">全体の初期位置文字列データ</param>
    /// <returns></returns>
    static std::vector<PlacementData> JsonConvertFirstData(int objNum,std::string placeStrData);
    /// <summary>
    /// Jsonで所得した初期位置を構造体に変換
    /// </summary>
    /// <param name="placeStrData">全体の初期位置文字列データ</param>
    /// <returns></returns>
    static std::vector<PlacementData> JsonConvertFirstData(std::string placeStrData);
    //Jsonのスキーマのパス
    static std::string schemaPath;
};