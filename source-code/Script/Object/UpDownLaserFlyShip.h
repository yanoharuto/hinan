#pragma once
#include  <memory>
#include  <iostream>
#include "Actor.h"
#include "EditObjectData.h"
class DamageObjectGenerator;
/// <summary>
/// �㉺�ɓ����Ȃ��烌�[�U�[���o�����
/// </summary>
class UpDownLaserFlyShip : public Actor,std::enable_shared_from_this<UpDownLaserFlyShip>
{
public:
    /// <summary>
    /// �����ʒu�̐ݒ�ƃ��[�U�[�𔭎�
    /// </summary>
    /// <param name="setPos">�����ʒu</param>
    /// <param name="damageObjGenerator">���[�U�[�𔭎˂��邱�Ƃ�`����N���X</param>
    UpDownLaserFlyShip(PlacementData setPos,std::weak_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// �㉺�ɓ�����
    /// </summary>
    void Update() override;
private:
    //totalMoveValue�̑�����
    static const float addMoveValue;
    //�㉺�ɓ������x
    static const float updownSpeed;
    //�������x
    static float firstPosY;
    //��������
    float totalMoveValue = 0;
};

