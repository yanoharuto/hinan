#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include "EditObjectData.h"
#include "InitObjKind.h"
class StageDataEditor;

constexpr int STAGE_WIDTH_VALUE = 6000;
using namespace ObjectInit;
/// <summary>
/// �ҏW�������̂��t�@�C���ɕۑ�����
/// </summary>
class EditDataSaver
{
public:
    EditDataSaver() {};
    ~EditDataSaver() {};
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="placeVector">�ҏW��������Z�߂�Vector</param>
    void SaveEditData(std::string fileName,std::vector<PlacementData> placeVector);
private:
    /// <summary>
    /// �ҏW��������ۑ�����
    /// </summary>
    /// <param name="editData">�ҏW�������</param>
    /// <param name="saveFileName">�ۑ�����t�@�C��</param>
    void SaveEditDataForCSV(std::string fileName,std::vector<PlacementData> editData)const;
    /// <summary>
    /// �����̕ҏW����Json�ɕۑ��ł���悤�ɂ���
    /// </summary>
    /// <param name="editData">�ҏW���</param>
    /// <param name="allocator">�ҏW�̂��߂ɕK�v��allocator</param>
    /// <returns>Json�ɕۑ��ł���悤�ɂ�������</returns>
    rapidjson::Value GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    /// <summary>
    /// Json�`���ŕۑ�����
    /// </summary>
    /// <param name="editData">�ҏW���������Z��</param>
    /// <param name="saveFileName">�ۑ���̃t�@�C���̖��O</param>
    void SaveEditDataForJSON(std::string fileName, std::vector<PlacementData> editData)const;
    //�X�e�[�W��
    const std::string stageFilePath = "data/Json/StageData/Stage4/stageData";
};