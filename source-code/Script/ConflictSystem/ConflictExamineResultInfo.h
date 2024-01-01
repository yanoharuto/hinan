#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// 当たった状況
/// </summary>
enum class HitSituation
{
    //当たってない
    NotHit,
    //当たった
    Enter,
    //当たり続けている
    Stay,
    //離れた
    Exist
};
/// <summary>
/// 当たり判定の結果 渡す情報
/// </summary>
struct CollisionResultInfo
{
    //当たり判定の当たり状況
    HitSituation hit = HitSituation::NotHit;
    //当たったオブジェクトのタグ
    Object::Object::ObjectTag tag = Object::ObjectTag::obstacle;
    //吹っ飛ぶベクトル
    VECTOR bounceVec = {};
    //当たった後の位置
    VECTOR pos = {};
    //吹っ飛び力
    float bouncePower = 0;
    /// <summary>
    /// tagや半径　吹っ飛び力を設定
    /// </summary>
    void SetObjInfo(Object* const obj)
    {
        tag = obj->GetTag();
        bouncePower = obj->GetBouncePower();
    }
};
