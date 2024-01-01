#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "DrawModel.h" 
/// <summary>
/// 上下に移動する飛行船の管理準備
/// </summary>
/// <param name="damageObjeGenerator">レーザーを発射できるようにする</param>
UpDownFlyShipController::UpDownFlyShipController(std::shared_ptr<DamageObjectGenerator> damageObjeGenerator)
    :FlyShipController(InitObjKind::upDownLaserShip,damageObjeGenerator)
{
    drawModel = std::make_unique<DrawModel>(InitObjKind::upDownLaserShip);
}
/// <summary>
/// 上下に対空する飛行船を引数の位置に追加
/// </summary>
/// <param name="editData">配置位置</param>
void UpDownFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(std::make_shared<UpDownLaserFlyShip>(editData, damageObjectGenerator));
}