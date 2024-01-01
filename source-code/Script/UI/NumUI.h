#pragma once
#include <string>
#include "UIManager.h"
#define TIMER_FONT_NUM 10
/// <summary>
/// ������`�悷��@������
/// </summary>
class NumUI
{
public:
    /// <summary>
    /// ������`�悷��
    /// </summary>
    NumUI(UIKind kind);
    /// <summary>
    /// UI�폜
    /// </summary>
    ~NumUI();
    /// <summary>
    /// �����̕`��
    /// </summary>
    /// <param name="num">����</param>
    virtual void Draw(int num)const;
    /// <summary>
    /// �����̕`��@�����_�t��
    /// </summary>
    /// <param name="num">����</param>
    void Draw(float num) const;
    /// <summary>
    /// �ꕶ���̑傫��
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
protected:
    /// <summary>
    /// �����̕`��
    /// </summary>
    /// <param name="x">��ԉE�[</param>
    /// <param name="y">Y���W</param>
    /// <param name="num">����</param>
    /// <param name="scale">�����̑傫��</param>
    /// <returns>���[�̍��W</returns>
    int Draw(UIData data, int num)const;
    //�����̃f�[�^
    UIData numUIData;
    //�����_�̉摜
    UIData pointUIData;
};