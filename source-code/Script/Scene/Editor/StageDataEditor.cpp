#include <fstream>
#include <string>
#include "StageDataEditor.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "CameraObserver.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "EditDataSaver.h"
#include "MouseInput.h"
#include "EditLog.h"
/// <summary>
///�X�e�[�W�ɔz�u����I�u�W�F�N�g�̈ʒu�Ȃǂ�ۑ�����
/// </summary>
StageDataEditor::StageDataEditor()
{
    //���W�A�C�e���̐��Əo�Ă���^�C�~���O�̏�����
    collectNum = 0;
    appearFaseNum = 0;
    //�������łɃt�@�C��������Ȃ�f�[�^������Ă���
    editedPlacementDataVec = FirstPositionGetter::GetPlaceData(editFilePath);

    if (!editedPlacementDataVec.empty())
    {
        for (int i = 0; i < CONTAINER_GET_SIZE(editedPlacementDataVec); i++)
        {
            switch (editedPlacementDataVec[i].objKind)
            {
                //�v���C���[�̃f�[�^������Ȃ�ڂ�
            case PLAYER_NUMBER:
                playerData = editedPlacementDataVec[i];
                editedPlacementDataVec.erase(editedPlacementDataVec.begin() + i);
                break;
                //���W�A�C�e���Ȃ�J�E���g
            case COLLECT_NUMBER:
                collectNum++;
                break;
            default:
                break;
            }
        }
    }
    //�L�^�W
    log = std::make_unique<EditLog>(editLogFilePath, CONTAINER_GET_SIZE(editedPlacementDataVec));
    //������W�A�C�e�����Ȃ�������ǉ�����
    if (collectNum == 0)
    {
        collectNum++;
        PlacementData placeData = playerData;
        placeData.objKind = COLLECT_NUMBER;
        editedPlacementDataVec.push_back(placeData);
    }
}
/// <summary>
/// �ҏW�I�u�W�F�N�g�̗����̊J����Json�t�@�C���ɏ����ʂ�
/// </summary>
StageDataEditor::~StageDataEditor()
{
    auto dataSaver = std::make_unique <EditDataSaver>();
    dataSaver->SaveEditData(editFilePath,GetAllEditEndPlacementData());//�ҏW�������ׂĂ���������
    SAFE_RESET(dataSaver);
    SAFE_RESET(log);
}
/// <summary>
/// �ҏW���Ăق����f�[�^��n��
/// </summary>
/// <returns>�ҏW���Ăق����f�[�^</returns>
PlacementData StageDataEditor::GetEditData() const
{    
    if(isEditPlayer)
    {
        return playerData;
    }
    else if (isReEdit && CONTAINER_GET_SIZE(editedPlacementDataVec) != 0)
    {
        return editedPlacementDataVec[editNum];
    }
}
/// <summary>
/// �`�悵�Ăق������̂�n����n��
/// </summary>
/// <returns>���̃t�F�[�Y�̕ҏW�ς݃f�[�^�̓Z�߂�����</returns>
std::vector<PlacementData> StageDataEditor::GetNowFaseEditEndPlacementData() const
{
    std::vector<PlacementData> returnValue;

    for (int i = 0; i < CONTAINER_GET_SIZE(editedPlacementDataVec); i++)
    {
        //�����t�F�[�Y�ɏo�Ă��邩
        if (editedPlacementDataVec[i].collectNum == appearFaseNum)
        {
            returnValue.push_back(editedPlacementDataVec[i]);
        }
    }
    returnValue.push_back(playerData);
    return returnValue;
}
/// <summary>
/// �ۑ����Ăق����ҏW�ς݃f�[�^��Z�߂����̂�n��
/// </summary>
/// <returns>�S�Ă̕ҏW�ς݃f�[�^�̓Z�߂�����</returns>
std::vector<PlacementData> StageDataEditor::GetAllEditEndPlacementData() const
{
    std::vector<PlacementData> returnValue = editedPlacementDataVec;
    returnValue.push_back(playerData);
    return returnValue;
}
/// <summary>
/// ���ݕҏW���Ă���A�C�e���̏o�Ă���^�C�~���O��ύX
/// </summary>
void StageDataEditor::ChangeAppearFase(std::weak_ptr<MouseInput> mouse)
{
    appearFaseNum += mouse.lock()->GetWheelIncreaseValue();
    //���W�A�C�e���̐���葽���Ȃ�Ȃ�
    if (appearFaseNum >= collectNum)
    {
        appearFaseNum = collectNum - 1;
    }
    //0��菭�Ȃ��Ȃ�Ȃ�
    if (appearFaseNum < 0)
    {
        appearFaseNum = 0;
    }
}

