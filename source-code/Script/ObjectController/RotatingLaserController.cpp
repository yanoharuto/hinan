#include "RotatingLaserController.h"
#include "RotatingLaser.h"
#include "ObjectObserver.h"
#include "LaserCollider.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
//回転半径
const float RotatingLaserController::rotateRadius = 1.333f;
/// <summary>
/// 追加と描画の準備
/// </summary>
/// <param name="generator">レーザー生成役</param>
RotatingLaserController::RotatingLaserController()
    :DamageObjectController(ObjectInit::InitObjKind::laser)
{
};
/// <summary>
/// レーザーを照射したオブジェクトを引数にもらう
/// </summary>
/// <param name="sub">レーザーを照射したオブジェクト</param>
void RotatingLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    std::shared_ptr<Actor> laser = std::make_shared<RotatingLaser>(std::move(sub));
    std::shared_ptr<SphereHitChecker> colider = std::make_shared<LaserCollider>(laser,rotateRadius);
    auto conflictProccesor = std::make_unique<ConflictProcessor>(laser);
    ConflictManager::AddConflictProcessor(conflictProccesor, colider);
    actorList.push_back(laser);
}