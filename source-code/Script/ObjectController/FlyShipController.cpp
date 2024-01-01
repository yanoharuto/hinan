#include "FlyShipController.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// ���������邽�߂ɕK�v�ȃf�[�^������
/// </summary>
/// <param name="kind">������������FlyShip�̎��</param>
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator)
    :AddableObjectController(kind)
{
    param.actorParam = InitActor::GetActorParamator(kind);
    AddFlyShipDataLoader::AddData addKind = AddFlyShipDataLoader::AddData::circleFlyShip;
    switch (kind)//�~�����ǉ��f�[�^�̎��
    {
    case InitObjKind::upDownLaserShip:
        addKind = AddFlyShipDataLoader::AddData::upDownFlyShip;
        break;
    case InitObjKind::bomberShip:
        addKind = AddFlyShipDataLoader::AddData::bomberShip;
        break;
    case InitObjKind::circleLaserShip:
        addKind = AddFlyShipDataLoader::AddData::circleFlyShip;
        break;
    default:
        break;
    }
    GetAddData(addKind);//�ǉ��f�[�^����
    damageObjectGenerator = damageObjGenerator;
}
/// <summary>
/// actorList��DrawModel��damageObjectGenerator�̉��
/// </summary>
FlyShipController::~FlyShipController()
{
    DeleteActorListAndDrawModel();
    damageObjectGenerator.reset();
}
/// <summary>
/// ��s�D�̒ǉ���񏊓�
/// </summary>
/// <param name="kind">��s�D�̎��</param>
void FlyShipController::GetAddData(AddFlyShipDataLoader::AddData kind)
{
    //FlyShip�p�̃f�[�^�����[�h
    auto loader = std::make_unique<AddFlyShipDataLoader>(kind);
    auto addData = loader->GetLoadData();
    //�ړ����x
    param.moveSpeed = STR_TO_F(addData[CAST_I(FlyShipParamator::moveSpeed)]);
    //��������
    param.setAliveTime = STR_TO_F(addData[CAST_I(FlyShipParamator::aliveTime)]);
    //�N�[���^�C��
    param.setCoolTime = STR_TO_F(addData[CAST_I(FlyShipParamator::coolTime)]);
    //�P�O���[�v���̂�
    param.unitNum = STR_TO_I(addData[CAST_I(FlyShipParamator::unitNum)]);
    //�̊ԋ���
    param.unitBetween = STR_TO_F(addData[CAST_I(FlyShipParamator::unitBetween)]);
    SAFE_RESET(loader);
}