#include "AddFlyShipDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 飛行船の情報を読み取る
/// </summary>
/// <param name="data">読み取る飛行船</param>
AddFlyShipDataLoader::AddFlyShipDataLoader(AddData data)
    :AddObjectDataLoader()
{

    if (IsExistJsonFile())//jsonファイルが見つかったかどうか
    {
        auto initJsonFileLoader = std::make_unique<JsonFileLoader>(addDataList[CAST_I(data)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("aliveTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("coolTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadInt("unitNum")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("unitBetween")));
        SAFE_RESET(initJsonFileLoader);
        
    }
    else//csvで読み込む
    {
        auto initDataLoader = std::make_unique< CSVFileLoader>(addDataList[CAST_I(data)]);
        loadData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
    }

}