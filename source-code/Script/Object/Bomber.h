#pragma once
#include "DamageObject.h"
class SphereHitChecker;
class ConflictProcessor;
/// <summary>
/// 上から下に落とす爆弾
/// </summary>
class Bomber final : public DamageObject
{
public:
    /// <summary>
/// 上から下に落とす爆弾
/// </summary>
    Bomber(std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// 球当たり判定削除
    /// </summary>
    ~Bomber() override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
    /// <summary>
    /// 衝突後の処理
    /// </summary>
    void OnConflict(CollisionResultInfo resultInfo) override;
private:
    //衝突後の爆発エフェクトの大きさ
    static const float effectRadius;
    //最初の落下速度
    static const float setFallingSpeed;
    //落下速度
    float fallingSpeed = setFallingSpeed;
    //重力
    static const float gravityPower;
    //燃えているときのエフェクト
    int burnEffect = -1;
};