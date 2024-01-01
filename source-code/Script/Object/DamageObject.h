#pragma once
#include <iostream>
#include <memory>
#include "Actor.h"
#include "InitObjKind.h"

class ObjectObserver;
/// <summary>
/// ダメージ判定のあるオブジェクト
/// </summary>
class DamageObject abstract:
    public Actor
{
public:
    /// <summary>
    /// 発射した奴の位置とかが分かるポインターをください
    /// </summary>
    /// <param name="kind"></param>
    /// <param name="setObserver"></param>
    DamageObject(ObjectInit::InitObjKind kind, std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// 発射したオブジェクトのユニークポインタの開放
    /// </summary>
    virtual ~DamageObject();
protected:
    /// <summary>
    /// 発射したオブジェクトの監視役
    /// </summary>
    std::unique_ptr<ObjectObserver> observer;
};

