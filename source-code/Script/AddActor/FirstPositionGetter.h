#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "Object.h"

/// <summary>
/// �����ʒu���t�@�C������Ƃ��Ă��ĕϊ�����
/// </summary>
class FirstPositionGetter
{
public:
    /// <summary>
    /// �I������Ă���X�e�[�W�̃I�u�W�F�N�g�̏����ʒu��n��
    /// </summary>
    /// <param name="kind">�I�u�W�F�N�g�̎�ނɂ���ēǂݍ��ޏ���ύX����</param>
    /// <returns>���̃I�u�W�F�N�g�̈ʒu���܂Ƃ߂��R���e�i</returns>
    static std::vector<PlacementData> GetPlaceData(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �����̃t�@�C������ǂݎ���ď����ʒu��n��
    /// </summary>
    /// <param name="fileName">�z�u���t�@�C���̖��O</param>
    /// <returns>�z�u���̃R���e�i</returns>
    static std::vector<PlacementData> GetPlaceData(std::string fileName);
    /// <summary>
    /// �I�����ꂽ�X�e�[�W�̏����ʒu��n��
    /// </summary>
    /// <returns>�z�u���̃R���e�i</returns>
    static std::vector<PlacementData> GetPlaceData();
private:
    /// <summary>
    /// CSV�ŏ������������ʒu���\���̂ɕϊ�
    /// </summary>
    /// <param name="objNum">������肽���I�u�W�F�N�g�̔ԍ�</param>
    /// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
    /// <returns></returns>
    static std::vector<PlacementData> CSVConvertFirstData(int objNum,std::string placeStrData);
    /// <summary>
    /// Csv�ŏ������������ʒu���\���̂ɕϊ�
    /// </summary>
    /// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
    /// <returns></returns>
    static std::vector<PlacementData> CSVConvertFirstData(std::string placeStrData);
    /// <summary>
    /// Json�ŏ������������ʒu���\���̂ɕϊ�
    /// </summary>
    /// <param name="objNum">������肽���I�u�W�F�N�g�̔ԍ�</param>
    /// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
    /// <returns></returns>
    static std::vector<PlacementData> JsonConvertFirstData(int objNum,std::string placeStrData);
    /// <summary>
    /// Json�ŏ������������ʒu���\���̂ɕϊ�
    /// </summary>
    /// <param name="placeStrData">�S�̂̏����ʒu������f�[�^</param>
    /// <returns></returns>
    static std::vector<PlacementData> JsonConvertFirstData(std::string placeStrData);
    //Json�̃X�L�[�}�̃p�X
    static std::string schemaPath;
};