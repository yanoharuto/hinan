#include "PlayerCarController.h"
#include "PlayerCar.h"
#include "SphereHitChecker.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "PlayerDrawModel.h"
#include "PlayerObserver.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
/// <summary>
/// プレイヤーの車の初期化
/// </summary>
PlayerCarController::PlayerCarController()
    :ActorController(ObjectInit::InitObjKind::player)
{
    //初期位置
    std::vector<PlacementData> editData = FirstPositionGetter::GetPlaceData(InitObjKind::player);
    //車の開放
    car = std::make_shared<PlayerCar>(editData[0]);
    playerObserver = std::make_shared<PlayerObserver>(car);
    //当たり判定を追加
    std::shared_ptr<Actor> actor = car;
    auto colider = std::make_shared<SphereHitChecker>(car);
    auto conflictProccesor = std::make_unique<ConflictProcessor>(car);
    ConflictManager::AddConflictProcessor(conflictProccesor, colider);
    //プレイヤーの位置から音を集めるリスナーの設定
    listener = std::make_unique<SoundListener>(CreatePlayerObserver());
    //プレイヤー描画役
    playerDrawer = std::make_unique<PlayerDrawModel>();
}
/// <summary>
/// 車とLisnerのDelete
/// </summary>
PlayerCarController::~PlayerCarController()
{
    SAFE_RESET(car);
    SAFE_RESET(listener);
}
/// <summary>
/// 車の位置とかを渡す
/// </summary>
/// <returns></returns>
std::shared_ptr<PlayerObserver> PlayerCarController::CreatePlayerObserver() const
{
    return playerObserver;
}
/// <summary>
/// 音を聞くために場所を更新
/// </summary>
void PlayerCarController::Update()
{
    car->Update();
    listener->Update();
}
/// <summary>
/// 描画
/// </summary>
void PlayerCarController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    playerDrawer->Draw(car->GetPos(),car->GetDir(),car->GetModelRotateVec());
}
