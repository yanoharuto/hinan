#pragma once
#include "AddableObjectController.h"
/// <summary>
/// 移動する回転のこぎりの管理者
/// </summary>
class MoveSawController : public AddableObjectController
{
public:
    /// <summary>
    /// 移動する回転のこぎりの管理者
    /// </summary>
    MoveSawController();
    /// <summary>
    /// 回転のこぎりを移動させる　破壊されたら破棄
    /// </summary>
    void Update()override;
protected:
    /// <summary>
    /// 移動する回転のこぎりの追加
    /// </summary>
    /// <param name="editData">位置や向き</param>
    void AddObject(PlacementData editData)override;
};

