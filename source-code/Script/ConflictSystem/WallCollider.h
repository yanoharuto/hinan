#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// ステージの外に出ないようにする壁
/// </summary>
class WallCollider : public SphereHitChecker
{
public:
    /// <summary>
    /// ステージの外に出ないようにする壁
    /// </summary>
    /// <param name="owner"></param>
    /// <param name="setFirstPos">これ以上の値になったら跳ね返す</param>
    /// <param name="setEndPos">これ以下の値になったら跳ね返す</param>
    WallCollider(std::shared_ptr<Actor>& owner,VECTOR setFirstPos,VECTOR setEndPos);
    /// <summary>
    /// 当たったか調べる
    /// </summary>
    /// <param name="hitCheckInfo">調べたい当たり判定</param>
    /// <returns>衝突結果</returns>
    CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo) override;
private:
    //これ以上の値になったら跳ね返す
    VECTOR firstPos;
    //これ以下の値になったら跳ね返す
    VECTOR endPos;
};
