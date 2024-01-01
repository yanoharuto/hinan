#pragma once
#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>
struct CollisionResultInfo;
struct HitCheckInfo;
class Actor;
class SphereHitChecker;
/// <summary>
/// 衝突処理実行役
/// </summary>
class  ConflictProcessor
{
public:
    /// <summary>
    /// 衝突処理実行役
    /// </summary>
    /// <param name="obj">実行したい衝突処理があるオブジェクト</param>
    ConflictProcessor(std::shared_ptr<Actor> obj);
    /// <summary>
    /// 実行先のオブジェクトをリセット
    /// </summary>
    virtual ~ConflictProcessor();
    /// <summary>
    /// 当たり判定の処理を呼び出す
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void OnConflict(CollisionResultInfo resultInfo);
    /// <summary>
    /// 当たり判定で衝突しているか調べるのに必要な情報を渡す
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;
    /// <summary>
    /// 衝突処理を行うオブジェクトがもう居ないなら
    /// </summary>
    /// <returns>もう居ないならTrue</returns>
    bool IsDead();
protected:
    ConflictProcessor() {};
    /// <summary>
    /// 当たり判定の持ち主
    /// </summary>
    std::shared_ptr<Actor> object = nullptr;
};