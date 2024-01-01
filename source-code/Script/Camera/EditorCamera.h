#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
#include "EditObjectData.h"
class MouseInput;
/// <summary>
/// 編集モード時のカメラ
/// </summary>
class EditorCamera : public Camera
{
public:
    /// <summary>
    /// カメラのスピードなどの初期化
    /// </summary>
    EditorCamera();
    /// <summary>
    /// 位置とターゲットの位置を更新
    /// </summary>
    /// <param name="input"></param>
    void UpdatePosition(std::weak_ptr<MouseInput>& input);
    /// <summary>
    /// カメラの向きとターゲットの位置を更新　
    /// </summary>
    /// <param name="input"></param>
    void UpdateTargetPosition(std::weak_ptr<MouseInput>& input);
private:
    //回転速度
    const float rotaSpeed = 0.01f;
    //マウスの端
    const int mouseEdge = 10;
};

