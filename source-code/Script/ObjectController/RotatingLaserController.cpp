#include "RotatingLaserController.h"
#include "RotatingLaser.h"
#include "ObjectObserver.h"
#include "LaserCollider.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
//��]���a
const float RotatingLaserController::rotateRadius = 1.333f;
/// <summary>
/// �ǉ��ƕ`��̏���
/// </summary>
/// <param name="generator">���[�U�[������</param>
RotatingLaserController::RotatingLaserController()
    :DamageObjectController(ObjectInit::InitObjKind::laser)
{
};
/// <summary>
/// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
/// </summary>
/// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
void RotatingLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    std::shared_ptr<Actor> laser = std::make_shared<RotatingLaser>(std::move(sub));
    std::shared_ptr<SphereHitChecker> colider = std::make_shared<LaserCollider>(laser,rotateRadius);
    auto conflictProccesor = std::make_unique<ConflictProcessor>(laser);
    ConflictManager::AddConflictProcessor(conflictProccesor, colider);
    actorList.push_back(laser);
}