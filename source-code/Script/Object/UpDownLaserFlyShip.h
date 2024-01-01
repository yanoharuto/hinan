#pragma once
#include  <memory>
#include  <iostream>
#include "Actor.h"
#include "EditObjectData.h"
class DamageObjectGenerator;
/// <summary>
/// 上下に動きながらレーザーを出すやつ
/// </summary>
class UpDownLaserFlyShip : public Actor,std::enable_shared_from_this<UpDownLaserFlyShip>
{
public:
    /// <summary>
    /// 初期位置の設定とレーザーを発射
    /// </summary>
    /// <param name="setPos">初期位置</param>
    /// <param name="damageObjGenerator">レーザーを発射することを伝えるクラス</param>
    UpDownLaserFlyShip(PlacementData setPos,std::weak_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// 上下に動くよ
    /// </summary>
    void Update() override;
private:
    //totalMoveValueの増加量
    static const float addMoveValue;
    //上下に動く速度
    static const float updownSpeed;
    //初期高度
    static float firstPosY;
    //動いた量
    float totalMoveValue = 0;
};

