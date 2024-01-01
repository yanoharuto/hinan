#include "CameraDataLoader.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "JsonFileLoader.h"
std::string CameraDataLoader::schemaPath = "cameraParametor.json";
/// <summary>
/// ��������񏊓�
/// </summary>
/// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
CameraDataLoader::CameraParamater CameraDataLoader::GetCameraParamator(UseCameraSceneKind type)const
{
    //�Ԃ�l
    CameraParamater returnValue;
    //�J�����̈ꗗ������
    std::vector<std::string> strData = GetAssetList(AssetList::camera);
    if (IsExistJsonFile())//json�œǂݍ���
    {
        auto fileLoader = std::make_unique<JsonFileLoader>(strData[CAST_I(type)], schemaPath);//�V�[�����̏�������
        returnValue.nearValue = fileLoader->GetLoadInt("nearValue");
        returnValue.farValue = fileLoader->GetLoadInt("farValue");
        returnValue.lookAngle = fileLoader->GetLoadInt("lookAngle");
        returnValue.targetBetween = fileLoader->GetLoadInt("targetBetween");
        returnValue.setYPos = fileLoader->GetLoadFloat("setYPos");
        returnValue.speed = fileLoader->GetLoadFloat("speed");
        SAFE_RESET(fileLoader);
    }
    else
    {
        //�܂Ƃ߃t�@�C������V�[�����Ƃ̏�������
        auto initDataLoader = std::make_unique<CSVFileLoader>(strData[CAST_I(type)]);
        strData = initDataLoader->GetStringData();
        SAFE_RESET(initDataLoader);
        //�J�����̗L���͈�
        returnValue.nearValue = STR_TO_F(strData[CAST_I(CameraParameter::setNearValue)]);
        returnValue.farValue = STR_TO_F(strData[CAST_I(CameraParameter::setFarValue)]);
        //�^�[�Q�b�g�Ƃ̋���
        returnValue.targetBetween = STR_TO_F(strData[CAST_I(CameraParameter::setTargetBetween)]);
        //���x
        returnValue.setYPos = STR_TO_F(strData[CAST_I(CameraParameter::setYPosition)]);
        //�J�����̑���
        returnValue.speed = STR_TO_F(strData[CAST_I(CameraParameter::setCameraSpeed)]);
        //�J�����̌����Ă���͈�
        returnValue.lookAngle = STR_TO_F(strData[CAST_I(CameraParameter::setLookingAngle)]);
    }
    return returnValue;
}
