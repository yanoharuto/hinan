#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;

/// <summary>
/// タイトル画面のカメラ　車の斜め正面を映す
/// </summary>
class TitleCamera : public Camera
{
public:

    /// <summary>
    /// タイトル画面のカメラ　車の斜め正面を映す
    /// </summary>
    TitleCamera(std::shared_ptr<ObjectObserver>& player);

    /// <summary>
    /// プレイヤーの位置に合わせてカメラが付いていく
    /// </summary>
    void Update();
private:
    //車を正面から見ないようにするためずらす角度の量
    float cameraRotate = 80.0f;
};