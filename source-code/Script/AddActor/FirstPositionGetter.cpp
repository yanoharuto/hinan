#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "JsonFileLoader.h"
#include "StageDataManager.h"
std::string FirstPositionGetter::schemaPath = "arrangeDataSchema.json";
/// <summary>
/// 初期位置を渡す
/// </summary>
/// <param name="dataKind">オブジェクトの種類によって読み込む情報を変更する</param>
/// <returns>そのオブジェクトの位置をまとめたコンテナ</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(ObjectInit::InitObjKind kind)
{
    if (StageDataManager::IsExistJsonFile())
    {
        return JsonConvertFirstData(CAST_I(kind), StageDataManager::GetPlaceStrData());
    }
    return CSVConvertFirstData(CAST_I(kind),StageDataManager::GetPlaceStrData());
}
/// <summary>
/// 引数のファイルから読み取って初期位置を渡す
/// </summary>
/// <param name="fileName">配置情報ファイルの名前</param>
/// <returns>配置情報のコンテナ</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(std::string fileName)
{    
    //配置情報に変換する
    std::vector<PlacementData> placeData;

    if (StageDataManager::IsExistJsonFile())
    {
        fileName += Utility::JSON_FILE;
        placeData = JsonConvertFirstData(fileName);
    }
    else
    {
        fileName += Utility::CSV_FILE;
        placeData = CSVConvertFirstData(fileName);
    }
    return placeData;
}
/// <summary>
/// 選択されたステージの初期位置を渡す
/// </summary>
/// <returns>配置情報のコンテナ</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData()
{
    if (StageDataManager::IsExistJsonFile())
    {
        return JsonConvertFirstData(StageDataManager::GetPlaceStrData());
    }
    return CSVConvertFirstData(StageDataManager::GetPlaceStrData());
}
/// <summary>
/// CSVで所得した初期位置を構造体に変換
/// </summary>
/// <param name="objNum">抜き取りたいオブジェクトの番号</param>
/// <param name="placeStrData">全体の初期位置文字列データ</param>
/// <returns></returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(int objNum, std::string placeStrData)
{
    //全配置情報を所得
    auto allPlaceData = CSVConvertFirstData(placeStrData);
    std::vector<PlacementData> returnValue;
    //引数のオブジェクトの見渡す
    for (int i = 0; i < CONTAINER_GET_SIZE(allPlaceData); i++)
    {
        if (allPlaceData[i].objKind == objNum)
        {
            returnValue.push_back(allPlaceData[i]);
        }
    }
    return returnValue;
}
/// <summary>
/// Jsonで所得した初期位置を構造体に変換
/// </summary>
/// <param name="objNum">抜き取りたいオブジェクトの番号</param>
/// <param name="placeStrData">全体の初期位置文字列データ</param>
/// <returns></returns>
std::vector<PlacementData> FirstPositionGetter::JsonConvertFirstData(int objNum, std::string placeStrData)
{
    //全配置情報を所得
    auto allPlaceData = JsonConvertFirstData(placeStrData);
    std::vector<PlacementData> returnValue;
    //引数のオブジェクトの見渡す
    for (int i = 0; i < CONTAINER_GET_SIZE(allPlaceData); i++)
    {
        if (allPlaceData[i].objKind == objNum)
        {
            returnValue.push_back(allPlaceData[i]);
        }
    }
    return returnValue;
}
/// <summary>
/// CSVファイルからステージに配置するための情報を所得
/// </summary>
/// <param name="fileName">配置情報までのパス</param>
/// <param name="kind">所得したい配置物の種類</param>
/// <returns>CSVファイルからステージに配置するための情報</returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName)
{
    auto csvFile = std::make_unique<CSVFileLoader>(fileName);
    auto placeStrData = csvFile->GetStringData();
    SAFE_RESET(csvFile)
    //データの種類と列の多さからオブジェクトの数を計算
    int objCount = CONTAINER_GET_SIZE(placeStrData) / EDIT_ARRANGEMENT_DATA_KIND_NUM;
    //戻り値
    std::vector<PlacementData> dataVec;

    for (int i = 0; i < objCount; i++)
    {
        //構造体の情報の種類
        int dataKindNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //配置初期化情報
        PlacementData initData = {};
        initData.objKind = STR_TO_I(placeStrData[dataKindNum + static_cast<int>(EditArrangementDataKind::objectKindNum)]);
        initData.collectNum = STR_TO_I(placeStrData[dataKindNum + static_cast<int>(EditArrangementDataKind::appearCollectNum)]);
        initData.posX = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(EditArrangementDataKind::positionX)]);
        initData.posZ = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(EditArrangementDataKind::positionZ)]);
        initData.dirX = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(EditArrangementDataKind::directionX)]);
        initData.dirZ = STR_TO_F(placeStrData[dataKindNum + static_cast<int>(EditArrangementDataKind::directionZ)]);
        dataVec.push_back(initData);
    }
    return dataVec;
}
/// <summary>
/// Jsonで所得した初期位置を構造体に変換
/// </summary>
/// <param name="placeStrData">全体の初期位置文字列データ</param>
/// <returns></returns>
std::vector<PlacementData> FirstPositionGetter::JsonConvertFirstData(std::string fileName)
{
    //ステージに配置するための情報
    std::vector<PlacementData> returnValue;
    //Jsonから読み取る
    auto fileLoader = std::make_unique<JsonFileLoader>(fileName, schemaPath);
    if (fileLoader->IsAccept())//スキーマと読み込むファイルのバリデーションチェック
    {
        const rapidjson::Value& list = fileLoader->GetLoadArray(ARRANGEDATA_MEMBER);
        auto arrayValue = list.Begin();
        //各オブジェクトの初期位置情報を所得
        for (int i = 0; i < static_cast<int>(list.Size()); i++)
        {
            PlacementData firstPlaceData;
            firstPlaceData.ConversionJsonToPlacementData(arrayValue);
            arrayValue++;
            returnValue.push_back(firstPlaceData);
        }
    }
    SAFE_RESET(fileLoader);
    return returnValue;
}