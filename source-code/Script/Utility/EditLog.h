#pragma once
#include "EditObjectData.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
/// <summary>
/// �ҏW�������̂����ɖ߂���悤�ɋL�^����
/// </summary>
class EditLog
{
public:
    EditLog(std::string logFileName);
    /// <summary>
    /// placeData����납��prevNum�Ԗڂɒǉ�
    /// </summary>
    /// <param name="prevNum">�߂肽���ꏊ</param>
    /// <param name="totalEdit">�ۑ��������I�u�W�F�N�g�̑���</param>
    /// <param name="nowEditNum">�ҏW�ԍ�</param>
    /// <param name="placeData">�ۑ����������</param>
    void SaveEditDataLog(int prevNum,int totalEdit,int nowEditNum, PlacementData placeData);
    /// <summary>
    /// �ЂƂO�̏�Ԃɖ߂��邩
    /// </summary>
    /// <returns></returns>
    bool CanBackPrevState(int prevNum)const;
    /// <summary>
    /// �ЂƂO�ɕҏW�������̂̏���n��
    /// </summary>
    /// <param name="prevNum"></param>
    /// <returns></returns>
    PlacementData GetPrevEditData(int prevNum);
    /// <summary>
    /// �ЂƂO�ɕҏW�����I�u�W�F�N�g�̔z��ԍ�
    /// </summary>
    /// <returns></returns>
    int GetEditNum()const { return editNum; };
    /// <summary>
    /// �ҏW�����I�u�W�F�N�g�̍��v��
    /// </summary>
    /// <returns></returns>
    int GetTotalNum()const { return totalNum; };
private:
    /// <summary>
    /// �ۑ����邽�߂�Json��Value�ɓo�^���ĕԂ�
    /// </summary>
    /// <param name="totalEdit">�ҏW����</param>
    /// <param name="editNum">�ҏW�z��ԍ�</param>
    /// <param name="editData">�ҏW���</param>
    /// <param name="allocator">Json�̃A���P�[�^�[</param>
    /// <returns></returns>
    rapidjson::Value GetEditPlaceData(int totalEdit,int editNum,PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    /// <summary>
    /// ������邽�߂�Json��Value�ɓo�^���ĕԂ�
    /// </summary>
    /// <param name="editData">�ҏW���</param>
    /// <param name="allocator">Json�̃A���P�[�^�[</param>
    /// <returns></returns>
    rapidjson::Value GetEditPlaceData(const rapidjson::Value* editData, rapidjson::Document::AllocatorType& allocator)const;
    //�X�L�[�}�̃p�X
    const std::string schemaStr = "data/Json/Schema/editLogData.json";
    //�t�@�C���̃p�X
    std::string fileName;
    // �ЂƂO�ɕҏW�����I�u�W�F�N�g�̔z��ԍ�
    int editNum = 0;
    // �ҏW�����I�u�W�F�N�g�̍��v��
    int totalNum = 0;
};