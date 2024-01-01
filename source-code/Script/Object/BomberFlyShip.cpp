#include "DamageObjectGenerator.h"
#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "ObjectObserver.h"
#include "AssetManager.h"
#include "ReusableTimer.h"
#include "InitActor.h"
/// <summary>
/// �����̈ʒu�ɐ����@
/// </summary>
/// <param name="data">�����ʒu�ƌ������������\����</param>
/// <param name="initParam">���e���˃N�[���^�C��������</param>
/// <param name="damageObjGenerator">���e���˂ɕK�v�ȃN���X</param>
BomberFlyShip::BomberFlyShip(PlacementData data, float coolTime, std::shared_ptr<DamageObjectGenerator> damageObjGenerator)
    :Actor(InitObjKind::bomberShip)
{
    position.x = data.posX;
    position.z = data.posZ;
    direction.x = data.dirX;
    direction.z = data.dirZ;
    direction.y = 0;
    bombFallTimer = std::make_unique<ReusableTimer>(coolTime);

    damageObjectGenerator = damageObjGenerator;
    velocity = direction;
}
/// <summary>
/// damageObjectGenerator�̊J��
/// </summary>
BomberFlyShip::~BomberFlyShip()
{
    damageObjectGenerator.reset();
}
/// <summary>
/// ���e�𗎂Ƃ��Ȃ���i��
/// </summary>
void BomberFlyShip::Update()
{
    //�N�[���^�C�����I�������
    if (bombFallTimer->IsOverLimitTime())
    {
        //�N�[���^�C���ăZ�b�g
        bombFallTimer->Reuse();
        //���e�𓊉�
        auto obserber = std::make_unique<ObjectObserver>(shared_from_this());
        damageObjectGenerator->GenerateDamageObject(DamageObjectGenerator::bomber, std::move(obserber));
    }
}