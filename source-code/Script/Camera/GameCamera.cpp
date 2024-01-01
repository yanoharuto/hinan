#include "GameCamera.h"
#include "OriginalMath.h"
#include "PlayerObserver.h"
#include "Utility.h"
#include "UserInput.h"
/// <summary>
/// 遊んでいるときのカメラの初期化
/// </summary>
/// <param name="player">プレイヤーの位置</param>
GameCamera::GameCamera(std::shared_ptr<PlayerObserver>& target)
    :Camera(CameraDataLoader::UseCameraSceneKind::game)
{
    targetObserver = target;
    //位置と向きを初期化
    VECTOR pos = targetObserver->GetSubjectPos();
    position = { 0,pos.y,0 };
    SetCameraPositionAndTarget_UpVecY(position, pos);
}

/// <summary>
/// 位置や向きの更新
/// </summary>
void GameCamera::Update()
{
    //カメラとプレイヤーの向きの差分べクトル
    VECTOR subDirVec = VSub(targetObserver->GetSubjectDir(), direction);
    subDirVec.y = 0;
    //向きの更新 cameraSpeedの速度で車の向きに合わせている
    VECTOR tempDir = VScale(subDirVec, cameraSpeed * VSize(subDirVec));
    direction = VNorm(VAdd(direction, tempDir));
    //カメラの位置の更新
    position = targetObserver->GetSubjectPos();
    position.y = posY;
    position.x += -(direction.x * targetBetweenSize);
    position.z += -(direction.z * targetBetweenSize);
    //カメラの狙ってる座標
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetweenSize));
    //位置と向きを確定
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}