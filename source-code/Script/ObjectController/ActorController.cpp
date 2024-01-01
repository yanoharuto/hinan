#include "ActorController.h"
#include "Actor.h"
#include "DrawModel.h"
#include "Utility.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
#include "CameraObserver.h"
/// <summary>
/// 描画役とオブジェクトのデリート
/// </summary>
ActorController::~ActorController()
{
    DeleteActorListAndDrawModel();
}
/// <summary>
/// ゲーム開始準備処理
/// </summary>
void ActorController::PrepareGame()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->PrepareGame();
    }
}
/// <summary>
/// 更新
/// </summary>
void ActorController::Update()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        //各actorの更新
        (*ite)->Update();
    }
}
/// <summary>
/// 描画処理
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
            if (object != nullptr && camera->IsLookingCamera(weak))//カメラの範囲内なら
            {
                //Drawerに渡して描画してもらう
                drawModel->Draw(object->GetPos(), object->GetDir());
            }
        }
    }
}
/// <summary>
/// 描画役とActorListの解放
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
/// 当たり判定を引数に追加
/// </summary>
/// <param name="hitCheckOwner">当たり判定の持ち主</param>
void ActorController::AddConflictManagement(std::shared_ptr<Actor>& hitCheckOwner)
{
    auto colider = std::make_shared<SphereHitChecker>(hitCheckOwner);
    auto conflictProccesor = std::make_unique<ConflictProcessor>(hitCheckOwner);
    ConflictManager::AddConflictProcessor(conflictProccesor, colider);
}