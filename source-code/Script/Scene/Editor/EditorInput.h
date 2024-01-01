#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "UIManager.h"
#include "UIDrawer.h"
//���͂��邽�߂ɕK�v�ȃ}�E�X�̉^����
constexpr int INPUT_RANGE = 60;
constexpr int EDIT_MODE_KIND = 12;
class MouseInput;
class EditorUI;
/// <summary>
/// �}�E�X�ŕҏW����Ƃ��ɉ�����͂�����
/// �m�点��N���X
/// </summary>
class EditorInput
{
public:
    /// <summary>
    /// �ҏW�̓��͓��e��ύX
    /// </summary>
    EditorInput();
    /// <summary>
    /// ���N���b�N�������Ă���Ƃ��͕ҏW������ύX�E���肷��
    /// </summary>
    void Update(std::weak_ptr<MouseInput>& input,std::weak_ptr<EditorUI>& ui);
    //���N���b�N���Ƀ}�E�X���ړ�������Ǝg����@�\
    enum class EditMode
    {
        //�������͂��Ă��Ȃ����͈ړ�
        Move,
        //�I�u�W�F�N�g����]������
        Rotate,
        //�폜
        Delete,
        //�z�u
        Put,
        //�o�Ă���^�C�~���O�̕ύX
        ChangeFase,
        //�������Ԃ̒���
        ChangeTimeLimit,
        //�J�����̊g��k��
        ScalingCameraBetween,
        //�ЂƂO�̏�Ԃɖ߂�
        BackEditState,
        //�������Ă��Ȃ���
        Free,
        //�V�����I�u�W�F�N�g��z�u����@�ĕҏW����
        SelectObject,
        //�ҏW����蒼��
        StepEditState,
        //�ҏW�����X�e�[�W��V��
        PlayEditStage,
    };
    /// <summary>
    /// ����������ׂ����Ԃ��@
    /// </summary>
    /// <returns>����������ׂ����Ԃ�.���{�^���𒷉����Ȃ�HoldLeftButton���Ԃ�</returns>
    EditorInput::EditMode GetEditMode()const;
    
private:
    //��������͂�����
    EditMode inputMode;
    //��]���[�h�t���O
    bool isRotateMode = true;
    //�ҏW�t���O
    bool isEditObject = false;
    //���{�^�����������̃}�E�XX���W
    int holdMouseX;
    //���{�^�����������̃}�E�XY���W
    int holdMouseY;
};