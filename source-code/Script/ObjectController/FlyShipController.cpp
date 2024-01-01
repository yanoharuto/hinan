#include "FlyShipController.h"
#include "CSVFileLoader.h"
#include "Utility.h"
/// <summary>
/// 初期化するために必要なデータを所得
/// </summary>
/// <param name="kind">初期化したいFlyShipの種類</param>
FlyShipController::FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator)
    :AddableObjectController(kind)
{
    param.actorParam = InitActor::GetActorParamator(kind);
    AddFlyShipDataLoader::AddData addKind = AddFlyShipDataLoader::AddData::circleFlyShip;
    switch (kind)//欲しい追加データの種類
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
    GetAddData(addKind);//追加データ所得
    damageObjectGenerator = damageObjGenerator;
}
/// <summary>
/// actorListとDrawModelとdamageObjectGeneratorの解放
/// </summary>
FlyShipController::~FlyShipController()
{
    DeleteActorListAndDrawModel();
    damageObjectGenerator.reset();
}
/// <summary>
/// 飛行船の追加情報所得
/// </summary>
/// <param name="kind">飛行船の種類</param>
void FlyShipController::GetAddData(AddFlyShipDataLoader::AddData kind)
{
    //FlyShip用のデータをロード
    auto loader = std::make_unique<AddFlyShipDataLoader>(kind);
    auto addData = loader->GetLoadData();
    //移動速度
    param.moveSpeed = STR_TO_F(addData[CAST_I(FlyShipParamator::moveSpeed)]);
    //生存時間
    param.setAliveTime = STR_TO_F(addData[CAST_I(FlyShipParamator::aliveTime)]);
    //クールタイム
    param.setCoolTime = STR_TO_F(addData[CAST_I(FlyShipParamator::coolTime)]);
    //１グループ何体か
    param.unitNum = STR_TO_I(addData[CAST_I(FlyShipParamator::unitNum)]);
    //個体間距離
    param.unitBetween = STR_TO_F(addData[CAST_I(FlyShipParamator::unitBetween)]);
    SAFE_RESET(loader);
}