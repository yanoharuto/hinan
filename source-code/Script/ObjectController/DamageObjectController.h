#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "ActorController.h"

class ObjectObserver;
class SphereHitChecker;
class ConflictProcessor;
class DamageObject;
/// <summary>
/// ダメージ判定のあるオブジェクトの管理クラス
/// </summary>
class DamageObjectController abstract : public ActorController
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="kind">初期化したいオブジェクトの種類</param>
    DamageObjectController(ObjectInit::InitObjKind kind);

    /// <summary>
    /// 引数のオブジェクトから生成されたとき
    /// </summary>
    /// <param name="sub">発射したオブジェクトの位置や向きなどを渡すクラス</param>
    virtual void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub) = 0;
protected:
};