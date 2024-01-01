#include "AddMoveSawDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// �ړ��ۋ��̏���ǂݎ��
/// </summary>
AddMoveSawDataLoader::AddMoveSawDataLoader()
    :AddObjectDataLoader()
{
    
    if (IsExistJsonFile())//json�t�@�C���������������ǂ���
    {
        auto initJsonFileLoader = std::make_unique<JsonFileLoader>(addDataList[CAST_I(AddData::moveSaw)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveTime")));
        SAFE_RESET(initJsonFileLoader);
    }
    else//csv�œǂݍ���
    {
        auto initDataLoader = std::make_unique<CSVFileLoader>(addDataList[CAST_I(AddData::moveSaw)]);
        loadData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
    }
    
}