#pragma once
#include "FlyShipController.h"
/// <summary>
/// �����@�Ǘ��N���X
/// </summary>
class BomberFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// �����@�̏������Ɣ��e���ˏ���
    /// </summary>
    /// <param name="generator">���e�𔭎˂ł���N���X</param>
    BomberFlyShipController(std::shared_ptr<DamageObjectGenerator> generator);
    /// <summary>
    /// �����@��ǉ�����
    /// </summary>
    /// <param name="editData">�z�u���</param>
    void AddObject(PlacementData editData)override;
};

