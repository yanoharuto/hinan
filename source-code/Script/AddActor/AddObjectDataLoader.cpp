#include "AddObjectDataLoader.h"
#include "JsonFileLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// �ǉ�����ǂݎ��
/// </summary>
AddObjectDataLoader::AddObjectDataLoader()
{
    addDataList = GetAssetList(AssetList::objectAddData);
}