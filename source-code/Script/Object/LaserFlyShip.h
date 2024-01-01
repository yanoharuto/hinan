#pragma once
#include "Actor.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// レーザーを出す飛行船
/// </summary>
class LaserFlyShip abstract : public Actor
{
public:
    /// <summary>
    /// 初期化 目的地の方に向かせる
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    LaserFlyShip(ObjectInit::InitObjKind kind);
protected:
    //初期位置Y
    float firstPosY;
};
