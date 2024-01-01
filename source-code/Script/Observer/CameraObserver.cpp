#include "CameraObserver.h"
#include "Camera.h"
#include "OriginalMath.h"
#include "Object.h"
/// <summary>
/// カメラを共有してもらう
/// </summary>
/// <param name="setCamera">共有してもらうカメラ</param>
CameraObserver::CameraObserver(std::shared_ptr<Camera> setCamera)
{
    camera = setCamera;
}
/// <summary>
/// カメラ開放
/// </summary>
CameraObserver::~CameraObserver()
{
    camera.reset();
}
/// <summary>
/// カメラの向きを所得
/// </summary>
/// <returns>編集カメラの向き</returns>
VECTOR CameraObserver::GetCameraDir() const
{
    return camera->GetNormDirection();
}
/// <summary>
/// カメラのターゲットの位置を渡す
/// </summary>
/// <returns>ターゲットの位置</returns>
VECTOR CameraObserver::GetTargetPosition() const
{
    return camera->GetTargetPosition();
}
/// <summary>
/// カメラの位置
/// </summary>
/// <returns></returns>
VECTOR CameraObserver::GetCameraPos() const
{
    return camera->GetPosition();
}

/// <summary>
/// 引数のものがカメラの範囲内か調べる
/// </summary>
/// <param name="obj">調べたいオブジェクト</param>
/// <returns>カメラの範囲内ならTrue</returns>
bool CameraObserver::IsLookingCamera(std::weak_ptr<Object>& weakObj) const
{
    auto obj = weakObj.lock();
    if (obj != nullptr)
    {
        VECTOR between = VSub(obj->GetPos(), camera->GetPosition());
        return OriginalMath::GetDegreeMisalignment(between, camera->GetNormDirection()) < camera->GetLookingAngle();
    }
}
/// <summary>
/// カメラとターゲットとの距離
/// </summary>
/// <returns></returns>
float CameraObserver::GetTargetBetweenSize() const
{
    return camera->GetTargetBetweenSize();
}
