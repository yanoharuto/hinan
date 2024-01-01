#include "CircleFlyShipController.h"
#include "InitActor.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "CircleLaserFlyShip.h"
#include "OriginalMath.h"
#include "DrawModel.h"
/// <summary>
/// レーザーを発射できるようにGeneratorを確保
/// </summary>
/// <param name="generator">レーザー発射に必要なクラス</param>
CircleFlyShipController::CircleFlyShipController(std::shared_ptr<DamageObjectGenerator> generator)
    :FlyShipController(InitObjKind::circleLaserShip,generator)
{
    drawModel = std::make_unique<DrawModel>(InitObjKind::circleLaserShip);
    generator.reset();
}

/// <summary>
/// 輪になっているレーザー照射機の配置と追加
/// </summary>
/// <param name="arrangementData">配置に必要な情報</param>
void CircleFlyShipController::AddObject(PlacementData arrangementData)
{
    //機体が囲んでいる中心座標
    VECTOR centerPos = VGet(arrangementData.posX, 0, arrangementData.posZ);
    //生成位置
    VECTOR generatePos = {};
    //方向　GeneratePosを計算するのに使う
    VECTOR dir = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
    //作る度にdirが曲がる角度
    float tempRota = static_cast<float>(360 / param.unitNum);
    //firstPosを囲むように配置
    for (int i = 0; i < param.unitNum; i++)
    {
        //離れる方向
        dir = VNorm(OriginalMath::GetYRotateVector(dir, tempRota));
        //生成位置はdirの方向にbetween分離れた所
        generatePos = VAdd(centerPos, VScale(dir, param.unitBetween));
        //機体生成位置と機体が向く位置
        actorList.push_back(std::make_shared<CircleLaserFlyShip>(generatePos, centerPos,damageObjectGenerator));
    }
}
