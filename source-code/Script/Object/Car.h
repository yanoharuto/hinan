#pragma once
#include <iostream>
#include <memory>
#include "Actor.h"
#include "DxLib.h"
#include "InitActor.h"
struct CollisionResultInfo;
struct HitCheckInfo;
class Timer;
class Wheels;
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car abstract :public Actor
{
public:
	/// <summary>
	/// 車
	/// </summary>
	/// <param name="kind"> 欲しいオブジェクトの種類</param>
	Car(ObjectInit::InitObjKind kind);
    /// <summary>
    /// タイヤの開放
    /// </summary>
    virtual ~Car();
protected:
	/// <summary>
	/// 車がぶつかった時の関数
	/// </summary>
	/// <param name="conflictInfo">ぶつかった時の結果</param>
	virtual void ConflictReaction(const CollisionResultInfo conflictInfo);
	/// <summary>
	/// 進む方向と速さを更新する
	/// </summary>
	virtual void UpdateVelocity();
	/// <summary>
	/// modelの描画場所を更新
	/// </summary>
	void ReflectsVelocity() override;
	/// <summary>
	/// このフレームの間に進む量を出す
	/// </summary>
	/// <returns>進む量</returns>
	virtual void UpdateAccelPower();
	/// <summary>
	/// 移動速度などの初期化
	/// </summary>
	/// <param name="kind">この車の種類</param>
	void InitSpeedParamater();
	//スピードのパラメータ
	struct SpeedParamator
	{
		//加速量
		float acceleSpeed;
		//最低速度
		float lowestSpeed;
		//最高速度
		float maxSpeed;
		//急加速速度
		float turboAddSpeed;
		//急加速時間
		float turboTime;
		//曲がる力
		float gripPower;
		//止まる力
		float breakPower;
		//急加速に必要な時間
		float turboChargeTime;
	};
	//車の初期化の種類
	enum class CarInitKind
	{
		//加速量
		acceleSpeed = 0,
		//最低速度
		lowestSpeed = 1,
		//最高速度
		maxSpeed = 2,
		//急加速速度
		turboSpeed = 3,
		//急加速時間
		turboTime = 4,
		//曲がる力
		gripPower = 5,
		//止まる力
		breakePower = 6,
		//急加速に必要な時間
		turboChargeTime 
	};
	//衝突して吹っ飛ぶ時間を計る
	std::unique_ptr<Timer> bounceTimer = nullptr;
	//タイヤ
	std::unique_ptr<Wheels> wheels;
	//ぶつかった物体との方向
	VECTOR conflictVec = {};
	//ひとつ前のポジション
	VECTOR prevPos = {};
	//車のパラメーター
	SpeedParamator speedParamator;
	//速さ
	float accelPower = 0;
	//最初のY座標
	float firstPosY = 0;
	// なにもしない時の減速.
	static const float defaultDecel;
	// グリップの減速.
	static const float gripDecel;
	// 障害物にぶつかったときの減速率.
	static const float colideDecel;
	//ダメージ
	bool isBounce = false;
};