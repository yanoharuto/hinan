#include "PlayerConflictProcessor.h"
#include "PlayerCar.h"
#include "PlayerObserver.h"
PlayerConflictProcessor::PlayerConflictProcessor(std::shared_ptr<PlayerCar>& car, std::shared_ptr<PlayerObserver>& observer)
{
    object = car;

}
/// <summary>
/// 衝突結果実行役
/// </summary>
/// <param name="resultInfo">衝突結果</param>
void PlayerConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    //衝突後の処理を行う必要がないなら終了
    if (object == nullptr)return;
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //当たった時の処理を行う
        object->OnConflict(resultInfo);
        //コレクトアイテムならカウント
        if (resultInfo.tag == Object::ObjectTag::collect)
        {
            observer->GetCollectCount();
        }
    }
}