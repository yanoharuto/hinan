#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "JsonFileLoader.h"
#include "StageDataManager.h"
std::string FirstPositionGetter::schemaPath = "arrangeDataSchema.json";
/// <summary>
/// �����ʒu��n��
/// </summary>
/// <param name="dataKind">�I�u�W�F�N�g�̎�ނɂ���ēǂݍ��ޏ���ύX����</param>
/// <returns>���̃I�u�W�F�N�g�̈ʒu���܂Ƃ߂��R���e�i</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(ObjectInit::InitObjKind kind)
{
    if (StageDataManager::IsExistJsonFile())
    {
        return JsonConvertFirstData(CAST_I(kind), StageDataManager::GetPlaceStrData());
    }
    return CSVConvertFirstData(CAST_I(kind),StageDataManager::GetPlaceStrData());
}
/// <summary>
/// �����̃t�@�C������ǂݎ���ď����ʒu��n��
/// </summary>
/// <param name="fileName">�z�u���t�@�C���̖��O</param>
/// <returns>�z�u���̃R���e�i</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData(std::string fileName)
{    
    //�z�u���ɕϊ�����
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
/// �I�����ꂽ�X�e�[�W�̏����ʒu��n��
/// </summary>
/// <returns>�z�u���̃R���e�i</returns>
std::vector<PlacementData> FirstPositionGetter::GetPlaceData()
{
    if (StageDataManager::IsExistJsonFile())
    {
        return JsonConvertFirstData(StageDataManager::GetPlaceStrData());
    }
    return CSVConvertFirstData(StageDataManager::GetPlaceStrData());
}
/// <summary>
/// CSV�ŏ������������ʒu���\���̂ɕϊ�
/// </summary>
/// <param name="objNum">������肽���I�u�W�F�N�g�̔ԍ�</param>
/// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
/// <returns></returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(int objNum, std::string placeStrData)
{
    //�S�z�u��������
    auto allPlaceData = CSVConvertFirstData(placeStrData);
    std::vector<PlacementData> returnValue;
    //�����̃I�u�W�F�N�g�̌��n��
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
/// Json�ŏ������������ʒu���\���̂ɕϊ�
/// </summary>
/// <param name="objNum">������肽���I�u�W�F�N�g�̔ԍ�</param>
/// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
/// <returns></returns>
std::vector<PlacementData> FirstPositionGetter::JsonConvertFirstData(int objNum, std::string placeStrData)
{
    //�S�z�u��������
    auto allPlaceData = JsonConvertFirstData(placeStrData);
    std::vector<PlacementData> returnValue;
    //�����̃I�u�W�F�N�g�̌��n��
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
/// CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏�������
/// </summary>
/// <param name="fileName">�z�u���܂ł̃p�X</param>
/// <param name="kind">�����������z�u���̎��</param>
/// <returns>CSV�t�@�C������X�e�[�W�ɔz�u���邽�߂̏��</returns>
std::vector<PlacementData> FirstPositionGetter::CSVConvertFirstData(std::string fileName)
{
    auto csvFile = std::make_unique<CSVFileLoader>(fileName);
    auto placeStrData = csvFile->GetStringData();
    SAFE_RESET(csvFile)
    //�f�[�^�̎�ނƗ�̑�������I�u�W�F�N�g�̐����v�Z
    int objCount = CONTAINER_GET_SIZE(placeStrData) / EDIT_ARRANGEMENT_DATA_KIND_NUM;
    //�߂�l
    std::vector<PlacementData> dataVec;

    for (int i = 0; i < objCount; i++)
    {
        //�\���̂̏��̎��
        int dataKindNum = i * EDIT_ARRANGEMENT_DATA_KIND_NUM;
        //�z�u���������
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
/// Json�ŏ������������ʒu���\���̂ɕϊ�
/// </summary>
/// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
/// <returns></returns>
std::vector<PlacementData> FirstPositionGetter::JsonConvertFirstData(std::string fileName)
{
    //�X�e�[�W�ɔz�u���邽�߂̏��
    std::vector<PlacementData> returnValue;
    //Json����ǂݎ��
    auto fileLoader = std::make_unique<JsonFileLoader>(fileName, schemaPath);
    if (fileLoader->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
    {
        const rapidjson::Value& list = fileLoader->GetLoadArray(ARRANGEDATA_MEMBER);
        auto arrayValue = list.Begin();
        //�e�I�u�W�F�N�g�̏����ʒu��������
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