#include "AddObjectDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ’Ç‰Áî•ñ‚ğ“Ç‚İæ‚é
/// </summary>
AddObjectDataLoader::AddObjectDataLoader()
{
    addDataList = GetAssetList(AssetList::objectAddData);
}