/// <summary>
/// �����̏ꏊ�ɕҏW�������̂����邩����ׂ�
/// </summary>
/// <param name="placeData">���ҏW���Ă���ꏊ�̏��</param>
void StageDataEditor::UpdateEditTarget(PlacementData placeData) 
{
    //������
    //�߂��̂��́i�ĕҏW���镨�j���Ȃ��Ƃ��͐V�����ǉ����邽��False
    isReEdit = false;
    isEditPlayer = false;
    editNum = CONTAINER_GET_SIZE(editedPlacementDataVec) - 1;//�V�K�쐬�Ȃ�ǉ��O�̍ő吔�Ɠ���
    //���ׂ�ʒu
    const VECTOR checkPosition = VGet(placeData.posX, 0, placeData.posZ);
    //�ҏW�ς݂̃I�u�W�F�N�g�̈ʒu���
    VECTOR editedPosition = VGet(playerData.posX, 0, playerData.posZ);
    //�����̍ŏ��l
    float minScale = nearDistanceReferenceValue;
    //�����̑傫��
    float betweenScale = VSize(VSub(editedPosition, checkPosition));
    
    //�v���C���[�Ƌ߂����̂𒲂ׂ�
    if(minScale > betweenScale)
    {
        isEditPlayer = true;
        minScale = betweenScale;
    }
    //�v���C���[�ȊO�̂��̂ŋ������߂����̂𒲂ׂ�
    for (int i = 0; i < CONTAINER_GET_SIZE(editedPlacementDataVec); i++)
    {
        PlacementData data = editedPlacementDataVec[i];
        //�ҏW���̃t�F�[�Y�ɏo�Ă���I�u�W�F�N�g�Ȃ��r����
        if (data.collectNum == appearFaseNum)
        {
            editedPosition = VGet(data.posX, 0, data.posZ);
            betweenScale = VSize(VSub(editedPosition, checkPosition));
            //�������r
            if (minScale > betweenScale)
            {
                isReEdit = true;
                isEditPlayer = false;
                editNum = i;
            }
        }
    }
}
/// <summary>
/// �ĕҏW���Ă��镨�͍폜����
/// </summary>
void StageDataEditor::OnEraceEditData()
{
    if(!editedPlacementDataVec.empty())
    {
        //���������ꏊ�Ɉړ�
        auto editData = editedPlacementDataVec.begin();
        editData += editNum;
        //���W�A�C�e���Ȃ琔���Ă���ϐ��̒l�����炷
        if ((*editData).objKind == COLLECT_NUMBER|| 1 > collectNum)
        {
            collectNum--;
            if (collectNum <= appearFaseNum)
            {
                appearFaseNum = collectNum - 1;
            }
        }
        //���������̂����O�Ɏc��
        auto eraceData = *editData;
        editedPlacementDataVec.erase(editData);
        log->SaveEditDataLog(prevNum,CONTAINER_GET_SIZE(editedPlacementDataVec), editNum, eraceData);
        prevNum = 0;
    }
}
/// <summary>
/// �ĕҏW�����ǂ���
/// </summary>
/// <returns>�ĕҏW���Ȃ�True</returns>
bool StageDataEditor::IsReEdit() const
{
    return isReEdit || isEditPlayer;
}
/// <summary>
/// �ЂƂO�̏�Ԃɖ߂�
/// </summary>
void StageDataEditor::OnBackStepPrevState()
{
    if (log->CanBackPrevState(prevNum))//�ҏW�������c���Ă���Ȃ�
    {
        //�ߋ��̔z�u�������� �z�C�[�������Ȃ�O�ɖ߂�@��Ȃ��ɖ߂�
        auto placeData = log->GetPrevEditData(prevNum);
        //�v���C���[��������v���C���[�̈ʒu�Ɖ�]��߂�
        if (placeData.data.objKind == PLAYER_NUMBER)
        {
            log->UpdateReEditData(prevNum, placeData, playerData);
            playerData = placeData.data;
        }
        else
        {
            //���O���w���Ă���I�u�W�F�N�g
            auto allocator = editedPlacementDataVec.begin();
            switch (placeData.editAction)
            {
            case EditLog::EditActionKind::reEdit://�ĕҏW�Ȃ猳�ɖ߂�
                log->UpdateReEditData(prevNum, placeData, editedPlacementDataVec[placeData.editNum]);
                editedPlacementDataVec[placeData.editNum] = placeData.data;
                break;
            case EditLog::EditActionKind::deleteData://�߂̏ꏊ�ɒǉ�
                allocator += placeData.editNum;
                editedPlacementDataVec.insert(allocator, placeData.data);
                break;
            case EditLog::EditActionKind::addData://�ЂƂO�͐V�������̂��Ȃ��̂ō폜
                editedPlacementDataVec.erase(editedPlacementDataVec.end() - 1);
                break;
            };
        }
        //�ЂƂO�̏�Ԃɖ߂�
        prevNum++;
    }
}
/// <summary>
/// �ЂƂO�̏�Ԃ��畜�����Ĉ��ɂ���
/// </summary>
void StageDataEditor::OnStepState()
{
    if (prevNum > 0)//�ЂƂO�ɖ߂��Ă���Ȃ畜���\
    {
        //���̏�Ԃɖ߂�
        prevNum--;
        //�ߋ��̔z�u��������
        auto placeData = log->GetStepEditData(prevNum);
        //�v���C���[��������v���C���[�̈ʒu�Ɖ�]��߂�
        if (placeData.data.objKind == PLAYER_NUMBER)
        {
            log->UpdateReEditData(prevNum, placeData, playerData);//���ɖ߂��O�̏�Ԃ��L�^
            playerData = placeData.data;
        }
        else
        {
            //���O���w���Ă���I�u�W�F�N�g
            auto allocator = editedPlacementDataVec.begin();
            switch (placeData.editAction)
            {
            case EditLog::EditActionKind::reEdit://�ĕҏW�Ȃ猳�ɖ߂�
                log->UpdateReEditData(prevNum, placeData, editedPlacementDataVec[placeData.editNum]);
                editedPlacementDataVec[placeData.editNum] = placeData.data;
                break;
            case EditLog::EditActionKind::deleteData://�ҏW�ӏ��͍폜����Ă���
                allocator += placeData.editNum;
                editedPlacementDataVec.erase(allocator);
                break;
            case EditLog::EditActionKind::addData://���Œǉ�����Ă���̂�push_back
                editedPlacementDataVec.push_back(placeData.data);
                break;
            }
        }
    }
}
/// <summary>
/// �ҏW����o�^
/// </summary>
void StageDataEditor::OnPut(PlacementData placeData)
{
    //�ĕҏW���[�h�Ȃ�Y���ӏ��̃f�[�^�������ւ�
    if (isReEdit && placeData.objKind != PLAYER_NUMBER)
    {
        //���W�A�C�e����ҏW���ĕʂ̂��̂ɕς����Ȃ�ő吔�����炷
        if (editedPlacementDataVec[editNum].objKind == COLLECT_NUMBER &&
            placeData.objKind != COLLECT_NUMBER)
        {
            collectNum--;
            appearFaseNum = appearFaseNum < collectNum ? appearFaseNum : collectNum - 1;
        }
        if(placeData.objKind == COLLECT_NUMBER)//�ĕҏW�������̂����W�A�C�e���Ȃ�
        {
            placeData.collectNum = collectNum;
            appearFaseNum = collectNum;
            collectNum++;
        }
        //�ĕҏW��ƑO�����ւ�
        std::swap(editedPlacementDataVec[editNum], placeData);
    }
    else//�V�K�o�^��
    {
        switch (placeData.objKind)
        {
        case COLLECT_NUMBER://���W�A�C�e���̐�����������
            placeData.collectNum = collectNum;
            appearFaseNum = collectNum;
            collectNum++;
            //�V�����ҏW�I�u�W�F�N�g���R���e�i�ɔ[�i
            editedPlacementDataVec.push_back(placeData);
            break;
            //�v���C���[�͈�����ł����̂ŕϐ��Ɏ��[
        case PLAYER_NUMBER:
            playerData = placeData;
            break;
        default:
            //���ڂ̃A�C�e��������������ŏo�Ă��邩�ݒ肷��
            placeData.collectNum = appearFaseNum;
            //�V�����ҏW�I�u�W�F�N�g���R���e�i�ɔ[�i
            editedPlacementDataVec.push_back(placeData);
            break;
        }
    }
    //�z�u�����烍�O�Ɏc��
    log->SaveEditDataLog(prevNum,CONTAINER_GET_SIZE(editedPlacementDataVec),editNum,placeData);
    //�ЂƂO�̏�Ԃɖ߂������Z�b�g
    prevNum = 0;
}