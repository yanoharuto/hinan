#pragma once
#include "UIManager.h"
/// <summary>
///�@�_�ł��Ȃ���`�悷��UI
/// </summary>
class FlashUI
{
public:
    /// <summary>
    /// �_�ŕ\��������UI�������ɓn��
    /// </summary>
    /// <param name="uiKind"></param>
    FlashUI(UIKind uiKind);
    /// <summary>
    /// pressKeyData�̍폜
    /// </summary>
    ~FlashUI();
    /// <summary>
    /// �A���t�@�l�̍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// ���X�ɔ����Ȃ�����Z���Ȃ����肵�Ȃ���`��
    /// </summary>
    void Draw()const;
private:
    //�X�y�[�X�L�[UI
    UIData pressKeyUIData;
    //�A���t�@�l
    int aValue;
    //�A���t�@�l�̑������x
    const int aSpeed = 10;
    //�A���t�@�l�̍Œ�l
    const int lowtestAvalue = 60;
    //�A���t�@�l�𑝂₷���ǂ���
    bool isAValueIncrement = false;
};