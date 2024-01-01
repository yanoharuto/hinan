#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "UIManager.h"
#include "UIDrawer.h"
//���͂��邽�߂ɕK�v�ȃ}�E�X�̉^����
constexpr int INPUT_RANGE = 60;
class MouseInput;
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
    void Update(std::weak_ptr<MouseInput> input);
    //���N���b�N���Ƀ}�E�X���ړ�������Ǝg����@�\
    enum class EditMode
    {
        //�������͂��Ă��Ȃ����͈ړ�
        Move,
        //�I�u�W�F�N�g����]������
        Rotate,
        //�ЂƂO�̏�Ԃɖ߂�
        BackPrevState,
        //�폜
        Delete,
        //�z�u
        Put,
        //�o�Ă���^�C�~���O�̕ύX
        ChangeFase,
        //�������Ԃ̒���
        ChangeTimeLimit,
        //�J�����̊g��k��
        ScalingCamera,
        //�������Ă��Ȃ���
        Free,
        //�V�����I�u�W�F�N�g��z�u����@�ĕҏW����
        SelectObject,
        //���{�^�����������Ƒ��̑I�������o���ԂɂȂ��Ă���
        HoldButton,
        //�ҏW�����X�e�[�W��V��
        PlayEditStage,
    };
    /// <summary>
    /// ����������ׂ����Ԃ��@
    /// </summary>
    /// <returns>����������ׂ����Ԃ�.���{�^���𒷉����Ȃ�HoldLeftButton���Ԃ�</returns>
    EditorInput::EditMode GetEditMode()const;
    /// <summary>
    /// ��������̕`��
    /// </summary>
    void Draw()const;
private:
    /// <summary>
    /// ���{�^���������ŕҏW������e��ς���
    /// </summary>
    void HoldChangeLeftMode(int mouseX,int mouseY);
    /// <summary>
    /// �E�{�^���������ŕҏW������e��ς���
    /// </summary>
    void HoldChangeRightMode(int mouseX,int mouseY);
    
    /// <summary>
    /// �}�E�X���{�^�����������Ȃ瑀�����
    /// </summary>
    /// <param name="format"></param>
    void DrawFormat(UIDrawer::Format format)const;
    //�`�悵����������ƈʒu
    UIDrawer::Format manual[8] = {
        {
            -INPUT_RANGE,0,"�ړ�"
        },
        {
            -INPUT_RANGE,0,"��]"
        },
        {
            INPUT_RANGE,0,"�ЂƂO�ɖ߂�"
        },
        {
            0,INPUT_RANGE,"�폜"
        },
        {
            0,-INPUT_RANGE,"�z�u"
        },
        {
            INPUT_RANGE,0,"�t�F�[�Y"
        },
        {
              -INPUT_RANGE,0,"��������"
        },
        {
            0,INPUT_RANGE,"�J����"
        },
    };
    //���������邩
    EditMode leftMode;
    //�E�{�^���z�[���h�����Ƃ��̃��[�h
    EditMode rightMode;
    //�����̐F
    unsigned int formatColor = GetColor(255,255,255);
    //��]���[�h�t���O
    bool isRotateMode = true;
    //�ĕҏW���[�h
    bool isEditObject = false;
    //���{�^�����z�[���h���Ă��邩
    bool isLeftHold = false;
    //�E�{�^�����z�[���h���Ă��邩
    bool isRightHold = false;
    //���{�^�����������̃}�E�XX���W
    int holdMouseX;
    //���{�^�����������̃}�E�XY���W
    int holdMouseY;
    //�ҏW�����X�e�[�W��V��
    UIData playEditStageUI;
};