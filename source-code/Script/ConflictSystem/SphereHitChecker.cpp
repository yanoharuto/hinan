#include "SphereHitChecker.h"
#include "Actor.h"
#include "HitCheckExamineObjectInfo.h"
#include "DxLib.h"
/// <summary>
/// 球形当たり判定
/// </summary>
/// <param name="obj">当たり判定の持ち主をください</param>
SphereHitChecker::SphereHitChecker(std::shared_ptr<Actor> obj)
{
    object = std::move(obj);
}

/// <summary>
/// 吹っ飛ぶ方向とかを返す
/// </summary>
/// <param name="hitCheckInfo">当たってきた方の情報</param>
/// <returns></returns>
CollisionResultInfo SphereHitChecker::HitCheck(HitCheckInfo hitCheckInfo)
{
    CollisionResultInfo resultInfo = {};
    HitCheckInfo objExamineInfo = {};
    objExamineInfo.SetExamineInfo(object.get());
    //当たってたら吹っ飛ぶ方向とかを返す
    if (HitCheck(objExamineInfo, hitCheckInfo))
    {
        VECTOR nBetweenDir = VNorm(VSub(object->GetPos(), hitCheckInfo.pos));//二つのオブジェクトの距離の向き
        //吹っ飛ぶ方向
        resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(nBetweenDir, VDot(hitCheckInfo.velocity, nBetweenDir) * 2));
        //吹っ飛んだ位置
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
        //当たったかどうか
        resultInfo.hit = HitSituation::Enter;
        //残りを設定
        resultInfo.SetObjInfo(object.get());
        //当たり判定変更
        hitCheckInfo.pos = resultInfo.pos;
    }

    return resultInfo;
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheck(const HitCheckInfo objAInfo, const HitCheckInfo objBInfo)
{
    return HitCheckProcess(objAInfo, objBInfo);
}
/// <summary>
/// 当たり判定で衝突しているか調べるのに必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckInfo SphereHitChecker::GetHitExamineCheckInfo() const
{
    HitCheckInfo info;
    info.SetExamineInfo(object.get());
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// 今もう動いていない状態か
/// </summary>
/// <returns>動いていないならTrue</returns>
bool SphereHitChecker::IsDead()
{
    return (object->GetObjectState() == Object::ObjectState::dead || object->GetObjectState() == Object::ObjectState::activeEnd);
}
/// <summary>
/// 当たったかどうか調べるときの共通処理
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool SphereHitChecker::HitCheckProcess(HitCheckInfo objAInfo, HitCheckInfo objBInfo)
{
    //引数同士の距離
    VECTOR distance = VSub(objAInfo.pos, objBInfo.pos);
    //引数同士の半径の合計
    float range = objAInfo.radius + objBInfo.radius;
    //半径の合計より小さかったら当たった
    if (range > VSize(distance))
    {
        return true;
    }
    return false;
}
