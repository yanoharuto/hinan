#include "BomberController.h"
#include "Bomber.h"
#include "ObjectObserver.h"
#include "DrawModel.h"
#include "Utility.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
/// <summary>
/// 爆弾制御係
/// </summary>
/// <param name="sub"></param>
BomberController::BomberController()
    :DamageObjectController(ObjectInit::InitObjKind::bomber)
{
    drawModel = std::make_unique<DrawModel>(ObjectInit::InitObjKind::bomber);
}
/// <summary>
/// 爆弾を更新できるようにする
/// </summary>
/// <param name="sub">爆弾を投下したオブジェクト</param>
void BomberController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    std::shared_ptr<Actor> actor = std::make_shared<Bomber>(std::move(sub));
    AddConflictManagement(actor);
    actorList.push_back(actor);
}
/// <summary>
/// 爆弾を落下させる
/// </summary>
void BomberController::Update()
{
    if(!actorList.empty())
    {
        //破棄するリスト
        std::list<std::list<std::shared_ptr<Actor>>::iterator> brokenList;
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            (*ite)->Update();
            //更新
            if ((*ite)->GetObjectState() == Object::ObjectState::dead)//爆破終了後は破棄
            {
                brokenList.push_back(ite);
                SAFE_RESET((*ite));
            }
        }
        //actorListから削除
        for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
        {
            actorList.erase(*(ite));
        }
    }
}