#include "AddMoveSawDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 移動丸鋸の情報を読み取る
/// </summary>
AddMoveSawDataLoader::AddMoveSawDataLoader()
    :AddObjectDataLoader()
{
    
    if (IsExistJsonFile())//jsonファイルが見つかったかどうか
    {
        auto initJsonFileLoader = std::make_unique<JsonFileLoader>(addDataList[CAST_I(AddData::moveSaw)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveTime")));
        SAFE_RESET(initJsonFileLoader);
    }
    else//csvで読み込む
    {
        auto initDataLoader = std::make_unique<CSVFileLoader>(addDataList[CAST_I(AddData::moveSaw)]);
        loadData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
    }
    
}