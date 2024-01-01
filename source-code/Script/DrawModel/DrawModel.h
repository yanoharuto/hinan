#pragma once
#include "InitObjKind.h"
#include "DxLib.h"
class Object;
/// <summary>
/// modelの描画をする役
/// </summary>
class DrawModel
{
public:
    /// <summary>
    /// modelの描画をする役
    /// </summary>
    /// <param name="kind">この種類のモデルの描画を行う</param>
    DrawModel(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position">位置</param>
    /// <param name="rotate">回転</param>
    virtual void Draw(VECTOR position,VECTOR rotate) const;
protected:
    /// <summary>
    /// 描画モデルの行列をセット
    /// </summary>
    virtual void ModelSetMatrix(VECTOR position, VECTOR rotate) const;
    //描画モデル
    int modelHandle;
};