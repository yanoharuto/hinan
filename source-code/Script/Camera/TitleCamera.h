#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;

/// <summary>
/// �^�C�g����ʂ̃J�����@�Ԃ̎΂ߐ��ʂ��f��
/// </summary>
class TitleCamera : public Camera
{
public:

    /// <summary>
    /// �^�C�g����ʂ̃J�����@�Ԃ̎΂ߐ��ʂ��f��
    /// </summary>
    TitleCamera(std::shared_ptr<ObjectObserver>& player);

    /// <summary>
    /// �v���C���[�̈ʒu�ɍ��킹�ăJ�������t���Ă���
    /// </summary>
    void Update();
private:
    //�Ԃ𐳖ʂ��猩�Ȃ��悤�ɂ��邽�߂��炷�p�x�̗�
    float cameraRotate = 80.0f;
};