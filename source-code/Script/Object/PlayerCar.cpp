#include <math.h>
#include <memory>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "PlayerCar.h"
#include "Wheels.h"
#include "Utility.h"	
#include "SoundPlayer.h"
#include "EffectManager.h"
#include "ConflictManager.h"
#include "AssetManager.h"
#include "SphereHitChecker.h"
#include "PlayerDrawModel.h"
#include "Timer.h"
#include "PlayerConflictProcessor.h"
#include "ConflictManager.h"

/// <summary>
/// プレイヤーが操作する車
/// </summary>
/// <param name="firstPos"></param>
/// <param name="setDirection"></param>
PlayerCar::PlayerCar(PlacementData arrangementData)
	:Car(ObjectInit::InitObjKind::player)
{
	//初期位置設定
	firstPosY = position.y;
	position.x = arrangementData.posX;
	position.z = arrangementData.posZ;
	position.y = firstPosY;
	prevPos = position;
	direction = VGet(arrangementData.dirX,0,arrangementData.dirZ);
	//エフェクトを読み込ませる
	EffectManager::LoadEffect(EffectKind::carConflict);
	EffectManager::LoadEffect(EffectKind::carWind);
	EffectManager::LoadEffect(EffectKind::carDamage);
	EffectManager::LoadEffect(EffectKind::turboCourse);
	EffectManager::LoadEffect(EffectKind::burner);
	EffectManager::LoadEffect(EffectKind::chargeBurner);
	EffectManager::LoadEffect(EffectKind::turboBurner);
	//音を読み込ませる
	SoundPlayer::LoadAndInitSound(SoundKind::playerFlight);
	SoundPlayer::LoadAndInitSound(SoundKind::playerCharge);
	SoundPlayer::LoadAndInitSound(SoundKind::playerDamage);
	reSpownDirection = direction;
	reSpownPosition = position;
	collectCount = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	SAFE_RESET(wheels);
	SAFE_RESET(bounceTimer);
	SAFE_RESET(turboTimer);
	//音消す
	SoundPlayer::StopSound(SoundKind::playerFlight);
	SoundPlayer::StopSound(SoundKind::playerDamage);
	//まだエフェクトが出ていたら終了
	DeleteEffect(defaultBurnerEffect);
	DeleteEffect(turboBurnerEffect);
	DeleteEffect(turboCourceEffect);
	DeleteEffect(chargeBurnerEffect);
	DeleteEffect(damageEffect);
	DeleteEffect(clashEffect);
	DeleteEffect(windEffect);
}

/// <summary>
/// 更新
/// </summary>
void PlayerCar::Update()
{	
	//リスポーン中なら
	if (isReSpown)
	{
		PostReSpownProcess();
	}
	else
	{
		//リスポーンボタンを押したら位置を最後に宝石を取ったところまで戻す
		if (UserInput::GetInputState(UserInput::KeyInputKind::AKey) == UserInput::InputState::Push)
		{
			ReSpown();
		}
		else
		{	
			//機体を傾ける
			UpdateRotate();
			//速度を更新
			UpdateVelocity();
			//位置の更新
			ReflectsVelocity();
			//タイヤの更新
			wheels->Update();
			UpdateEffects();
		}
	}
}


/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::OnConflict(CollisionResultInfo conflictInfo)
{
	if (conflictInfo.hit == HitSituation::Enter)
	{
		if (conflictInfo.tag == ObjectTag::damageObject)//ダメージを受けた
		{
			ReactionDamage(conflictInfo);
		}
		else if (conflictInfo.tag == ObjectTag::collect)//収集アイテムにぶつかったら再出現位置を設定
		{
			reSpownPosition = position;
			reSpownDirection = direction;
			collectCount++;
		}
		else
		{
			ReactionConflict(conflictInfo);
		}
	}
}
/// <summary>
/// 機体の傾きを渡す
/// </summary>
/// <returns></returns>
VECTOR PlayerCar::GetModelRotateVec()const
{
	//y軸回転
	float rotaY = 0;
	//ダメージを受けていたらぐるぐる回転
	if (isBounce)
	{
		rotaY = static_cast<float> (bounceTimer->GetElaspedTime() / setDamageReactionTime);
		rotaY *= damageReactionRotaValue;
	}

	return VGet(0,rotaY,twistZRota);
}

