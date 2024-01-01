#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// 輪になっているレーザー照射機の更新とかする
/// </summary>
class CircleFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// レーザーを発射できるようにGeneratorを確保
    /// </summary>
    /// <param name="generator">レーザー発射に必要なクラス</param>
    CircleFlyShipController(std::shared_ptr<DamageObjectGenerator> generator);
private:
    /// <summary>
    /// 輪になっているレーザー照射機の配置と追加
    /// </summary>
    /// <param name="arrangementData">配置に必要な情報</param>
    void AddObject(PlacementData arrangementData);
};

