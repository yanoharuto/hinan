#include "AddMoveSawDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ˆÚ“®ŠÛ‹˜‚Ìî•ñ‚ğ“Ç‚İæ‚é
/// </summary>
AddMoveSawDataLoader::AddMoveSawDataLoader()
    :AddObjectDataLoader()
{
    
    if (IsExistJsonFile())//jsonƒtƒ@ƒCƒ‹‚ªŒ©‚Â‚©‚Á‚½‚©‚Ç‚¤‚©
    {
        auto initJsonFileLoader = std::make_unique<JsonFileLoader>(addDataList[CAST_I(AddData::moveSaw)], addDataSchema);
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveSpeed")));
        loadData.push_back(std::to_string(initJsonFileLoader->GetLoadFloat("moveTime")));
        SAFE_RESET(initJsonFileLoader);
    }
    else//csv‚Å“Ç‚İ‚Ş
    {
        auto initDataLoader = std::make_unique<CSVFileLoader>(addDataList[CAST_I(AddData::moveSaw)]);
        loadData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
    }
    
}