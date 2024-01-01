#include "CircleFlyShipController.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"
#include "DrawModel.h"
/// <summary>
/// ���[�U�[�𔭎˂ł���悤��Generator���m��
/// </summary>
/// <param name="generator">���[�U�[���˂ɕK�v�ȃN���X</param>
CircleFlyShipController::CircleFlyShipController(std::shared_ptr<DamageObjectGenerator> generator)
    :FlyShipController(InitObjKind::circleLaserShip,generator)
{
    drawModel = std::make_unique<DrawModel>(InitObjKind::circleLaserShip);
    generator.reset();
}

/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̔z�u�ƒǉ�
/// </summary>
/// <param name="arrangementData">�z�u�ɕK�v�ȏ��</param>
void CircleFlyShipController::AddObject(PlacementData arrangementData)
{
    //�@�̂��͂�ł��钆�S���W
    VECTOR centerPos = VGet(arrangementData.posX, 0, arrangementData.posZ);
    //�����ʒu
    VECTOR generatePos = {};
    //�����@GeneratePos���v�Z����̂Ɏg��
    VECTOR dir = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
    //���x��dir���Ȃ���p�x
    float tempRota = static_cast<float>(360 / param.unitNum);
    //firstPos���͂ނ悤�ɔz�u
    for (int i = 0; i < param.unitNum; i++)
    {
        //��������
        dir = VNorm(OriginalMath::GetYRotateVector(dir, tempRota));
        //�����ʒu��dir�̕�����between�����ꂽ��
        generatePos = VAdd(centerPos, VScale(dir, param.unitBetween));
        //�@�̐����ʒu�Ƌ@�̂������ʒu
        actorList.push_back(std::make_shared<CircleLaserFlyShip>(generatePos, centerPos,damageObjectGenerator));
    }
}
