#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
#include "DrawModel.h"
/// <summary>
/// 爆撃機の初期化と爆弾発射準備
/// </summary>
/// <param name="generator">爆弾を発射できるクラス</param>
BomberFlyShipController::BomberFlyShipController(std::shared_ptr<DamageObjectGenerator> generator)
    :FlyShipController(InitObjKind::bomberShip,generator)
{
    drawModel = std::make_unique<DrawModel>(InitObjKind::bomberShip);
}
/// <summary>
/// 爆撃機を追加する
/// </summary>
/// <param name="editData">配置情報</param>
void BomberFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(std::make_shared<BomberFlyShip>(editData, param.setCoolTime, damageObjectGenerator));
}
