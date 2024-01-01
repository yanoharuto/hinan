#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class PlayerObserver;
/// <summary>
/// 遊んでいるときのカメラ
/// </summary>
class GameCamera final : public Camera
{
public:
    /// <summary>
    /// 遊んでいるときのカメラの初期化
    /// </summary>
    /// <param name="player">プレイヤーの位置</param>
    GameCamera(std::shared_ptr<PlayerObserver>& player);
    /// <summary>
    /// 位置や向きの更新
    /// </summary>
    void Update();
};

