#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// Y座標を無視しているけど線分の当たり判定
/// </summary>
class LaserCollider : public SphereHitChecker
{
public:
    /// <summary>
    /// Y軸回転するレーザーの当たり判定
    /// </summary>
    /// <param name="obj"></param>
    /// <param name="setLineRange">高さが1に対する底辺の長さ</param>
    LaserCollider(std::shared_ptr<Actor>& obj, float setLineRange);

    /// <summary>
    /// Y座標を無視しているけど線分の当たり判定
    /// </summary>
    /// <param name="hitCheckInfo">当たってくる奴の情報</param>
    /// <returns></returns>
    CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo)override;
private:
    //線分の長さは高さと係数によって決める
    float lineRange;
};

