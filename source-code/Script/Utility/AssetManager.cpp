#include <sys/stat.h>
#include <iostream>
#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "JsonFileLoader.h"
#include "Utility.h"
#include "CSVFileLoader.h"
//初期化ファイルの名前
 std::string const AssetManager::initFileNames[]
= { 
    {"CameraInitPath"},
    {"initEffectPath"},
    {"InitObjPath"},
    {"InitUIPath"},
    {"SoundInitPath"},
    {"stageDataList"},
    {"ObjectAddDataPath"},
};
 //csvファイルまでのパス
 std::string const AssetManager::initCSVFilePath = "data/csv/List/";
 //Jsonファイルがあるか調べるのに使う
 std::string const AssetManager::jsonExistFile = "data/Json";
 //jsonファイルまでのパス
 std::string const AssetManager::initJSONFilePath = "data/Json/List/";
 //リストのスキーマ
 const std::string AssetManager::listSchemaPath = "data/Json/List/assetPassSchema";
 AssetManager::AssetManager()
 {
 }
 /// <summary>
/// jsonFileで読み取れそうか調べる
/// </summary>
/// <returns>調べれそうならtrue</returns>
 bool AssetManager::IsExistJsonFile()
 {
     struct stat jsonFile;
     auto boolValue = stat(jsonExistFile.c_str(), &jsonFile) != -1;
     return boolValue;
 }
 /// <summary>
/// 初期化で使うファイルのパスを所得
/// </summary>
/// <param name="fileKind">欲しいファイルの種類</param>
/// <returns></returns>
std::string AssetManager::GetInitCsvFilePath(AssetList fileKind) 
{
    return initCSVFilePath + initFileNames[CAST_I(fileKind)] + Utility::CSV_FILE;
}

/// <summary>
/// 初期化で使うJsonファイルのパスを所得
/// </summary>
/// <param name="fileKind">欲しいファイルの種類</param>
/// <returns>初期化で使うJsonファイルのパス</returns>
std::string AssetManager::GetInitJsonFilePath(AssetList fileKind)
{
    return initJSONFilePath + initFileNames[CAST_I(fileKind)] + Utility::JSON_FILE;
}
/// <summary>
/// 読み取ったファイルからasset一覧をVectorに移していく
/// </summary>
/// <param name="fileLoader">読み取ったファイル</param>
std::vector<std::string> AssetManager::GetAssetList(AssetList listKind)
{
    std::vector<std::string> returnValue;
    if (IsExistJsonFile())//jsonでエフェクト一覧を所得
    {
        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(GetInitJsonFilePath(listKind), listSchemaPath + Utility::JSON_FILE);

        if (initJsonFileLoader->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
        {
            const rapidjson::Value& list = initJsonFileLoader->GetLoadArray("assetPass");
            auto array = list.Begin();
            //各オブジェクトの情報があるファイルのパスを所得
            for (int i = 0; i < static_cast<int>(list.Size()); i++)
            {
                returnValue.push_back(array->FindMember("item")->value.GetString());
                array++;
            }
        }
        SAFE_DELETE(initJsonFileLoader);
        return returnValue;
    }
    else//csvで所得
    {
        CSVFileLoader* initDataFile = new CSVFileLoader(GetInitCsvFilePath(listKind));
        returnValue = initDataFile->GetStringData();
        SAFE_DELETE(initDataFile);
    }
    return returnValue;
}
/// <summary>
/// 引数のファイルが存在するか調べる
/// </summary>
/// <param name="fileName"></param>
/// <returns>存在するならtrue</returns>
bool AssetManager::IsExistFile(std::string fileName)
{
    struct stat jsonFile;
    auto boolValue = stat(fileName.c_str(), &jsonFile) != -1;
    return boolValue;
}

 