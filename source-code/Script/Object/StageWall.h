#pragma once
#include "Actor.h"
#include "WallCollider.h"
#include <string>
/// <summary>
/// 行動範囲を狭める壁
/// </summary>
class StageWall : public Actor
{
public:
    /// <summary>
    /// 行動範囲を狭める壁
    /// </summary>
    StageWall();
    ~StageWall() {};
private:
    //付き飛ばす力
    const float setBouncePower = 50;
    //マップの端１
    const VECTOR stageBiggestSize = { 2850,0,3150 };
    //マップの端2
    const VECTOR stageSmallestSize = { -3150,0,-2850 } ;
};