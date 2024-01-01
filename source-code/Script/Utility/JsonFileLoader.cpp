#include <fstream>
#include <iostream>
#include "JsonFileLoader.h"
//スキーマファイルまでのパス
std::string const JsonFileLoader::jsonSchemaFilePath = "data/Json/Schema/";
/// <summary>
/// Json形式のファイルを開く
/// </summary>
/// <param name="filePath">開きたいファイル</param>
/// <param name="schemaFileName">開くファイルのSchema</param>
JsonFileLoader::JsonFileLoader(std::string filePath, std::string schemaFileName)
{
    //スキーマから書き方を調べる
    std::ifstream schema_ifs(jsonSchemaFilePath + schemaFileName);
    rapidjson::IStreamWrapper schema_isw(schema_ifs);
    rapidjson::Document schema_doc;
    schema_doc.ParseStream(schema_isw);
    //読み取りたいデータファイルを開く
    std::ifstream ifs(filePath);
    rapidjson::IStreamWrapper isw(ifs);
    loadDoc.ParseStream(isw);
    //スキーマ通りの書き方か調べる
    rapidjson::SchemaDocument schema(schema_doc);
    rapidjson::SchemaValidator validator(schema);
    isAccept = loadDoc.Accept(validator);
    //失敗した
    if (!isAccept) {
        rapidjson::StringBuffer sb;
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);//リソースの場所をSBに渡す
        std::cout << "Invalid schema:" << sb.GetString() << std::endl;
        std::cout << "Invalid keyword:" << validator.GetInvalidSchemaKeyword() << std::endl;
    }
}
/// <summary>
/// Schemaと開きたいファイルが適応しているなら
/// </summary>
/// <returns>適応したならTrue</returns>
bool JsonFileLoader::IsAccept() const
{
    return isAccept;
}
/// <summary>
/// integer型を読み取る
/// </summary>
/// <param name="dataName">読み取りたいメンバの名前</param>
/// <returns>欲しいデータ</returns>
int JsonFileLoader::GetLoadInt(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetInt();
}
/// <summary>
/// float型
/// </summary>
/// <param name="dataName">読み取りたいデータ</param>
/// <returns>取りたいデータ</returns>
float JsonFileLoader::GetLoadFloat(std::string dataName)const
{
    return loadDoc[dataName.c_str()].GetFloat();
}
/// <summary>
/// 必要なデータ文字列を読み取る
/// </summary>
/// <param name="dataName">読み取りたいデータの名前</param>
/// <returns>取りたいデータ</returns>
std::string JsonFileLoader::GetLoadString(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetString();
}
/// <summary>
/// 必要な配列を読み取る
/// </summary>
/// <param name="dataName">欲しい配列の名前</param>
/// <returns>rapidjson::Value型の配列</returns>
const rapidjson::Value& JsonFileLoader::GetLoadArray(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetArray();
}

/// <summary>
/// 読み取った内容をValueに移す
/// </summary>
/// <param name="value">移す先</param>
/// <param name="dataName">移したい内容</param>
void JsonFileLoader::MoveValue(rapidjson::Value& value, std::string dataName)
{
    value = loadDoc.FindMember(dataName.c_str())->value;
}
