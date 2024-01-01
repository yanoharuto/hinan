#include "Wheels.h"
#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "AssetManager.h"
//車の回転力
const float Wheels::wheelDriveRotaPower = 4.4f;
//タイヤが左右に傾く力
const float Wheels::wheelCurvePower = 1.7f;
//この角度までタイヤは傾くよ
const float Wheels::maxAxisY = 45.5f;
//進行方向に影響するまでに必要なタイヤの角度
const float Wheels::curbCalculationLine = 1.2f;
//軸距　前輪と後輪の距離
const float Wheels::wheelbase = 10.0f;
/// <summary>
/// タイヤの左右の傾きを初期化
/// </summary>
Wheels::Wheels()
{
	axisY = 0.0f;
}
/// <summary>
/// 左右キーを入力したらタイヤの角度を変更
/// </summary>
void Wheels::Update()
{	
	//右を押したら
	if (UserInput::GetInputState(UserInput::KeyInputKind::Right) != UserInput::InputState::Free)
	{		
		//y軸回転
		axisY = axisY < maxAxisY ? axisY + wheelCurvePower : maxAxisY;
	}
	//左を押したら
	else if (UserInput::GetInputState(UserInput::KeyInputKind::Left) != UserInput::InputState::Free)
	{
		axisY = axisY > -maxAxisY ? axisY - wheelCurvePower : -maxAxisY;
	}
	//どっちも押されてなかったらタイヤを元に戻す
	else if (fabsf(axisY) > curbCalculationLine)
	{
		axisY += axisY > 0 ? -wheelCurvePower : wheelCurvePower;
		//ある程度戻ってたら角度を0にする
		if (fabsf(axisY) < curbCalculationLine)
		{
			axisY = 0;
		}
	}	
}

/// <summary>
/// 進行方向が何度曲がるか返す
/// </summary>
/// <param name="velocitySize">速さのベクトルの大きさ</param>
/// <returns>進行方向が左右に何度ずれるか返す</returns>
float Wheels::GetMoveDirTheta(const float velocitySize)const
{
	//右にタイヤが曲がっているなら
	if (axisY > curbCalculationLine)
	{
		//回転半径と移動速度で曲がる量を出す
		return atan2f(velocitySize, GetRotationRadius()); 
	}
	//左にタイヤが曲がっているなら
	else if (axisY < -curbCalculationLine)
	{
		return -atan2f(velocitySize,GetRotationRadius());
	}
	return 0.0f;
}

/// <summary>
/// 回転するための半径を返す
/// </summary>
/// <returns>回転半径</returns>
float Wheels::GetRotationRadius()const
{
	//ある程度タイヤが曲がっていたら曲がり始める
	if (fabsf(axisY) > curbCalculationLine)
	{
		//タイヤの角度をタンジェントに
		float rota = tan(static_cast<float> (fabsf(axisY)) * RAGE);
		//軸距を割って回転半径を出す
		return  wheelbase / rota;
	}
	return 0.0f;
}
