#include "LaserCollider.h"
#include "Actor.h"
/// <summary>
/// Y軸回転するレーザーの当たり判定
/// </summary>
/// <param name="obj"></param>
/// <param name="setLineRange">高さが1に対する底辺の長さ</param>
LaserCollider::LaserCollider(std::shared_ptr<Actor>& obj, float setLineRange)
    :SphereHitChecker(obj)
{
    lineRange = setLineRange;
}
/// <summary>
/// Y座標を無視しているけど線分の当たり判定
/// </summary>
/// <param name="hitCheckInfo">当たってくる奴の情報</param>
/// <returns></returns>
CollisionResultInfo LaserCollider::HitCheck(HitCheckInfo hitCheckInfo)
{
    CollisionResultInfo resultInfo = {};
    //レーザーの情報
    HitCheckInfo lineInfo;
    lineInfo.SetExamineInfo(object.get());
    //objectの高さ分伸ばす
    float range = (object->GetPos().y - hitCheckInfo.pos.y) * lineRange;
    lineInfo.pos = VAdd(lineInfo.pos, VScale(object->GetDir(),  range));
    //当たってくる奴の高さに合わせる
    lineInfo.pos.y = hitCheckInfo.pos.y;

    if (SphereHitChecker::HitCheck(lineInfo, hitCheckInfo))
    {
        resultInfo.bounceVec = VSub(hitCheckInfo.pos, lineInfo.pos);
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
        resultInfo.tag = object->GetTag();
        resultInfo.hit = HitSituation::Enter;
    }
    return resultInfo;
}
