#pragma once
#include "NumUI.h"
#include "DxLib.h"
#include "UIManager.h"
/// <summary>
/// ���v�X�R�A�̕\��
/// </summary>
class ScoreNum : private NumUI
{
public:
    /// <summary>
    /// �X�R�A�̕]���̐�����������
    /// </summary>
    ScoreNum();
    /// <summary>
    /// highScoreUI�̍폜
    /// </summary>
    ~ScoreNum();
    /// <summary>
    /// �X�R�A�ɂ���đ傫���ύX
    /// </summary>
    /// <param name="num">���vscore</param>
    void Draw(int num)const override;
private:
    //�O��̃n�C�X�R�A
    int prevHiScore = 0;
    //���ɃN���A�����Ƃ��̃X�R�A�̃��C��
    int first = 0;
    //���ʂɃN���A�����Ƃ��̃X�R�A�̃��C��
    int second = 0;
    //�Ȃ�Ƃ��N���A�����Ƃ��̃X�R�A�̃��C��
    int third = 0;
    //second����̃X�R�A�ɂȂ������̕����̃t�H���g
    float secondBorderFontSize = 0.9f;
    //third����̃X�R�A�ɂȂ������̕����̃t�H���g
    float thirdBorderFontSize = 0.85f;
    //third��艺�̃X�R�A�ɂȂ������̕����̃t�H���g
    float thirdUnderFontSize = 0.8f;
    //�n�C�X�R�A�̕\�L
    UIData highScoreUIData;
    //��Ԃ����X�R�A�̐F
    VECTOR firstColor = VGet(255,215,0);
    //������Ƃ����Ƃ��̐F
    VECTOR thirdColor = VGet(196,112,34);
    //��Ԗڂɂ������̐F
    VECTOR secondColor = VGet(192, 192, 192);
    //�ŏ��ɂȂ��Ă���X�R�A�̐F
    VECTOR thirdUnderColor = VGet(100,100,100);
};