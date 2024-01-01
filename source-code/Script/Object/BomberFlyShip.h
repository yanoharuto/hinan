#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "Actor.h"
#include "EditObjectData.h"

class Timer;
class ReusableTimer;
class DamageObjGenerator;
/// <summary>
/// �����@
/// </summary>
class BomberFlyShip : public Actor,std::enable_shared_from_this<BomberFlyShip>
{
public:
    /// <summary>
    /// �����̈ʒu�ɐ����@
    /// </summary>
    /// <param name="data">�����ʒu�ƌ������������\����</param>
    /// <param name="initParam">���e���˃N�[���^�C��������</param>
    /// <param name="damageObjGenerator">���e���˂ɕK�v�ȃN���X</param>
    BomberFlyShip(PlacementData data,float coolTime,std::shared_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// damageObjectGenerator�̊J��
    /// </summary>
    ~BomberFlyShip();
    /// <summary>
    /// ���e�𗎂Ƃ��Ȃ���i��
    /// </summary>
    void Update() override;
private:
    //���e�𗎂Ƃ�����
    std::unique_ptr<ReusableTimer> bombFallTimer;
    //���e�𐶐�����̂ɕK�v�ȃN���X
    std::shared_ptr<DamageObjectGenerator> damageObjectGenerator;
};