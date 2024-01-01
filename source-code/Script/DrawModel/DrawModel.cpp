#include "DrawModel.h"
#include "DxLib.h"
#include "Object.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// modelの描画をする役
/// </summary>
DrawModel::DrawModel(ObjectInit::InitObjKind kind)
{
    modelHandle = InitActor::GetModelHandle(kind);
}
/// <summary>
/// 描画
/// </summary>
/// <param name="position">位置</param>
/// <param name="rotate">回転</param>
void DrawModel::Draw(VECTOR position, VECTOR rotate)const
{
    //描画するモデルがないなら終了
    if (modelHandle != -1)
    {
        //向きを変える
        ModelSetMatrix(position,rotate);
        //描画
        MV1DrawModel(modelHandle);
    }
}

/// <summary>
/// 描画モデルの行列をセット
/// </summary>
void DrawModel::ModelSetMatrix(VECTOR position, VECTOR rotate) const
{
    // 向きに合わせて回転.
    MV1SetRotationZYAxis(modelHandle, rotate, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // モデルに向いてほしい方向に回転.
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, position);
}