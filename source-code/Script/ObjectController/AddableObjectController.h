#pragma once
#include "ActorController.h"
/// <summary>
/// 編集して位置が決まっているオブジェクトの管理クラス
/// </summary>
class AddableObjectController abstract : public ActorController
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="kind">初期化したいオブジェクトの種類</param>
    AddableObjectController(ObjectInit::InitObjKind kind);
    /// <summary>
    /// リストに対象のオブジェクトを纏めて追加
    /// </summary>
    /// <param name="placeDataVec">配置位置リスト</param>
    virtual void OnAddObject(std::vector<PlacementData> placeDataVec);
protected:
    /// <summary>
    /// リストに対象のオブジェクトを追加
    /// </summary>
    /// <param name="placeData">配置位置</param>
    virtual void AddObject(PlacementData placeData) = 0;
};