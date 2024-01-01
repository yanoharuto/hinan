#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "UIManager.h"

class NumUI;
class Timer;
class CountDown;
class PlayManual;
class ReusableTimer;
class CollectItemObserver;
/// <summary>
/// ���[�X�O�̏�������Ă����
/// </summary>
class PrePlayGameProcess
{
public:
    /// <summary>
    /// ���������J�E���g�_�E���B���Ȃǂ�����
    /// </summary>
    /// <param name="collectObserver">��������邩�����Ă��炤</param>
    PrePlayGameProcess(std::weak_ptr<CollectItemObserver> collectObserver);
    /// <summary>
    /// �J�E���g�_�E���Ȃǂ����
    /// </summary>
    ~PrePlayGameProcess();
    /// <summary>
    /// �J�E���g�_�E���̍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �V�ѕ��ƃJ�E���g�_�E���̕`��
    /// </summary>
    void Draw() const;
    /// <summary>
    /// �������I��������
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess();
private:
    //���W���̃A�C�R��
    UIData collectIconUIData;
    //���������UI
    std::unique_ptr<PlayManual> playManual;
    //�Q�[���̖ڕW
    UIData gamePuroseUIData;
    //���W�A�C�e���̏W�߂鐔
    std::unique_ptr<NumUI> collectItemNum;
    //�R�}����p�^�C�}�[
    std::unique_ptr<ReusableTimer> frameByFrameTimer;
    //�J�E���g�_�E���p�̃^�C�}�[
    std::shared_ptr<Timer> countDownTimer;
    //�Q�[�����n�߂�O�̃J�E���g�_�E��
    std::unique_ptr<CountDown> countDown;
    //�����I��������
    bool processEnd = false;
    //���W�A�C�e���A�C�R���̃R�}����ԍ�
    int iconGHIndex = 0;
    //�Q�[���̖ڕW���������Ă���Ԃ͎���𔒂�����
    int fadeValue = 0;
    //���W�A�C�e���̐�
    int remainingCollectNum = 0;
    //�X�^�[�g�̃J�E���g�_�E����5�b
    const float startTimerLimit = 5;
};