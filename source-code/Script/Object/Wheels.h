#pragma once
#include "DxLib.h"
#include <string>

/// <summary>
/// タイヤのY軸制御と回転半径を出す
/// </summary>
class Wheels 
{
public:
	/// <summary>
	/// タイヤの左右の傾きを初期化
	/// </summary>
	Wheels();
	/// <summary>
	/// 左右キーを入力したらタイヤの角度を変更
	/// </summary>
	void Update();
	/// <summary>
	/// 進行方向が何度曲がるか返す
	/// </summary>
	/// <param name="velocitySize">速さのベクトルの大きさ</param>
	/// <returns>進行方向が左右に何度ずれるか返す</returns>
	float GetMoveDirTheta(const float velocitySize) const;
private:	
	/// <summary>
    /// 回転するための半径を返す
    /// </summary>
	/// <returns>回転半径</returns>
	float GetRotationRadius() const;
	//車の左右への傾き
	float axisY = 0.0f;
	//車の回転力
	static const float wheelDriveRotaPower;
	//タイヤが左右に傾く力
	static const float wheelCurvePower;
	//この角度までタイヤは傾くよ
	static const float maxAxisY;
	//進行方向に影響するまでに必要なタイヤの角度
	static const float curbCalculationLine;
	//軸距　前輪と後輪の距離
	static const float wheelbase;
};