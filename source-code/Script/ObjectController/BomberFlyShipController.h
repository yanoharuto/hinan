#pragma once
#include "FlyShipController.h"
/// <summary>
/// 爆撃機管理クラス
/// </summary>
class BomberFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// 爆撃機の初期化と爆弾発射準備
    /// </summary>
    /// <param name="generator">爆弾を発射できるクラス</param>
    BomberFlyShipController(std::shared_ptr<DamageObjectGenerator> generator);
    /// <summary>
    /// 爆撃機を追加する
    /// </summary>
    /// <param name="editData">配置情報</param>
    void AddObject(PlacementData editData)override;
};

