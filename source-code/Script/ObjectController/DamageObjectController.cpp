#include "DamageObjectController.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
#include "DamageObject.h"
/// <summary>
/// ������
/// </summary>
/// <param name="kind">�������������I�u�W�F�N�g�̎��</param>
DamageObjectController::DamageObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
}