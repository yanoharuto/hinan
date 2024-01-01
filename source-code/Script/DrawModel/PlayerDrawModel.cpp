#include "PlayerDrawModel.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "PlayerCar.h"
/// <summary>
	/// プレイヤーの機体の傾きなどに対応する
	/// </summary>
PlayerDrawModel::PlayerDrawModel()
	:DrawModel(ObjectInit::InitObjKind::player)
{
}
/// <summary>
/// プレイヤーの角度に合わせて回転する
/// </summary>
/// <param name="drawObj"></param>
void PlayerDrawModel::Draw(VECTOR position, VECTOR direction, VECTOR rotate) const
{
    //描画するモデルがないなら終了
    if (modelHandle == -1)return;
    //変更前の行列を保存
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    //向きを変える
    ModelSetMatrix(position, direction, rotate);
    MV1DrawModel(modelHandle);
}

/// <summary>
/// 描画モデルの行列をセット
/// </summary>
void PlayerDrawModel::ModelSetMatrix(VECTOR position, VECTOR direction, VECTOR rotate) const
{	
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), rotate.z);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f + rotate.y) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);
}