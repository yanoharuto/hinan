#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "DrawModel.h" 
/// <summary>
/// �㉺�Ɉړ������s�D�̊Ǘ�����
/// </summary>
/// <param name="damageObjeGenerator">���[�U�[�𔭎˂ł���悤�ɂ���</param>
UpDownFlyShipController::UpDownFlyShipController(std::shared_ptr<DamageObjectGenerator> damageObjeGenerator)
    :FlyShipController(InitObjKind::upDownLaserShip,damageObjeGenerator)
{
    drawModel = std::make_unique<DrawModel>(InitObjKind::upDownLaserShip);
}
/// <summary>
/// �㉺�ɑ΋󂷂��s�D�������̈ʒu�ɒǉ�
/// </summary>
/// <param name="editData">�z�u�ʒu</param>
void UpDownFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(std::make_shared<UpDownLaserFlyShip>(editData, damageObjectGenerator));
}