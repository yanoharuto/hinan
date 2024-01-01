#include "MoveSawController.h"
#include "MoveSaw.h"
#include "DrawModel.h"
#include "Utility.h"
#include "ReusableTimer.h"
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
/// </summary>
MoveSawController::MoveSawController()
    :AddableObjectController(ObjectInit::InitObjKind::moveSaw)
{
    drawModel = std::make_unique<DrawModel>(controllObjKind);
}
/// <summary>
/// ‰ñ“]‚Ì‚±‚¬‚è‚ğˆÚ“®‚³‚¹‚é@”j‰ó‚³‚ê‚½‚ç”jŠü
/// </summary>
void MoveSawController::Update()
{
    //”jŠü‚·‚éƒŠƒXƒg
    std::list<std::list<std::shared_ptr<Actor>>::iterator > brokenList;
    //XV
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::ObjectState::dead)//”š”jI—¹Œã‚Í”jŠü
        {
            brokenList.push_back(ite);
            auto deleteObj = *(ite);
            SAFE_RESET(deleteObj);
        }
    }
    //actorList‚©‚çíœ
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚Ì’Ç‰Á
/// </summary>
/// <param name="editData">ˆÊ’u‚âŒü‚«</param>
void MoveSawController::AddObject(PlacementData editData)
{
    std::shared_ptr<Actor> moveSaw = std::make_shared<MoveSaw>(editData);
    actorList.push_back(moveSaw);
}