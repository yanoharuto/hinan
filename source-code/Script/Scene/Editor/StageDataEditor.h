#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"

//�v���C���[�̎��ʔԍ�
constexpr int PLAYER_NUMBER = static_cast<int>(ObjectInit::InitObjKind::player);
//�v���C���[�̎��ʔԍ�
constexpr int COLLECT_NUMBER = static_cast<int>(ObjectInit::InitObjKind::collect);

class EditorDrawModel;
class CameraObserver;
class MouseInput;
class EditLog;
using namespace ObjectInit;
/// <summary>
/// �X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
/// </summary>
class StageDataEditor
{
public: 
    /// <summary>
    ///�X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
    /// </summary>
    StageDataEditor();
    /// <summary>
    /// �ҏW�I�u�W�F�N�g�̗����̊J����Json�t�@�C���ɏ����ʂ�
    /// </summary>
    virtual ~StageDataEditor();
    /// <summary>
    /// �ҏW����
    /// </summary>
    void OnPut(PlacementData placeData);
    /// <summary>
    /// �ҏW���Ăق����f�[�^��n��
    /// </summary>
    /// <returns>�ҏW���Ăق����f�[�^</returns>
    PlacementData GetEditData() const;
    /// <summary>
    /// �`�悵�Ăق������̂�n����n��
    /// </summary>
    /// <returns>���̃t�F�[�Y�̕ҏW�ς݃f�[�^�̓Z�߂�����</returns>
    std::vector<PlacementData> GetNowFaseEditEndPlacementData()const;
    /// <summary>
    /// �ۑ����Ăق����ҏW�ς݃f�[�^��Z�߂����̂�n��
    /// </summary>
    /// <returns>�S�Ă̕ҏW�ς݃f�[�^�̓Z�߂�����</returns>
    std::vector<PlacementData> GetAllEditEndPlacementData()const;
    /// <summary>
    /// ���ݕҏW���Ă���A�C�e���̏o�Ă���^�C�~���O��ύX
    /// </summary>
    void ChangeAppearFase(std::weak_ptr<MouseInput> mouse);
    /// <summary>
    /// �����̏ꏊ�ɕҏW�������̂����邩����ׂ�
    /// </summary>
    /// <param name="placeData">���ҏW���Ă���ꏊ�̏��</param>
    void UpdateEditTarget(PlacementData placeData);
    /// <summary>
    /// �ĕҏW���Ă��镨�͍폜����
    /// </summary>
    void OnEraceEditData();
    /// <summary>
    /// �ЂƂO�̏�Ԃɖ߂�
    /// </summary>
    void OnBackStepPrevState();
    /// <summary>
    /// �ЂƂO�̏�Ԃ��畜�����Ĉ��ɂ���
    /// </summary>
    void OnStepState();
    /// <summary>
    /// �ĕҏW�����ǂ���
    /// </summary>
    /// <returns>�ĕҏW���Ȃ�True</returns>
    bool IsReEdit()const;
    /// <summary>
    /// ���W�A�C�e���̐�
    /// </summary>
    /// <returns></returns>
    int GetCollectNum()const { return collectNum; };
    /// <summary>
    /// ���ҏW���Ă���Fase�ԍ�
    /// </summary>
    /// <returns></returns>
    int GetApperFaseNum()const { return appearFaseNum; };
protected:

    /// ���W�A�C�e���̐�
    int collectNum;  
    /// ���W�A�C�e����������ǂ̃^�C�~���O�ŏo�Ă��邩
    int appearFaseNum;
    //���ݕҏW���Ă���ԍ�
    int editNum = 0;
    //�ĕҏW�����ǂ����̃t���O
    bool isReEdit = false;
    //�v���C���[�ҏW�����ǂ����̃t���O
    bool isEditPlayer = false;
    //�ҏW�ς݃f�[�^
    std::vector<PlacementData> editedPlacementDataVec;
    //�ҏW�t�@�C���u����
    const std::string editFilePath = "data/Json/StageData/Stage4/editData";
    //�ЂƂO�̏�Ԃɖ߂����߂̊O���t�@�C��
    const std::string editLogFilePath = "data/Json/StageData/Stage4/editLogData";
    //�}�E�X�ŃN���b�N�����ꏊ����300���߂�������ĕҏW
    const float nearDistanceReferenceValue = 30.0f;
    //�v���C���[�ԍ�
    PlacementData playerData = { PLAYER_NUMBER,0,0,0,1,0 };
    //�ǂ̂��炢�O�̏�Ԃɖ߂��� 0�Ȃ��ԍŐV�̏��
    int prevNum = 0;
    //�ߋ��̕ҏW�f�[�^
    std::unique_ptr<EditLog> log;
};