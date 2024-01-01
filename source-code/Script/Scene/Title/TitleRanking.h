#pragma once
#include "UIManager.h"
#include "DxLib.h"
#include <memory>
#include <iostream>
class NumUI;
/// <summary>
/// �^�C�g���Ŋe�X�e�[�W�̃X�R�A�����L���O��ʎO����`��
/// </summary>
class TitleRanking
{
public:
    /// <summary>
    /// �^�C�g���Ŋe�X�e�[�W�̃X�R�A�����L���O��ʎO����`��
    /// </summary>
    TitleRanking();
    /// <summary>
    /// �����L���O���\�����鐔��UI������
    /// </summary>
    ~TitleRanking();
    /// <summary>
    /// �����L���O�̏�ʎO����`��
    /// </summary>
    void Draw()const;
private:
    /// <summary>
    /// �����̗v�f��`��
    /// </summary>
    /// <param name="ui">�g�����������`��UI</param>
    /// <param name="num">�`�悵��������</param>
    /// <param name="color">�����̐F</param>
    void Draw(NumUI* ui,int num,VECTOR color)const;
    //���̃X�e�[�W�̒��ň�Ԃ����X�R�A
    std::unique_ptr<NumUI> highUI;
    //2�Ԗڂɗǂ��X�R�A
    std::unique_ptr<NumUI> secondUI;
    //3�Ԗڂɂ����X�R�A
    std::unique_ptr<NumUI> thirdUI;
    //�P�̏���UI
    std::unique_ptr<NumUI> highRankUI;
    //�Q�̏���UI
    std::unique_ptr<NumUI> secondRankUI;
    //3�̏���UI
    std::unique_ptr<NumUI> thirdRankUI;
    //�����L���O
    UIData rankUIData;

    //��Ԃ����X�R�A�̐F
    const VECTOR firstColor = VGet(255, 215, 0);
    //������Ƃ����Ƃ��̐F
    const VECTOR thirdColor = VGet(196, 112, 34);
    //��Ԗڂɂ������̐F
    const VECTOR secondColor = VGet(192, 192, 192);
};