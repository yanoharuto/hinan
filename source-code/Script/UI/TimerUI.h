#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "UIManager.h"
class Timer;
class NumUI;
/// <summary>
/// �c�莞�Ԃ�`�悷��
/// </summary>
class TimerUI
{
public:
    /// <summary>
    /// �c�莞�Ԃ̃Z�b�g�Ɛ����摜�̓ǂݍ���
    /// </summary>
    /// <param name="setTimer">�c�莞�ԃ^�C�}�[</param>
    TimerUI(std::weak_ptr<Timer> setTimer);
    /// <summary>
    /// �^�C�}�[�̃��b�N���� UI�폜
    /// </summary>
    ~TimerUI();
    //�c�莞�Ԃ�`�悷��
    void Draw();
private:
    //�����̃t�H���g�摜
    UIData frameUIData;
    //�����_
    UIData pointUIData;
    //�^�C�}�[�̘g�̉��ʒu
    int frameX;
    //�c�莞�Ԃ���������p
    std::weak_ptr<Timer> timer;
    //������`�悷��
    std::unique_ptr<NumUI> numUI = nullptr;
};