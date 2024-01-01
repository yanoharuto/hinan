#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̍X�V�Ƃ�����
/// </summary>
class CircleFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// ���[�U�[�𔭎˂ł���悤��Generator���m��
    /// </summary>
    /// <param name="generator">���[�U�[���˂ɕK�v�ȃN���X</param>
    CircleFlyShipController(std::shared_ptr<DamageObjectGenerator> generator);
private:
    /// <summary>
    /// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̔z�u�ƒǉ�
    /// </summary>
    /// <param name="arrangementData">�z�u�ɕK�v�ȏ��</param>
    void AddObject(PlacementData arrangementData);
};

