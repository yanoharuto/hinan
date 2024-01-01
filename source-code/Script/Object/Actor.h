#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"

/// <summary>
/// 当たり判定を所有することが出来るクラス
/// </summary>
class Actor abstract : public Object
{
public:
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    /// <param name="kind"></param>
    Actor(ObjectInit::InitObjKind kind);
    

    virtual ~Actor()
    {
    };

    /// <summary>
    /// 衝突処理
    /// </summary>
    virtual void OnConflict(const CollisionResultInfo conflictInfo) {};

    /// <summary>
    /// 当たり判定で当たってたら渡す情報
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitCheckExamineInfo();
};