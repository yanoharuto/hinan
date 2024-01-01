#include <sys/stat.h>
#include <iostream>
#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "JsonFileLoader.h"
#include "Utility.h"
#include "CSVFileLoader.h"
//�������t�@�C���̖��O
 std::string const AssetManager::initFileNames[]
= { 
    {"CameraInitPath"},
    {"initEffectPath"},
    {"InitObjPath"},
    {"InitUIPath"},
    {"SoundInitPath"},
    {"stageDataList"},
    {"ObjectAddDataPath"},
};
 //csv�t�@�C���܂ł̃p�X
 std::string const AssetManager::initCSVFilePath = "data/csv/List/";
 //Json�t�@�C�������邩���ׂ�̂Ɏg��
 std::string const AssetManager::jsonExistFile = "data/Json";
 //json�t�@�C���܂ł̃p�X
 std::string const AssetManager::initJSONFilePath = "data/Json/List/";
 //���X�g�̃X�L�[�}
 const std::string AssetManager::listSchemaPath = "data/Json/List/assetPassSchema";
 AssetManager::AssetManager()
 {
 }
 /// <summary>
/// jsonFile�œǂݎ�ꂻ�������ׂ�
/// </summary>
/// <returns>���ׂꂻ���Ȃ�true</returns>
 bool AssetManager::IsExistJsonFile()
 {
     struct stat jsonFile;
     auto boolValue = stat(jsonExistFile.c_str(), &jsonFile) != -1;
     return boolValue;
 }
 /// <summary>
/// �������Ŏg���t�@�C���̃p�X������
/// </summary>
/// <param name="fileKind">�~�����t�@�C���̎��</param>
/// <returns></returns>
std::string AssetManager::GetInitCsvFilePath(AssetList fileKind) 
{
    return initCSVFilePath + initFileNames[CAST_I(fileKind)] + Utility::CSV_FILE;
}

/// <summary>
/// �������Ŏg��Json�t�@�C���̃p�X������
/// </summary>
/// <param name="fileKind">�~�����t�@�C���̎��</param>
/// <returns>�������Ŏg��Json�t�@�C���̃p�X</returns>
std::string AssetManager::GetInitJsonFilePath(AssetList fileKind)
{
    return initJSONFilePath + initFileNames[CAST_I(fileKind)] + Utility::JSON_FILE;
}
/// <summary>
/// �ǂݎ�����t�@�C������asset�ꗗ��Vector�Ɉڂ��Ă���
/// </summary>
/// <param name="fileLoader">�ǂݎ�����t�@�C��</param>
std::vector<std::string> AssetManager::GetAssetList(AssetList listKind)
{
    std::vector<std::string> returnValue;
    if (IsExistJsonFile())//json�ŃG�t�F�N�g�ꗗ������
    {
        JsonFileLoader* initJsonFileLoader = new JsonFileLoader(GetInitJsonFilePath(listKind), listSchemaPath + Utility::JSON_FILE);

        if (initJsonFileLoader->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
        {
            const rapidjson::Value& list = initJsonFileLoader->GetLoadArray("assetPass");
            auto array = list.Begin();
            //�e�I�u�W�F�N�g�̏�񂪂���t�@�C���̃p�X������
            for (int i = 0; i < static_cast<int>(list.Size()); i++)
            {
                returnValue.push_back(array->FindMember("item")->value.GetString());
                array++;
            }
        }
        SAFE_DELETE(initJsonFileLoader);
        return returnValue;
    }
    else//csv�ŏ���
    {
        CSVFileLoader* initDataFile = new CSVFileLoader(GetInitCsvFilePath(listKind));
        returnValue = initDataFile->GetStringData();
        SAFE_DELETE(initDataFile);
    }
    return returnValue;
}
/// <summary>
/// �����̃t�@�C�������݂��邩���ׂ�
/// </summary>
/// <param name="fileName"></param>
/// <returns>���݂���Ȃ�true</returns>
bool AssetManager::IsExistFile(std::string fileName)
{
    struct stat jsonFile;
    auto boolValue = stat(fileName.c_str(), &jsonFile) != -1;
    return boolValue;
}

 