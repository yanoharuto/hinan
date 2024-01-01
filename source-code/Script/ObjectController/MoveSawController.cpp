#include "MoveSawController.h"
#include "MoveSaw.h"
#include "DrawModel.h"
#include "Utility.h"
#include "ReusableTimer.h"
/// <summary>
/// �ړ������]�̂�����̊Ǘ���
/// </summary>
MoveSawController::MoveSawController()
    :AddableObjectController(ObjectInit::InitObjKind::moveSaw)
{
    drawModel = std::make_unique<DrawModel>(controllObjKind);
}
/// <summary>
/// ��]�̂�������ړ�������@�j�󂳂ꂽ��j��
/// </summary>
void MoveSawController::Update()
{
    //�j�����郊�X�g
    std::list<std::list<std::shared_ptr<Actor>>::iterator > brokenList;
    //�X�V
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Update();
        if ((*ite)->GetObjectState() == Object::ObjectState::dead)//���j�I����͔j��
        {
            brokenList.push_back(ite);
            auto deleteObj = *(ite);
            SAFE_RESET(deleteObj);
        }
    }
    //actorList����폜
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        actorList.erase(*(ite));
    }
}
/// <summary>
/// �ړ������]�̂�����̒ǉ�
/// </summary>
/// <param name="editData">�ʒu�����</param>
void MoveSawController::AddObject(PlacementData editData)
{
    std::shared_ptr<Actor> moveSaw = std::make_shared<MoveSaw>(editData);
    actorList.push_back(moveSaw);
}