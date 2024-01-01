#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"
#include "ObjectObserver.h"
/// <summary>
/// 位置と向きを初期化してレーザーを発射
/// </summary>
/// <param name="setPos">位置</param>
/// <param name="setDestinationPos">向くべき方向の位置</param>
/// <param name="damageObjectGenerator">レーザーを発射することを伝えるクラス</param>
CircleLaserFlyShip::CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos, std::weak_ptr<DamageObjectGenerator> damageObjectGenerator)
    :Actor(ObjectInit::InitObjKind::circleLaserShip)
{
    position.x = firstPos.x;
    position.z = firstPos.z;
    setDestinationPos.y = position.y;
    direction = VNorm(VSub(setDestinationPos, position));
    std::unique_ptr<ObjectObserver> observer = std::make_unique<ObjectObserver>(shared_from_this());
    //レーザーを発射
    damageObjectGenerator.lock()->GenerateDamageObject(DamageObjectGenerator::laser, std::move(observer));
}