/// <summary>
/// 加速用ベクトルを更新
/// </summary>
/// <returns></returns>
void PlayerCar::UpdateVelocity()
{
	Car::UpdateAccelPower();

	//加速量
	VECTOR accelVec = VScale(direction, accelPower);

	//ダメージを受けていなかったらターボ
	if (!isBounce)
	{
		accelVec = VAdd(accelVec, VScale(direction, GetTurboPower()));
	}
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	theta *= speedParamator.gripPower - (accelPower - speedParamator.lowestSpeed) / speedParamator.maxSpeed * speedParamator.gripPower;
	velocity = VTransform(accelVec, MGetRotY(theta));
	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);
}
/// <summary>
/// 入力すると機体が傾く
/// </summary>
void PlayerCar::UpdateRotate()
{
	//右か左か押してたら機体を傾ける
	if (UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Hold)
	{
		twistZRota = twistZRota + twistZRotaSpeed > twistZMaxRota ? twistZMaxRota : twistZRota + twistZRotaSpeed;//上限値を越しそうならMaxRotaをセット
	}
	else if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Hold)
	{
		twistZRota = twistZRota - twistZRotaSpeed < -twistZMaxRota? -twistZMaxRota : twistZRota - twistZRotaSpeed;
	}
	//何もしていない時や上下ボタンを押しているときは機体を水平に戻す
	else
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
}
/// <summary>
/// エフェクトの更新
/// </summary>
void PlayerCar::UpdateEffects()
{
	if (IsEffekseer3DEffectPlaying(clashEffect) != -1)//ぶつかった時のエフェクトを自機の位置に合わせる
	{
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
	}
	//車の向き
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	
	if (isBounce)//ダメージを受けていたら
	{
		//機体から出る炎を消す
		if (defaultBurnerEffect != -1)
		{
			StopEffekseer3DEffect(defaultBurnerEffect);
			defaultBurnerEffect = -1;
		}
		//スピード出ていなかったらエフェクトを消す
		if (windEffect != -1)
		{
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
		}
		//ターボしているときに出る進行方向を出す
		if (turboCourceEffect != -1)
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
		}
		if (damageEffect != -1)//ダメージエフェクトを追従させる
		{
			SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		}
	}
	else
	{
		if (isTurbo)//急加速中に出るエフェクト
		{
			SetEffectPosAndDir(&windEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), EffectKind::carWind);
			SetEffectPosAndDir(&turboBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), EffectKind::turboBurner);
		}
		else//加速終了
		{
			StopEffekseer3DEffect(turboBurnerEffect);
			turboBurnerEffect = -1;
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
		}
		//ターボ準備中なら
		if (isTurboReserve)
		{
			SetEffectPosAndDir(&turboCourceEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), EffectKind::turboCourse);
			SetEffectPosAndDir(&chargeBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), EffectKind::chargeBurner);
		}
		else//ターボチャージ中エフェクト終了
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
			StopEffekseer3DEffect(chargeBurnerEffect);
			chargeBurnerEffect = -1;
		}
		//ターボも準備もしていないなら
		if (!(isTurbo || isTurboReserve))
		{
			//走っているとき出るエフェクト
			SetEffectPosAndDir(&defaultBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), EffectKind::burner);
		}
	}
	
}
/// <summary>
/// ダメージを与えた時のリアクション
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ReactionDamage(CollisionResultInfo returnInfo)
{
	//位置と吹っ飛びベクトルを取ってくる
	conflictVec = VScale(returnInfo.bounceVec,returnInfo.bouncePower);
	conflictVec.y = 0;
	SAFE_RESET(bounceTimer);
	//吹っ飛ぶ時間
	bounceTimer = std::make_unique<Timer>(setDamageReactionTime);
	
	position = returnInfo.pos;
	position.y = firstPosY;
	
	if (!isBounce)
	{
		//ダメージを受けた時のエフェクトと音
		damageEffect = EffectManager::GetPlayEffect3D(EffectKind::carDamage);
		SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(SoundKind::playerDamage);
		isBounce = true;
		twistZRota = 0.0f;
		//加速も終了
		isTurbo = false;
		isTurboReserve = false;
		SAFE_RESET(turboTimer);
		//後ろの炎も消す
		DeleteEffect(chargeBurnerEffect);
		DeleteEffect(turboBurnerEffect);
		DeleteEffect(defaultBurnerEffect);
	}
}
/// <summary>
/// 衝突時のリアクション
/// </summary>
/// <param name="returnInfo"></param>
void PlayerCar::ReactionConflict(CollisionResultInfo returnInfo)
{
	//ターボ中なら
	if (isTurbo)
	{
		//ぶつかった時の音とエフェクト
		clashEffect = EffectManager::GetPlayEffect3D(EffectKind::carConflict);
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(SoundKind::playerDamage);
	}
	
	//減速
	accelPower -= accelPower * colideDecel;

	//衝突して移動
	position = returnInfo.pos;
	position.y = firstPosY;
	
	//エフェクトも移動
	UpdateEffects();
}
/// <summary>
/// 左右に押しながら下を離すとブースト
/// </summary>
/// <returns></returns>
float PlayerCar::GetTurboPower()
{
	//ジョイパッドだったら対応ボタンを変更
	UserInput::InputState turboInput = UserInput::GetInputState(UserInput::KeyInputKind::Down);
	if (GetJoypadNum() != 0)
	{
		turboInput = UserInput::GetInputState(UserInput::KeyInputKind::Space);
	}
	//下方向に入力するとターボ準備完了
	if (turboInput == UserInput::InputState::Hold && ! isTurbo)
	{
		turboChargeTime += Utility::DELTATIME;
		//初めてターボ準備中
		if (!isTurboReserve)
		{
			//チャージ中バーナーに変更して終了
			StopEffekseer3DEffect(defaultBurnerEffect);
			chargeBurnerEffect = EffectManager::GetPlayEffect3D(EffectKind::chargeBurner);
			isTurboReserve = true;
			SoundPlayer::Play3DSE(SoundKind::playerCharge);
		}
		return 0;
	}
	else 
	{	
		//離したらチャージ終了
		if (turboInput == UserInput::InputState::Detach)
		{
			//十分にチャージ出来たらターボに入る
			if (!isTurbo && turboChargeTime > speedParamator.turboChargeTime)
			{
				//このタイマーの間急加速
				turboTimer = std::make_unique<Timer>(speedParamator.turboTime);
				isTurbo = true;
				//加速するときはエフェクトと音が発生
				StopEffekseer3DEffect(chargeBurnerEffect);
				turboBurnerEffect = EffectManager::GetPlayEffect3D(EffectKind::turboBurner);
				SoundPlayer::Play3DSE(SoundKind::playerFlight);
			}
			//終了したら音を消す
			isTurboReserve = false;
			turboChargeTime = 0;
			SoundPlayer::StopSound(SoundKind::playerCharge);
		}
	}
	//ターボ期間中
	if (isTurbo)
	{
		//加速
		if (turboTimer != nullptr && !turboTimer->IsOverLimitTime())
		{
			//加速量を渡す
			return static_cast<float>(turboTimer->GetRemainingTime() * speedParamator.turboAddSpeed);
		}
		else//終了後
		{
			isTurbo = false;
			SAFE_RESET(turboTimer);
		}
	}
	return 0;
}
/// <summary>
/// エフェクトの位置と方向をセット
/// </summary>
/// <param name="playEffect"></param>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="effectKind"></param>
void PlayerCar::SetEffectPosAndDir(int* playEffect, VECTOR pos, VECTOR dir, EffectKind effectKind)
{
	//エフェクトが出てなかったら出す
	if (*playEffect == -1 || IsEffekseer3DEffectPlaying(*playEffect))
	{
		*playEffect = EffectManager::GetPlayEffect3D(effectKind);
	}
	//車の場所と向きに合わせる
	SetPosPlayingEffekseer3DEffect(*playEffect, pos.x, pos.y, pos.z);
	if (VCross(VGet(1, 0, 0), direction).y < 0)
	{
		SetRotationPlayingEffekseer3DEffect(*playEffect, dir.x, -dir.y, dir.z);
	}
	else
	{
		SetRotationPlayingEffekseer3DEffect(*playEffect, dir.x, dir.y, dir.z); 
	}
}
/// <summary>
/// エフェクトを消去
/// </summary>
/// <param name="effectHandle">消したいエフェクト</param>
void PlayerCar::DeleteEffect(int effectHandle)
{
	if (effectHandle != -1)
	{
		StopEffekseer3DEffect(effectHandle);
		effectHandle = -2;
	}
}
/// <summary>
/// 既定の場所まで戻る
/// </summary>
void PlayerCar::ReSpown()
{
	position = reSpownPosition;
	direction = reSpownDirection;
	position.y = RE_SPOWN_POSITION_Y;
	isReSpown = true;
	isTurbo = false;
	isTurboReserve = false;
	SAFE_RESET(turboTimer);
}
/// <summary>
/// リスポーン後の処理
/// </summary>
void PlayerCar::PostReSpownProcess()
{
	position.y++;
	UpdateEffects();
	StopEffekseer3DEffect(defaultBurnerEffect);
	defaultBurnerEffect = -1;
	if (position.y > firstPosY)
	{
		position.y = firstPosY;
		isReSpown = false;
	}
}
