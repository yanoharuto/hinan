#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// �㉺�Ɉړ������s��
/// </summary>
class UpDownFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// �㉺�Ɉړ������s�D�̊Ǘ�����
    /// </summary>
    /// <param name="damageObjeGenerator">���[�U�[�𔭎˂ł���悤�ɂ���</param>
    UpDownFlyShipController(std::shared_ptr<DamageObjectGenerator> damageObjeGenerator);
protected:
    /// <summary>
    /// �㉺�ɑ΋󂷂��s�D�������̈ʒu�ɒǉ�
    /// </summary>
    /// <param name="editData">�z�u�ʒu</param>
    void AddObject(PlacementData editData)override;

};

