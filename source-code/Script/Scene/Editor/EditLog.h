#pragma once
#include "JsonWriter.h"
#include "EditObjectData.h"
#include <vector>
constexpr char TOTALNUM_MEMBER[] = "totalEdit";
constexpr char EDIT_MEMBER[] = "editNum";
/// <summary>
/// �ҏW�������̂����ɖ߂���悤�ɋL�^����
/// </summary>
class EditLog :public JsonWriter
{
public:
    /// <summary>
    /// �ҏW����t�@�C���̖��O�ƕҏW������ۑ��@
    /// </summary>
    /// <param name="logFileName">�t�@�C���̖��O</param>
    /// <param name="firstTotalEditNum">�ҏW����</param>
    EditLog(std::string logFileName,int firstTotalEditNum);

    ~EditLog() {};
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
    /// �ҏW���e
    /// </summary>
    enum class EditActionKind
    {
        deleteData,//�폜
        reEdit,//�ĕҏW
        addData//�ǉ�
    };
    /// <summary>
    /// �ҏW���e
    /// </summary>
    struct EditData
    {
        EditActionKind editAction;//�ҏW���e
        PlacementData data;//�z�u���
        int editNum;//�ҏW�ԍ�
    };
    /// <summary>
    /// �ĕҏW�̎���Log�𔽉f�������Ƃ��L�^�����ւ���
    /// </summary>
    /// <param name="prevNum">����ւ���</param>
    /// <param name="editData">����ւ��O�̃f�[�^</param>
    /// <param name="placeData">����ւ���̃f�[�^</param>
    void UpdateReEditData(int prevNum, EditData editData, PlacementData placeData);
    /// <summary>
    /// �ЂƂO�ɕҏW�������̂̏���n��
    /// </summary>
    /// <param name="prevNum">�߂肽���i�K�� 0�Ȃ��ԍŌ�̃��O�������@���̐��͂Ȃ�</param>
    /// <returns></returns>
    EditLog::EditData GetPrevEditData(int prevNum);
    /// <summary>
    /// �ЂƂO�̏�Ԃ̂Ƃ��Ɉ��̏�Ԃɖ߂�
    /// </summary>
    /// <param name="prevNum">�߂肽���i�K�� 0�Ȃ��ԍŌ�̃��O�������@���̐��͂Ȃ�</param>
    /// <returns></returns>
    EditLog::EditData GetStepEditData(int prevNum);
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
    //�X�L�[�}�̃p�X
    const std::string schemaStr = "editLogData.json";

    int firstTotalNum = 0;
};