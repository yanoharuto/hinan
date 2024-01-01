#include "SceneBase.h"
#include "Utility.h"

/// <summary>
/// 現在のシーンの保存
/// </summary>
/// <param name="_SceneType">現在のシーンの保存</param>
SceneBase::SceneBase(SceneType _SceneType)
{
    nowSceneType = _SceneType;
}