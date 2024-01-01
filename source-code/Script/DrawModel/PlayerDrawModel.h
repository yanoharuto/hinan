#pragma once
#include "DrawModel.h"
class PlayerCar;
/// <summary>
/// プレイヤーの機体の傾きなどに対応する
/// </summary>
class PlayerDrawModel : public DrawModel
{
public:
    /// <summary>
    /// プレイヤーの機体の傾きなどに対応
    /// </summary>
    PlayerDrawModel();
    /// <summary>
    /// プレイヤーの角度に合わせて回転する
    /// </summary>
    /// <param name="drawObj"></param>
    void Draw(VECTOR position,VECTOR direction,VECTOR rotate) const;
protected:
    /// <summary>
/// 描画モデルの行列をセット
/// </summary>
    void ModelSetMatrix(VECTOR position, VECTOR direction, VECTOR rotate) const;
};

