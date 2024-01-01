#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "DxLib.h"
#include "UIManager.h"
class Timer;
/// <summary>
/// �J�E���g�_�E����UI
/// </summary>
class CountDown
{
public:
    /// <summary>
    /// �J�E���g�_�E����UI
    /// </summary>
    /// <param name="setTimer">���̃^�C�}�[�̎c�莞�Ԃ�3�b�O����J�E���g�_�E������</param>
    CountDown(std::weak_ptr<Timer> setTimer);
    /// <summary>
    /// �^�C�}�[�̉�� UI�폜
    /// </summary>
    ~CountDown();
    /// <summary>
    /// �^�C�}�[��i�܂���UI�̐�����ύX����
    /// </summary>
    void Update();
    /// <summary>
    /// �J�E���g�_�E���̐����̕`��
    /// </summary>
    virtual void DrawUI()const;
    /// <summary>
    /// �J�E���g�_�E�����I�������
    /// </summary>
    /// <returns></returns>
    bool IsCountDownEnd()const;
    /// <summary>
    /// �J�E���g�_�E���̉�����I�������
    /// </summary>
    /// <returns></returns>
    bool IsPlayCountDownSound()const;
protected:
    //�J�E���g�_�E���𐔂���^�C�}�[
    std::weak_ptr<Timer> timer;
    //�J�E���g�_�E����UI
    UIData countDownUIData;
    //�I��莞��UI
    UIData endUIData;
    //�J�E���g�_�E�����I�������
    bool isCountDownEnd = false;
    //�J�E���g�_�E�����ʉ���炵����
    bool isPlayedCountSE = false;
    //�J�E���g�_�E��UI�̉摜��ύX���邽�߂̓Y����
    int uiHIndex = -1;
};