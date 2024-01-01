#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// 上下に移動する飛行艇
/// </summary>
class UpDownFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// 上下に移動する飛行船の管理準備
    /// </summary>
    /// <param name="damageObjeGenerator">レーザーを発射できるようにする</param>
    UpDownFlyShipController(std::shared_ptr<DamageObjectGenerator> damageObjeGenerator);
protected:
    /// <summary>
    /// 上下に対空する飛行船を引数の位置に追加
    /// </summary>
    /// <param name="editData">配置位置</param>
    void AddObject(PlacementData editData)override;

};

