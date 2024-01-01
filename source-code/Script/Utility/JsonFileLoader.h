#pragma once
#include <vector>
#include <rapidjson.h>
#include <string>
#include "document.h"
#include "istreamwrapper.h"
#include "schema.h"
#include "stringbuffer.h"
/// <summary>
/// Jsonファイル読み取りクラス
/// </summary>
class JsonFileLoader
{
public:
    /// <summary>
    /// Json形式のファイルを開く
    /// </summary>
    /// <param name="filePath">開きたいファイル</param>
    /// <param name="schemaFileName">開くファイルのSchema</param>
    JsonFileLoader(std::string filePath,std::string schemaFileName);
    /// <summary>
    /// Schemaと開きたいファイルが適応しているなら
    /// </summary>
    /// <returns>適応したならTrue</returns>
    bool IsAccept()const;
    /// <summary>
    /// integer型を読み取る
    /// </summary>
    /// <param name="dataName">読み取りたいメンバの名前</param>
    /// <returns>欲しいデータ</returns>
    int GetLoadInt(std::string dataName)const;
    /// <summary>
    /// 必要なfloat型を読み取る
    /// </summary>
    /// <param name="dataName">読み取りたいメンバの名前</param>
    /// <returns>取りたいデータ</returns>
    float GetLoadFloat(std::string dataName)const;
    /// <summary>
    /// 必要な文字列を読み取る
    /// </summary>
    /// <param name="dataName">読み取りたいメンバの名前</param>
    /// <returns>取りたいデータ</returns>
    std::string GetLoadString(std::string dataName)const;
    /// <summary>
    /// 必要な配列を読み取る
    /// </summary>
    /// <param name="dataName">欲しい配列の名前</param>
    /// <returns>rapidjson::Value型の配列</returns>
    const rapidjson::Value& GetLoadArray(std::string dataName)const;
    /// <summary>
    /// 読み取った内容をValueに移す
    /// </summary>
    /// <param name="value">移す先</param>
    /// <param name="dataName">移したい内容</param>
    void MoveValue(rapidjson::Value& value, std::string dataName);
private:
    //Schemaと開きたいファイルが適応しているなら
    bool isAccept;
    //読み取る状態
    rapidjson::Document loadDoc;
    //スキーマファイルまでのパス
    static std::string const jsonSchemaFilePath;
};