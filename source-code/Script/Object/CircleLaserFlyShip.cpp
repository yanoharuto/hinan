#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"
#include "ObjectObserver.h"
/// <summary>
/// �ʒu�ƌ��������������ă��[�U�[�𔭎�
/// </summary>
/// <param name="setPos">�ʒu</param>
/// <param name="setDestinationPos">�����ׂ������̈ʒu</param>
/// <param name="damageObjectGenerator">���[�U�[�𔭎˂��邱�Ƃ�`����N���X</param>
CircleLaserFlyShip::CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos, std::weak_ptr<DamageObjectGenerator> damageObjectGenerator)
    :Actor(ObjectInit::InitObjKind::circleLaserShip)
{
    position.x = firstPos.x;
    position.z = firstPos.z;
    setDestinationPos.y = position.y;
    direction = VNorm(VSub(setDestinationPos, position));
    std::unique_ptr<ObjectObserver> observer = std::make_unique<ObjectObserver>(shared_from_this());
    //���[�U�[�𔭎�
    damageObjectGenerator.lock()->GenerateDamageObject(DamageObjectGenerator::laser, std::move(observer));
}