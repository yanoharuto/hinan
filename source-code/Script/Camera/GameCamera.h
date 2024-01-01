#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class PlayerObserver;
/// <summary>
/// �V��ł���Ƃ��̃J����
/// </summary>
class GameCamera final : public Camera
{
public:
    /// <summary>
    /// �V��ł���Ƃ��̃J�����̏�����
    /// </summary>
    /// <param name="player">�v���C���[�̈ʒu</param>
    GameCamera(std::shared_ptr<PlayerObserver>& player);
    /// <summary>
    /// �ʒu������̍X�V
    /// </summary>
    void Update();
};

