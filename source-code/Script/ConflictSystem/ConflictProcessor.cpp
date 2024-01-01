#include "ConflictProcessor.h"
#include "Actor.h"
#include "SphereHitChecker.h"
#include "ConflictManager.h"
/// <summary>
/// 衝突処理実行役
/// </summary>
/// <param name="obj">実行したい衝突処理があるオブジェクト</param>
ConflictProcessor::ConflictProcessor(std::shared_ptr<Actor> obj)
{
    object = std::move(obj);
}
/// <summary>
/// 実行先のオブジェクトをリセット
/// </summary>
ConflictProcessor::~ConflictProcessor()
{
    object.reset();
}

/// <summary>
/// 当たり判定の処理を呼び出す
/// </summary>
/// <param name="resultInfo">衝突時の結果</param>
void ConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //当たった時の処理を行う
        object->OnConflict(resultInfo);
    }
}
/// <summary>
/// 当たり判定で衝突しているか調べるのに必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckInfo ConflictProcessor::GetHitExamineCheckInfo() const
{
    HitCheckInfo info;
    info.SetExamineInfo(object.get());
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// 衝突処理を行うオブジェクトがもう居ないなら
/// </summary>
/// <returns>もう居ないならTrue</returns>
bool ConflictProcessor::IsDead()
{
    return object->GetObjectState()== Object::ObjectState::dead;
}
