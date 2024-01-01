#pragma once

#include "SceneType.h"

class FadeInFadeOut;
class SceneFlowBase;
class Clock;
class SoundPlayer;
class InitActor;
class EffectManager;
class UIManager;
/// <summary>
/// 各シーンの分岐を渡す
/// </summary>
class SceneBase abstract
{
public:
    /// <summary>
    /// 現在のシーンの保存
    /// </summary>
    /// <param name="_SceneType">現在のシーンの保存</param>
    SceneBase(SceneType _SceneType);    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase() {};
    /// <summary>
    /// シーンの更新
    /// </summary>
    /// <returns>次のシーン</returns>
    virtual SceneType Update() = 0;
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() const = 0;
protected:
    //このシーンの種類
    SceneType nowSceneType;
};