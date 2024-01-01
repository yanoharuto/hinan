#pragma once
#include "Car.h"
#include "EffectManager.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "OriginalMath.h"
constexpr float RE_SPOWN_POSITION_Y = -25.0f;
class PlayerConflictProcessor;
class SphereHitChecker;
class Timer;
 /// <summary>
 /// プレイヤーが操作する車
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	PlayerCar(PlacementData arrangementData);
	///デストラクタ
    ~PlayerCar()override;
    /// <summary>
    /// 移動処理 回転や急加速処理など
    /// </summary>
	void Update() override;
	/// <summary>
	/// ぶつかった時の処理
	/// </summary>
	/// <param name="conflictInfo"></param>
	void OnConflict(CollisionResultInfo conflictInfo)override;
	/// <summary>
	/// 機体の傾きを渡す
	/// </summary>
	/// <returns></returns>
	VECTOR GetModelRotateVec()const;
	/// <summary>
	/// 収集アイテムの回収数
	/// </summary>
	/// <returns>収集アイテムの回収数</returns>
	int GetCollectCount()const { return collectCount; };
private:
	/// <summary>
	/// 加速用ベクトルを更新
	/// </summary>
	/// <returns></returns>
	void UpdateVelocity()override;
	/// <summary>
	/// 入力するとTwistZRotaが変更する
	/// </summary>
	void UpdateRotate();
	/// <summary>
	/// 走っているときのエフェクトを更新
	/// </summary>
	void UpdateEffects();
	/// <summary>
	/// ダメージを受けた時のリアクション
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ReactionDamage(CollisionResultInfo conflictInfo);
	/// <summary>
	/// ぶつかった時のリアクション
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ReactionConflict(CollisionResultInfo conflictInfo);
	/// <summary>
	/// 左右に押しながら下を離すとブースト
	/// </summary>
	/// <returns></returns>
	float GetTurboPower();
	/// <summary>
	/// エフェクトの位置と方向をセット
	/// </summary>
	/// <param name="playEffect">対象のエフェクトハンドル</param>
	/// <param name="pos">位置</param>
	/// <param name="dir">向き</param>
	/// <param name="effectKind">エフェクトの種類</param>
	void SetEffectPosAndDir(int* playEffect,VECTOR pos,VECTOR dir,EffectKind effectKind);
	/// <summary>
	/// エフェクトを消去
	/// </summary>
	/// <param name="effectHandle">消したいエフェクト</param>
	void DeleteEffect(int effectHandle);
	/// <summary>
	/// 既定の場所まで戻る
	/// </summary>
	void ReSpown();
	/// <summary>
	/// リスポーン後の処理
	/// </summary>
	void PostReSpownProcess();
	//ターボ時間
	std::unique_ptr<Timer> turboTimer = nullptr;
	//リスポーン中フラグ
	bool isReSpown = false;
	//リスポーン中ポジション
	VECTOR reSpownPosition;
	//リスポーン中の向き
	VECTOR reSpownDirection;
	//走っているときに出るエフェクト
	int windEffect = -1;
	//ぶつかった時のエフェクト
	int clashEffect = -1;
	//ダメージを受けた時のエフェクト
	int damageEffect = -1;
	//ターボ準備中に出るエフェクト
	int turboCourceEffect = -1;
	//通常時の後ろの炎
	int defaultBurnerEffect = -1;
	//チャージ中の後ろの炎
	int chargeBurnerEffect = -1;
	//加速中の後ろの炎
	int turboBurnerEffect = -1;
	//収集アイテムの回収数
	int collectCount = 0;
	//急加速中
	bool isTurbo = false;
	//急加速準備中
	bool isTurboReserve = false;
	//加速チャージタイム
	float turboChargeTime = 0;
	//y軸回転
	float rotaY = 0;
	//縦に回転する
	float twistZRota = 0.0f;
	//ダメージを受けた時の操作不可能時間の合計
	const float setDamageReactionTime = 0.8f;
	//ダメージを受けた時に回転する量
	const float damageReactionRotaValue = 540.0f;
	//曲がったりするときに傾く速度
	const float twistZRotaSpeed = 1.7f * RAGE;
	//最大傾き度
	const float twistZMaxRota = 27.0f * RAGE;
};