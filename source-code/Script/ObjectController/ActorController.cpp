#include "ActorController.h"
#include "Actor.h"
#include "DrawModel.h"
#include "Utility.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
#include "CameraObserver.h"
/// <summary>
/// �`����ƃI�u�W�F�N�g�̃f���[�g
/// </summary>
ActorController::~ActorController()
{
    DeleteActorListAndDrawModel();
}
/// <summary>
/// �Q�[���J�n��������
/// </summary>
void ActorController::PrepareGame()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->PrepareGame();
    }
}
/// <summary>
/// �X�V
/// </summary>
void ActorController::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        //�eactor�̍X�V
        (*ite)->Update();
    }
}
/// <summary>
/// �`�揈��
/// </summary>
void ActorController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    auto camera = cameraObserever.lock();
    if (drawModel != nullptr && camera != nullptr)
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            std::weak_ptr<Object> weak = *ite;
            auto object = weak.lock();
            if (object != nullptr && camera->IsLookingCamera(weak))//�J�����͈͓̔��Ȃ�
            {
                //Drawer�ɓn���ĕ`�悵�Ă��炤
                drawModel->Draw(object->GetPos(), object->GetDir());
            }
        }
    }
}
/// <summary>
/// �`�����ActorList�̉��
/// </summary>
void ActorController::DeleteActorListAndDrawModel()
{
    if (!actorList.empty())
    {
        for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
        {
            SAFE_RESET((*ite));
        }
        actorList.clear();
    }
    SAFE_RESET(drawModel);
}


/// <summary>
/// �����蔻��������ɒǉ�
/// </summary>
/// <param name="hitCheckOwner">�����蔻��̎�����</param>
void ActorController::AddConflictManagement(std::shared_ptr<Actor>& hitCheckOwner)
{
    auto colider = std::make_shared<SphereHitChecker>(hitCheckOwner);
    auto conflictProccesor = std::make_unique<ConflictProcessor>(hitCheckOwner);
    ConflictManager::AddConflictProcessor(conflictProccesor, colider);
}