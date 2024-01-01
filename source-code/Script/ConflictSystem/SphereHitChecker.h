#pragma once
#include "Object.h"
#include <iostream>
#include <memory>
struct HitCheckInfo;
struct CollisionResultInfo;
class Actor;
/// <summary>
/// 球同士の当たり判定をやります
/// </summary>
class SphereHitChecker
{
public:
    /// <summary>
    /// 球同士の当たり判定を行う
    /// </summary>
    /// <param name="obj">当たり判定の持ち主</param>
    SphereHitChecker(std::shared_ptr<Actor> obj);
    ~SphereHitChecker() {};
    /// <summary>
    /// 当たっているか調べ吹っ飛ぶ方向とかを返す
    /// </summary>
    /// <param name="hitCheckInfo">当たっているか調べたい当たり判定</param>
    /// <returns>当たってたら衝突結果を返す</returns>
    virtual CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo);
    /// <summary>
    /// 当たり判定で衝突しているか調べるのに必要な情報を渡す
    /// </summary>
    /// <returns>当たり判定で必要な情報</returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;
    /// <summary>
    /// trueなら当たり判定無し
    /// </summary>
    /// <returns>当たり判定の持ち主が動いていないならTrue</returns>
    bool IsDead();
protected:
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(const HitCheckInfo objAInfo, const HitCheckInfo objBInfo);

protected:
    /// <summary>
    /// 当たったかどうか調べるときの共通処理
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheckProcess(HitCheckInfo objAInfo, HitCheckInfo objBInfo);

    //当たり判定の持ち主
    std::shared_ptr<Actor> object = nullptr;
};