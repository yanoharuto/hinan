#pragma once
#include <iostream>
#include <memory>
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class PlayerObserver;
class EndCountDown;
class EnemyGenerator;
class CollectCompass;
class PlayManual;
class CollectItemObserver;
class ReusableTimer;
/// <summary>
/// �V��ł���Ƃ���UI
/// </summary>
class GamePlayUI final
{
public:
    /// <summary>
    /// �v���C���[�␧�����ԁA���W�A�C�e���̐��Ȃǂ�\���ł���悤�ɂ���
    /// </summary>
    /// <param name="player">�v���C���[�̈ʒu</param>
    /// <param name="timer">��������</param>
    /// <param name="collectItemObserver">���W�A�C�e�����</param>
    GamePlayUI(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer, std::shared_ptr<CollectItemObserver> collectItemObserver);
    /// <summary>
    /// �eUI�����
    /// </summary>
    ~GamePlayUI();
    /// <summary>
    /// �~�j�}�b�v�̍X�V����W�A�C�e���̖������X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()const;
private:
    //�ŏ��̎��W�A�C�e���̖���
    int allCollectNum = 0;
    // �v���C���[��������������
    int nowGetCollectNum = 0;
    //�c��̎��W�A�C�e������\�����邩
    bool isDrawGetNum = false;
    //�c��̎��W�A�C�e������\�����鎞��
    float remainingNumDrawTime = 2.0f;
    //�c�������W�A�C�e���̐��̕\�����Ԃ��v��
    std::unique_ptr<ReusableTimer> remainingNumDrawTimer = nullptr;
    //�Q�[���c�莞�ԃ^�C�}�[
    std::unique_ptr<TimerUI> gameTimerUI;
    //�~�j�}�b�v
    std::unique_ptr<MiniMap> minimapUI;
    //�ŏ��̎��W�A�C�e���̖�����`�悷��N���X
    std::unique_ptr<NumUI> firstCollectNumUI;
    //�Q�b�g�������W�A�C�e���̖�����`��
    std::unique_ptr<NumUI> getNumUI;
    //�c�������W�A�C�e���̐�
    std::unique_ptr<NumUI> remainingNumUI;
    //�c����W�A�C�e���ɂ��Ẵt���[�Y
    UIData remainingFrazeUIData;
    //�����̊Ԃɒu���X���b�V��
    UIData frameUIData;  
    //�J�E���g�_�E��
    std::unique_ptr<EndCountDown> countDown;
    //�v���C���[�̈ʒu�Ƃ����W�A�C�e���̏������Ȃǂ������Ă����z
    std::weak_ptr<PlayerObserver> playerObserver;
    //���W�A�C�e���̕����Ƃ��������Ă����
    std::unique_ptr<CollectCompass> collectCompass;
    //�v���C���[�̑�����@
    std::unique_ptr<PlayManual> playManual;
};