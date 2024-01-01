#pragma once
#include <vector>
#include "DamageObjectController.h"
class ObjectObserver;
/// <summary>
/// y軸回転する大回りするレーザー
/// </summary>
class RotatingLaserController : public DamageObjectController
{
public:
    /// <summary>
    /// 追加と描画の準備
    /// </summary>
    /// <param name="generator">レーザー生成役</param>
    RotatingLaserController();
    /// <summary>
    /// レーザーを照射したオブジェクトを引数にもらう
    /// </summary>
    /// <param name="sub">レーザーを照射したオブジェクト</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
private:
    //回転半径
    static const float rotateRadius;
};