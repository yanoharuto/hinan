#include "AddPlayerDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// �v���C���[�̒ǉ���������
/// </summary>
AddPlayerDataLoader::AddPlayerDataLoader()
{
    
    if (IsExistJsonFile())//json�t�@�C���������������ǂ���
    {
        auto initJsonFileLoader = std::make_unique <JsonFileLoader>(addDataList[CAST_I(AddData::playerSpeed)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("acceleSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("lowestSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("maxSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("turboAddSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("turboTime")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("gripPower")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("breakPower")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("turboChargeTime")));
        SAFE_RESET(initJsonFileLoader); 
    }
    else//csv�œǂݍ���
    {
        auto initDataLoader = std::make_unique<CSVFileLoader>(addDataList[CAST_I(AddData::playerSpeed)]);
        loadData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
    }
    
}
