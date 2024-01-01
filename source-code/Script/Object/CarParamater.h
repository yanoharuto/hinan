#pragma once
#include "DxLib.h"
/// <summary>
/// 車のパラメーター
/// </summary>
struct CarInfomation
{
    //加速量
    float addSpeed;
    //最高速度
    float maxSpeed;
    //当たり判定の半径
    float setRadius;
    //modelの大きさ
    float modelSize;
    //吹き飛ばし力
    float bouncePower;
    //曲がる力
    float gripPower;
    //曲がり始める角度
    float turnAngularLine;
};