#pragma once
#include "Actor.h"
#include<iostream>
#include<memory>
class DamageObjectGenerator;
/// <summary>
/// �~��ɐw�`��g�݃��[�U�[�𔭎˂����s�D
/// </summary>
class CircleLaserFlyShip : public Actor,std::enable_shared_from_this<CircleLaserFlyShip>
{
public:
    /// <summary>
    /// �ʒu�ƌ��������������ă��[�U�[�𔭎�
    /// </summary>
    /// <param name="setPos">�ʒu</param>
    /// <param name="setDestinationPos">�����ׂ������̈ʒu</param>
    /// <param name="damageObjectGenerator">���[�U�[�𔭎˂��邱�Ƃ�`����N���X</param>
    CircleLaserFlyShip(VECTOR setPos, VECTOR setDestinationPos,std::weak_ptr<DamageObjectGenerator> damageObjectGenerator);
};

