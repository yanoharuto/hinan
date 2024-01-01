#include "SawController.h"
#include "DrawModel.h"
#include "Saw.h"
#include "Utility.h"
/// <summary>
/// �v���C���[���͂�����΂��ۋ�
/// </summary>
SawController::SawController()
    :AddableObjectController(ObjectInit::InitObjKind::saw)
{
    drawModel = std::make_unique<DrawModel>(controllObjKind);
}
/// <summary>
/// �ۋ���ǉ�
/// </summary>
/// <param name="editData">�ǉ�����ʒu�Ȃǂ̏��</param>
void SawController::AddObject(PlacementData editData)
{
    auto saw = std::make_shared<Saw>(editData);
    std::shared_ptr<Actor> actor = saw;
    AddConflictManagement(actor);
    actorList.push_back(saw);
    
}
/// <summary>
/// ��]������@�j�󂳂ꂽ��j��
/// </summary>
void SawController::Update()
{
    //�j�����郊�X�g
    std::list<std::list<std::shared_ptr<Actor>>::iterator> brokenList;
    //�X�V
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::ObjectState::dead)//���j�I����͔j��
        {
            brokenList.push_back(ite);
            auto deleteSaw = *ite;
            SAFE_RESET(deleteSaw);
        }
    }
    //actorList����폜
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
