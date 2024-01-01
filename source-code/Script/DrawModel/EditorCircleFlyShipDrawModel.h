#pragma once
#include "EditorDrawModel.h"

/// <summary>
/// 円形上に陣形を組む敵の描画担当
/// </summary>
class EditorCircleFlyShipDrawModel final : public EditorDrawModel
{
public:
    /// <summary>
    /// 円形飛行艇は編集時は陣形の飛行機纏めて描画する
    /// そのために必要な情報を初期化
    /// </summary>
    EditorCircleFlyShipDrawModel();
    /// <summary>
    /// 描画する
    /// </summary>
    /// <param name="data">配置情報</param>
    void Draw(PlacementData data)const override;
    /// <summary>
    /// 引数のmodelの位置や回転に合わせて描画する
    /// </summary>
    /// <param name="drawObj">位置とか教えてももらう</param>
    void Draw(VECTOR position, VECTOR rotate)const override;
private:
    /// <summary>
    /// 初期化
    /// </summary>
    void Init();
    //ユニットの数
    int uniNum = 0;
    //各ユニットの方向への角度
    float uniDirRota = 0.0f;
    //ユニット同士の距離
    float uniBetween=0.0f;
};