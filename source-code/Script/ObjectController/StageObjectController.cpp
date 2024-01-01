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
/// ������
/// </summary>
/// <returns></returns>
StageObjectController::StageObjectController()
    :ActorController(ObjectInit::InitObjKind::wall)
{   
    //���̐ݒ�
    floorModelHandle = InitActor::GetModelHandle(InitObjKind::stageFloor);
    auto param = InitActor::GetActorParamator(InitObjKind::stageFloor);
    MV1SetPosition(floorModelHandle, VGet(0, param.firstPosY, 0));
    //skyDome�̐ݒ�
    skyDomeModelHandle = InitActor::GetModelHandle(InitObjKind::skyDome);
    stageWall = std::make_unique<StageWall>();
    drawModel = std::make_unique<DrawModel>(InitObjKind::wall);
}
/// <summary>
/// �X�e�[�W���͂ރI�u�W�F�N�g�̉��
/// </summary>
StageObjectController::~StageObjectController()
{
    SAFE_RESET(stageWall);
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void StageObjectController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    //�ǂƏ�
    drawModel->Draw(stageWall->GetPos(),stageWall->GetDir());
    MV1DrawModel(floorModelHandle);
    //���C�g�̉e���Ȃ��ŋ��`��
    SetUseLighting(false);
    MV1DrawModel(skyDomeModelHandle);
    SetUseLighting(true);
}