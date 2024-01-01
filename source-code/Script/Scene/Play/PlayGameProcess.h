#pragma once
#include <iostream>
#include <memory>
class PlayerObserver;
class GamePlayUI;
class CollectItemObserver;
class StopTimer;
class Timer;
/// <summary>
/// �Q�[�����̏�����
/// </summary>
class PlayGameProcess
{
public:
    /// <summary>
    /// BGM�ƃQ�[���I���^�C�}�[���N��
    /// </summary>
    /// <param name="player">UI�Ƀv���C���[����n��</param>
    /// <param name="collectItemObserver">UI�Ɏ��W�A�C�e������n��</param>
    PlayGameProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<CollectItemObserver> const collectItemObserver);
    /// <summary>
    /// UI�ƃ^�C�}�[�̉��
    /// </summary>
    ~PlayGameProcess();
    /// <summary>
    /// �V��ł���Ƃ��̍X�V
    /// </summary>
    /// <param name="collectObserver">���W�A�C�e���̎c�萔�������Ă��炤</param>
    void Update(std::weak_ptr<CollectItemObserver> const collectObserver);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �Q�[�������̏����̏I��
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const
    {
        return isEndProcess;
    };
    /// <summary>
    /// �Q�[���̎c�莞�ԃ^�C�}�[��n��
    /// </summary>
    /// <returns> �Q�[���̎c�莞�ԃ^�C�}�[��n��</returns>
    std::shared_ptr<Timer> GetGameTimer();
    
private:
    //�������Ԃ̃^�C�}�[
    std::shared_ptr<StopTimer> timer;
    //�V��ł���Ƃ���UI
    GamePlayUI* playUI;
    //�����I���t���O
    bool isEndProcess = false;
    //�ŏ��̍X�V�t���O
    bool isFirstUpdate = true;
};