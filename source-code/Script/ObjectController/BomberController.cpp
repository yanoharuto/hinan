#include "BomberController.h"
#include "Bomber.h"
#include "ObjectObserver.h"
#include "DrawModel.h"
#include "Utility.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
/// <summary>
/// ���e����W
/// </summary>
/// <param name="sub"></param>
BomberController::BomberController()
    :DamageObjectController(ObjectInit::InitObjKind::bomber)
{
    drawModel = std::make_unique<DrawModel>(ObjectInit::InitObjKind::bomber);
}
/// <summary>
/// ���e���X�V�ł���悤�ɂ���
/// </summary>
/// <param name="sub">���e�𓊉������I�u�W�F�N�g</param>
void BomberController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    std::shared_ptr<Actor> actor = std::make_shared<Bomber>(std::move(sub));
    AddConflictManagement(actor);
    actorList.push_back(actor);
}
/// <summary>
/// ���e�𗎉�������
/// </summary>
void BomberController::Update()
{
    if(!actorList.empty())
    {
        //�j�����郊�X�g
        std::list<std::list<std::shared_ptr<Actor>>::iterator> brokenList;
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            (*ite)->Update();
            //�X�V
            if ((*ite)->GetObjectState() == Object::ObjectState::dead)//���j�I����͔j��
            {
                brokenList.push_back(ite);
                SAFE_RESET((*ite));
            }
        }
        //actorList����폜
        for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
        {
            actorList.erase(*(ite));
        }
    }
}