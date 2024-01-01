#pragma once
#include <iostream>
#include<memory>
class PlayerObserver;
/// <summary>
/// ���𕷂��Ă���I�u�W�F�N�g�̏ꏊ���X�V
/// </summary>
class SoundListener
{
public:
    /// <summary>
    /// ���𕷂���̃|�C���^�[��Ⴄ
    /// </summary>
    /// <param name="listener"></param>
     SoundListener(std::weak_ptr<PlayerObserver> listener);
     /// <summary>
    /// ���L�|�C���^�����Z�b�g
    /// </summary>
     ~SoundListener();
    /// <summary>
    /// ���X�i�[�̈ʒu�𔽉f
    /// </summary>
    void Update();
private:
    
    //���𕷂��Ă���I�u�W�F�N�g
    std::weak_ptr<PlayerObserver> listener;
};

