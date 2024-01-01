#include <math.h>
#include "DxLib.h"
#include "StageObjectController.h"
#include "AssetManager.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "InitActor.h"
#include "StageWall.h"
#include "DrawModel.h"
#include "CameraObserver.h"
/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
StageObjectController::StageObjectController()
    :ActorController(ObjectInit::InitObjKind::wall)
{   
    //床の設定
    floorModelHandle = InitActor::GetModelHandle(InitObjKind::stageFloor);
    auto param = InitActor::GetActorParamator(InitObjKind::stageFloor);
    MV1SetPosition(floorModelHandle, VGet(0, param.firstPosY, 0));
    //skyDomeの設定
    skyDomeModelHandle = InitActor::GetModelHandle(InitObjKind::skyDome);
    stageWall = std::make_unique<StageWall>();
    drawModel = std::make_unique<DrawModel>(InitObjKind::wall);
}
/// <summary>
/// ステージを囲むオブジェクトの解放
/// </summary>
StageObjectController::~StageObjectController()
{
    SAFE_RESET(stageWall);
}

/// <summary>
/// コースのモデルを描画
/// </summary>
void StageObjectController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    //壁と床
    drawModel->Draw(stageWall->GetPos(),stageWall->GetDir());
    MV1DrawModel(floorModelHandle);
    //ライトの影響なしで空を描画
    SetUseLighting(false);
    MV1DrawModel(skyDomeModelHandle);
    SetUseLighting(true);
}