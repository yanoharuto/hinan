#pragma once
#include "UIManager.h"
#include "UserInput.h"
/// <summary>
/// ���������`�悷��
/// </summary>
class PlayManual
{
public:
    /// <summary>
    /// �摜��ǂݍ���
    /// </summary>
    PlayManual();
    /// <summary>
    /// UI�폜
    /// </summary>
    ~PlayManual();
    /// <summary>
    /// �v���C���[�̓��͂ɂ���đ��������ς���
    /// </summary>
    void Update();
    /// <summary>
    /// ��������̕`��
    /// </summary>
    void Draw()const;
private:
    //�`�悷�鑀����@�f�[�^
    UIData playManualUIData = {};
    //������@�̉��Ɉ����g
    UIData sheatUIData = {};
    //�`�悵����������@
    UIKind nowUIKind = UIKind::manual;
    //�e�L�[�̑�����@
    struct ButtonUI
    {
        UIData data = {};
        bool push = false;
    };
    //���{�^������UI
    ButtonUI leftBUI;
    //�E�{�^������UI
    ButtonUI rightBUI;
    //���{�^������UI
    ButtonUI downBUI;
};