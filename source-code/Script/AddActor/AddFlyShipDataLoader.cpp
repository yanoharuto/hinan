#include "AddFlyShipDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ��s�D�̏���ǂݎ��
/// </summary>
/// <param name="data">�ǂݎ���s�D</param>
AddFlyShipDataLoader::AddFlyShipDataLoader(AddData data)
    :AddObjectDataLoader()
{

    if (IsExistJsonFile())//json�t�@�C���������������ǂ���
    {
        auto initJsonFileLoader = std::make_unique<JsonFileLoader>(addDataList[CAST_I(data)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("aliveTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("coolTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadInt("unitNum")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("unitBetween")));
        SAFE_RESET(initJsonFileLoader);
        
    }
    else//csv�œǂݍ���
    {
        auto initDataLoader = std::make_unique< CSVFileLoader>(addDataList[CAST_I(data)]);
        loadData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
    }

}