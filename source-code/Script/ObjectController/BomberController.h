#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectSubject;
class ObjectObserver;
class SphereHitChecker;
class ConflictProccesor;
/// <summary>
/// 爆弾の管理クラス
/// </summary>
class BomberController : public DamageObjectController
{
public:
    /// <summary>
    /// 爆弾の管理クラス
    /// </summary>
    BomberController();
    /// <summary>
    /// 爆弾を更新できるようにする
    /// </summary>
    /// <param name="sub">爆弾を投下したオブジェクト</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
    /// <summary>
    /// 爆弾の更新
    /// </summary>
    void Update()override;
private:
};