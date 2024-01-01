#include "UpDownLaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "ObjectObserver.h"
//totalMoveValueの増加量
const float UpDownLaserFlyShip::addMoveValue = 0.05f;
//上下に動く速度
const float UpDownLaserFlyShip::updownSpeed = 6.0f;
//初期高度
float UpDownLaserFlyShip::firstPosY = 0.0f;
/// <summary>
/// 初期位置の設定とレーザーを発射
/// </summary>
/// <param name="editData">初期位置</param>
/// <param name="damageObjGenerator">レーザーを発射することを伝えるクラス</param>
UpDownLaserFlyShip::UpDownLaserFlyShip(PlacementData editData, std::weak_ptr<DamageObjectGenerator> damageObjGenerator)
    :Actor(ObjectInit::InitObjKind::upDownLaserShip)
{
    firstPosY = position.y;
    //位置と向きの初期化
    position.x = editData.posX;
    position.z = editData.posZ;
    direction = VGet(editData.dirX, 0, editData.dirZ);
    //レーザーを発射
    damageObjGenerator.lock()->GenerateDamageObject(DamageObjectGenerator::laser, std::make_unique<ObjectObserver>(shared_from_this()));
}
/// <summary>
/// 上下に動くよ
/// </summary>
void UpDownLaserFlyShip::Update()
{
    //上下に移動
    totalMoveValue += addMoveValue;
    position.y = cosf(totalMoveValue) * updownSpeed + firstPosY;
}