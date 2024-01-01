#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
#include "MouseInput.h"
/// <summary>
/// Editor画面のカメラ
/// </summary>
EditorCamera::EditorCamera()
    :Camera(CameraDataLoader::UseCameraSceneKind::editor)
{
    targetPos = {0,0,0};
    position = targetPos;
    position.z = 1.0f;
    position.y = posY;
    direction = VNorm(VSub(targetPos, position));
    targetBetweenSize = VSize(VSub(targetPos, position));
}
/// <summary>
/// カメラの位置を変更
/// </summary>
/// <param name="targetPlaceData">向きたい場所の配置情報</param>
void EditorCamera::UpdatePosition(std::weak_ptr<MouseInput>& input)
{   
    VECTOR moveVector = { 0,0,0 };
    //マウス入力情報
    auto mouseInput = input.lock();
    if (mouseInput == nullptr) return;
    //左右の端に来たら
    if (mouseInput->GetMouseX() > mouseInput->GetWidth() - mouseEdge || mouseInput->GetMouseX() < mouseEdge)
    {
        //右端にマウスが位置するならTrue
        bool isRightEdge = mouseInput->GetMouseX() > mouseInput->GetWidth() - mouseEdge;
        //移動ベクトルはカメラの向きから外積でとった横方向
        moveVector = VCross(direction, VGet(0,0,isRightEdge ? cameraSpeed : -cameraSpeed));

    }
    //上下の端に来たら
    else if (mouseInput->GetMouseY() > mouseInput->GetHeight() - mouseEdge || mouseInput->GetMouseY() < mouseEdge)
    {
        //下端にマウスが位置するならTrue
        bool isDownEdge = mouseInput->GetMouseY() > mouseInput->GetHeight() - mouseEdge;
        //移動ベクトルはカメラの向きかその逆方向
        moveVector = VCross(direction, VGet(isDownEdge ? cameraSpeed : -cameraSpeed, 0, 0));
    }
    position = VAdd(position, moveVector);
    //ターゲットの位置も変更
    targetPos = VAdd(position, VScale(direction, targetBetweenSize));
    //位置と向きを確定
    SetCameraPositionAndTarget_UpVecY(position, targetPos);
}
/// <summary>
/// カメラの向きとターゲットの位置を更新　
/// </summary>
/// <param name="input"></param>
void EditorCamera::UpdateTargetPosition(std::weak_ptr<MouseInput>& input)
{
    auto mouseInput = input.lock();
    if (mouseInput == nullptr) return;
    //マウスのホイール
    int wheelValue = mouseInput->GetWheelIncreaseValue(cameraSpeed);
    if (wheelValue != 0)
    {
        //カメラの向きと距離を更新
        targetBetweenSize += wheelValue;
        position = VAdd(targetPos, VScale(direction, -targetBetweenSize));
    }
}