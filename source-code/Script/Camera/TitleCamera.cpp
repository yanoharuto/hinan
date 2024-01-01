#include "TitleCamera.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"

/// <summary>
/// タイトル画面のカメラ　車の斜め正面を映す
/// </summary>
TitleCamera::TitleCamera(std::shared_ptr<ObjectObserver>& target)
    :Camera(CameraDataLoader::UseCameraSceneKind::title)
{
    targetObserver = target;
    VECTOR pos = targetObserver->GetSubjectPos();
    position = { 0,posY,0 };
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// プレイヤーの位置に合わせてカメラの位置を修正
/// </summary>
void TitleCamera::Update()
{
    auto target = targetObserver;
    if (target != nullptr)return;
    //カメラの向く位置
    VECTOR aimPos = target->GetSubjectPos();
    //車の向きから若干ずらしてさらに離れる
    VECTOR between = VScale(OriginalMath::GetYRotateVector(target->GetSubjectDir(),cameraRotate),targetBetweenSize);
    position = VAdd(VAdd(aimPos, VScale(target->GetSubjectDir(), targetBetweenSize)), between);
    position.y = posY;
    //カメラの向きを変更
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}