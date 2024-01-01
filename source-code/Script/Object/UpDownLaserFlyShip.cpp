#include "UpDownLaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "ObjectObserver.h"
//totalMoveValue�̑�����
const float UpDownLaserFlyShip::addMoveValue = 0.05f;
//�㉺�ɓ������x
const float UpDownLaserFlyShip::updownSpeed = 6.0f;
//�������x
float UpDownLaserFlyShip::firstPosY = 0.0f;
/// <summary>
/// �����ʒu�̐ݒ�ƃ��[�U�[�𔭎�
/// </summary>
/// <param name="editData">�����ʒu</param>
/// <param name="damageObjGenerator">���[�U�[�𔭎˂��邱�Ƃ�`����N���X</param>
UpDownLaserFlyShip::UpDownLaserFlyShip(PlacementData editData, std::weak_ptr<DamageObjectGenerator> damageObjGenerator)
    :Actor(ObjectInit::InitObjKind::upDownLaserShip)
{
    firstPosY = position.y;
    //�ʒu�ƌ����̏�����
    position.x = editData.posX;
    position.z = editData.posZ;
    direction = VGet(editData.dirX, 0, editData.dirZ);
    //���[�U�[�𔭎�
    damageObjGenerator.lock()->GenerateDamageObject(DamageObjectGenerator::laser, std::make_unique<ObjectObserver>(shared_from_this()));
}
/// <summary>
/// �㉺�ɓ�����
/// </summary>
void UpDownLaserFlyShip::Update()
{
    //�㉺�Ɉړ�
    totalMoveValue += addMoveValue;
    position.y = cosf(totalMoveValue) * updownSpeed + firstPosY;
}