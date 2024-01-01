#include "SawController.h"
#include "DrawModel.h"
#include "Saw.h"
#include "Utility.h"
/// <summary>
/// プレイヤーをはじき飛ばす丸鋸
/// </summary>
SawController::SawController()
    :AddableObjectController(ObjectInit::InitObjKind::saw)
{
    drawModel = std::make_unique<DrawModel>(controllObjKind);
}
/// <summary>
/// 丸鋸を追加
/// </summary>
/// <param name="editData">追加する位置などの情報</param>
void SawController::AddObject(PlacementData editData)
{
    auto saw = std::make_shared<Saw>(editData);
    std::shared_ptr<Actor> actor = saw;
    AddConflictManagement(actor);
    actorList.push_back(saw);
    
}
/// <summary>
/// 回転させる　破壊されたら破棄
/// </summary>
void SawController::Update()
{
    //破棄するリスト
    std::list<std::list<std::shared_ptr<Actor>>::iterator> brokenList;
    //更新
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::ObjectState::dead)//爆破終了後は破棄
        {
            brokenList.push_back(ite);
            auto deleteSaw = *ite;
            SAFE_RESET(deleteSaw);
        }
    }
    //actorListから削除
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
