#pragma once
#include "Actor.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// ���[�U�[���o����s�D
/// </summary>
class LaserFlyShip abstract : public Actor
{
public:
    /// <summary>
    /// ������ �ړI�n�̕��Ɍ�������
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    LaserFlyShip(ObjectInit::InitObjKind kind);
protected:
    //�����ʒuY
    float firstPosY;
};
