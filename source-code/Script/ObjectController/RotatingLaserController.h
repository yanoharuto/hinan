#pragma once
#include <vector>
#include "DamageObjectController.h"
class ObjectObserver;
/// <summary>
/// y����]������肷�郌�[�U�[
/// </summary>
class RotatingLaserController : public DamageObjectController
{
public:
    /// <summary>
    /// �ǉ��ƕ`��̏���
    /// </summary>
    /// <param name="generator">���[�U�[������</param>
    RotatingLaserController();
    /// <summary>
    /// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
    /// </summary>
    /// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
private:
    //��]���a
    static const float rotateRadius;
};