#include "MoveSawController.h"
#include "MoveSaw.h"
#include "DrawModel.h"
#include "Utility.h"
#include "ReusableTimer.h"
/// <summary>
/// 移動する回転のこぎりの管理者
/// </summary>
MoveSawController::MoveSawController()
    :AddableObjectController(ObjectInit::InitObjKind::moveSaw)
{
    drawModel = std::make_unique<DrawModel>(controllObjKind);
}
/// <summary>
/// 回転のこぎりを移動させる　破壊されたら破棄
/// </summary>
void MoveSawController::Update()
{
    //破棄するリスト
    std::list<std::list<std::shared_ptr<Actor>>::iterator > brokenList;
    //更新
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::ObjectState::dead)//爆破終了後は破棄
        {
            brokenList.push_back(ite);
            auto deleteObj = *(ite);
            SAFE_RESET(deleteObj);
        }
    }
    //actorListから削除
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
/// <summary>
/// 移動する回転のこぎりの追加
/// </summary>
/// <param name="editData">位置や向き</param>
void MoveSawController::AddObject(PlacementData editData)
{
    std::shared_ptr<Actor> moveSaw = std::make_shared<MoveSaw>(editData);
    actorList.push_back(moveSaw);
}