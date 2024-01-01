#pragma once
#include "DrawModel.h"
#include "EditObjectData.h"

class EditorObject;
/// <summary>
/// 各編集オブジェクトの描画担当役
/// </summary>
class EditorDrawModel:public DrawModel
{
public:
    /// <summary>
    /// 各編集オブジェクトの描画担当役
    /// </summary>
    /// <param name="kind">描画する物</param>
    EditorDrawModel(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 引数の場所に描画
    /// </summary>
    /// <param name="data"></param>
    virtual void Draw(PlacementData data)const;
protected:
    /// <summary>
    /// 描画モデルの行列をセット
    /// </summary>
    /// <param name="pos">位置</param>
    /// <param name="dir">方向</param>
    void ModelSetMatrix(VECTOR pos,VECTOR dir) const;
    //選択されているならちょっと位置が高くなる
    const float selectPosY = 75.0f;
};