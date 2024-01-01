#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "CollectItem.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "InitActor.h"
#include "DrawModel.h"
#include "Object.h"
/// <summary>
/// 収集アイテムを予めNewして最大枚数を保存
/// </summary>
CollectItemController::CollectItemController()
    :ActorController(InitObjKind::collect)
{
    //配置情報所得
    auto positionGetter = std::make_unique<FirstPositionGetter>();
    auto editDataVec = positionGetter->GetPlaceData(InitObjKind::collect);
    SAFE_RESET(positionGetter);
    //配置情報に基づいてNewしていく
    for (int i = 0; i < CONTAINER_GET_SIZE(editDataVec); i++)
    {
        //収集アイテムの位置をコンストラクタに与える
        auto newCoin = std::make_shared<CollectItem>(editDataVec[i]);
        //当たり判定を追加
        std::shared_ptr<Actor> actor = newCoin;
        AddConflictManagement(actor);
        actorList.push_back(newCoin);  
        //マップに位置を伝えるためオブザーバーを渡す
        auto observer = std::make_unique<ObjectObserver>(newCoin);
        MiniMap::AddMarker(std::move(observer));
    }
    //収集アイテム最大値
    totalCollectNum = CONTAINER_GET_SIZE(actorList);
    //残りの数
    remainingCollectNum = totalCollectNum;
    //今出てきている収集アイテムの数
    collectCount = 0;
    //描画役
    drawModel = std::make_unique<DrawModel>(InitObjKind::collect);
    //今のアイテムの位置
    nowActiveCollectItemPos = {};
    //回収されているかどうかのフラグ
    isCollectLastOne = false;
}
/// <summary>
/// actorListの先頭の収集アイテムだけ更新
/// </summary>
void CollectItemController::Update()
{
    //何もない状態なら終了
    if (actorList.empty())return;
    //actorListの先頭の一つだけ動かす
    auto objIte = actorList.begin();
    (*objIte)->Update();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();

    //取っているけどエフェクトを出している途中なら現存数をへらす
    Object::ObjectState objState = (*objIte)->GetObjectState();
    //プレイヤーにぶつかって取られたならアクティブ以外の状態になっている
    if (objState == Object::ObjectState::dead)
    {
        //残り数を全体から1減らす
        remainingCollectNum = CONTAINER_GET_SIZE(actorList) - 1;
        //壊していいようにする
        auto brokenObj = (*objIte);
        //消していいやつだったら消す
        actorList.erase(objIte);
        SAFE_RESET(brokenObj);
        //次のアイテムは何番目か
        collectCount = totalCollectNum - remainingCollectNum;
    }
    //最後の一つが回収されたか
    else if (objState == Object::ObjectState::activeEnd && static_cast<int>(actorList.size()) == 1)
    {
        isCollectLastOne = true;
    }
}
/// <summary>
/// 収集アイテムの描画
/// </summary>
void CollectItemController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    if (!actorList.empty())
    {
        auto drawItem = *(actorList.begin());
        drawModel->Draw(drawItem->GetPos(),drawItem->GetDir());
    }
}
/// <summary>
/// ゲームが始まる前の処理
/// </summary>
void CollectItemController::PrepareGame()
{
    //イテレーター
    auto objIte = actorList.begin();
     (*objIte)->PrepareGame();
    //今現在動いているアイテムの場所を更新
    nowActiveCollectItemPos = (*objIte)->GetPos();
}
/// <summary>
/// 引数と収集アイテムの距離
/// </summary>
/// <param name="pos">収集アイテムとの距離を調べたい位置</param>
/// <returns>引数と収集アイテムの距離ベクトル</returns>
VECTOR CollectItemController::GetItemBetween(VECTOR pos)const
{
    return VSub(nowActiveCollectItemPos, pos);
}
/// <summary>
/// 最初にステージに配置される枚数
/// </summary>
/// <returns>ステージに配置された最大数</returns>
int CollectItemController::GetTotalNum()const
{
    return totalCollectNum;
}
/// <summary>
/// アイテムの残り枚数
/// </summary>
/// <returns>プレイヤーに取られると減る</returns>
int CollectItemController::GetRemainingNum()const
{
    return remainingCollectNum;
}
/// <summary>
/// 今の収集アイテムが何番目のアイテムか
/// </summary>
/// <returns>取られたら増える</returns>
int CollectItemController::GetCollectCount()const
{
    return collectCount;
}
/// <summary>
/// 最後の一つのアイテムが回収されたか
/// </summary>
/// <returns>回収されたらTrue</returns>
bool CollectItemController::IsCollectLastOne()const
{
    return isCollectLastOne;
}