#pragma once
#include <string>
#include "DamageObject.h"
#include "EffectManager.h"
class LaserCollider;
class ObjectObserver;
/// <summary>
/// ��]���[�U�[
/// </summary>
class RotatingLaser :public DamageObject
{
public:
    /// <summary>
    /// ���[�U�[�̃G�t�F�N�g��ǂݍ��݈ʒu�������̃I�u�W�F�N�g����o��
    /// </summary>
    /// <param name="setObserver">���˃I�u�W�F�N�g�̈ʒu����ʒB���Ă��炤</param>
    RotatingLaser(std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// �G�t�F�N�g�Ɠ����蔻��̍폜
    /// </summary>
    ~RotatingLaser()override;
    /// <summary>
    /// ���[�U�[����]������@���˂��Ă���I�u�W�F�N�g�̈ʒu��Ǐ]����
    /// </summary>
    void Update();
private:
    /// <summary>
    /// ���[�U�[��y����]
    /// </summary>
    void YRotate();
    /// <summary>
    /// ���[�U�[�Ղ��o��
    /// </summary>
    void SetLaserTrack();
    //���[�U�[�̐Ղ̈ʒu
    VECTOR laserTrackPos = {};
    //���󓖂��蔻��
    LaserCollider* collider;
    //�G�t�F�N�g�n���h��
    int laserEffect = -1;
    //�Ă���
    int trackEffect = -1;
    //�G�t�F�N�g�̉�]�p�i���W�A���j
    float effectRota;
    //��]���x
    static const float rotaSpeed;
    //��]���a
    static const float rotateRadius;
};