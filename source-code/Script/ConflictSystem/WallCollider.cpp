#include "WallCollider.h"
#include "Actor.h"
/// <summary>
/// ステージの外に出ないようにする壁
/// </summary>
/// <param name="owner"></param>
/// <param name="setFirstPos">これ以上の値になったら跳ね返す</param>
/// <param name="setEndPos">これ以下の値になったら跳ね返す</param>
WallCollider::WallCollider(std::shared_ptr<Actor>& owner,VECTOR setFirstPos, VECTOR setEndPos)
    :SphereHitChecker(owner)
{
    firstPos = setFirstPos;
    endPos = setEndPos;
}

/// <summary>
/// 当たったか調べる
/// </summary>
/// <param name="hitCheckInfo"></param>
/// <returns></returns>
CollisionResultInfo WallCollider::HitCheck(HitCheckInfo hitCheckInfo)
{
    CollisionResultInfo resultInfo;//返り値
    resultInfo.SetObjInfo(object.get());
    resultInfo.pos = hitCheckInfo.pos;
    resultInfo.hit = HitSituation::NotHit;
    //速さを足した場合のポジション
    VECTOR nextPos = VAdd(hitCheckInfo.pos, hitCheckInfo.velocity);
    //処理終了フラグ
    bool isEndProcess = false;
    //範囲内に戻るまで処理を行う
    while (!isEndProcess)
    {
        isEndProcess = true;
        //範囲外に出ようとしているなら押し戻す
        if (nextPos.x - hitCheckInfo.radius < firstPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.x = firstPos.x + hitCheckInfo.radius + 1;
            isEndProcess = false;
        }
        else if (nextPos.x + hitCheckInfo.radius > endPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.x = endPos.x - hitCheckInfo.radius - 1;
            isEndProcess = false;
        }
        else if (nextPos.z - hitCheckInfo.radius < firstPos.z)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.z = firstPos.z + hitCheckInfo.radius + 1;
            isEndProcess = false;
        }
        else if (nextPos.z + hitCheckInfo.radius > endPos.z)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.z = endPos.z - hitCheckInfo.radius - 1;
            isEndProcess = false;
        }
        //吹っ飛んだ位置
        resultInfo.pos = nextPos;
    }
    return resultInfo;
}
