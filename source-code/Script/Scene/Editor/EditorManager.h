#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include "InitObjKind.h"
#include "EditObjectData.h"

class EditorDrawModel;
class EditorCircleFlyShipDrawModel;
/// <summary>
/// 編集処理の流れ
/// </summary>
class EditorDrawModelManager final
{
public:
    /// <summary>
    /// 編集時の描画に必要なものを確保
    /// </summary>
    EditorDrawModelManager();
    /// <summary>
    /// 描画に使うクラスの開放
    /// </summary>
    ~EditorDrawModelManager();
    /// <summary>
    /// 引数の位置に描画
    /// </summary>
    /// <param name="placeData">描画してほしい位置</param>
    void Draw(PlacementData placeData) const;
    /// <summary>
    /// 引数の位置に描画
    /// </summary>
    /// <param name="placeData">描画してほしい位置をまとめたもの</param>
    void Draw(std::vector<PlacementData> placeData) const;
private:
    //描画クラス
    std::unordered_map<ObjectInit::InitObjKind,EditorDrawModel*> drawModelMap;
    //円形陣を組む敵の描画クラス
    EditorCircleFlyShipDrawModel* drawCircleFlyShip;
};