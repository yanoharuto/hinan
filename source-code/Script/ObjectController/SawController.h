#pragma once
#include "AddableObjectController.h"
/// <summary>
/// プレイヤーをはじき飛ばす丸鋸
/// </summary>
class SawController : public AddableObjectController
{
public:
    /// <summary>
    /// プレイヤーをはじき飛ばす丸鋸
    /// </summary>
    SawController();
    /// <summary>
    /// 丸鋸を追加
    /// </summary>
    /// <param name="editData">追加する位置などの情報</param>
    void AddObject(PlacementData editData)override;
    /// <summary>
    /// 回転させる　破壊されたら破棄
    /// </summary>
    void Update()override;
};

