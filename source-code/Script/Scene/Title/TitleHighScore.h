#pragma once
#include "NumUI.h"
/// <summary>
/// �^�C�g���ŕ\������n�C�X�R�A
/// </summary>
class TitleHighScore : private NumUI
{
public:
    /// <summary>
    /// �^�C�g���ŕ\������n�C�X�R�A
    /// </summary>
    TitleHighScore();
    /// <summary>
    /// ���ݑI�΂�Ă���X�e�[�W�̃n�C�X�R�A�\��
    /// </summary>
    void Draw()const;
private:
    //�e�X�e�[�W�̃n�C�X�R�A
    UIData highScoreUI;
};

