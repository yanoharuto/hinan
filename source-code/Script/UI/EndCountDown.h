#pragma once
#include "CountDown.h"
/// <summary>
/// �Q�[���I�����̃J�E���g�_�E��
/// </summary>
class EndCountDown final: public CountDown
{
public:
    /// <summary>
    /// �^�C�}�[���؂ꂻ���ɂȂ�����J�E���g�_�E����\������
    /// </summary>
    /// <param name="timer">�c�莞�Ԃ̃^�C�}�[</param>
    EndCountDown(std::weak_ptr<Timer> timer);
    /// <summary>
    /// �J�E���g�_�E���̐����ƏI����\��
    /// </summary>
    void DrawUI()const;
private:
    //�J�E���g�_�E���̐����𔖂��\��
    const int aValue = 130;
};

