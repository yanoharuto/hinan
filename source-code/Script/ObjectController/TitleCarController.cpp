#include "TitleCarController.h"
#include "TitleCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// タイトルで走らせる車
/// </summary>
/// <param name="setPos">初期位置</param>
/// <param name="setDir">初期向き</param>
/// <param name="initTimer">定期的に初期位置に戻すためのタイマー</param>
TitlteCarController::TitlteCarController(VECTOR setPos, VECTOR setDir, std::shared_ptr<Timer> initTimer)
    :ActorController(ObjectInit::InitObjKind::player)
{
    titleCar = std::make_shared<TitleCar>(setPos, setDir,initTimer);
    observer = std::make_shared<ObjectObserver>(titleCar);
    drawModel = std::make_unique<DrawModel>(ObjectInit::InitObjKind::player);
}
/// <summary>
/// 走っている車と描画役の開放
/// </summary>
TitlteCarController::~TitlteCarController()
{
    SAFE_RESET(titleCar);
    observer.reset();
    SAFE_RESET(drawModel);
}
/// <summary>
/// 車の移動
/// </summary>
void TitlteCarController::Update()
{
    titleCar->Update();
}
/// <summary>
/// 描画
/// </summary>
void TitlteCarController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    drawModel->Draw(titleCar->GetPos(),titleCar->GetDir());
}
/// <summary>
/// 車の位置などをカメラなどに渡せるようにする
/// </summary>
/// <returns>車情報伝達役</returns>
std::shared_ptr<ObjectObserver> TitlteCarController::CreateCarObserver()
{
    return observer;
}
