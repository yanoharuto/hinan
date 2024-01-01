#include "Car.h"
#include "OriginalMath.h"
#include "Wheels.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundPlayer.h"
#include "HitCheckExamineObjectInfo.h"
#include "UserInput.h"
#include "Timer.h"
#include "InitActor.h"
#include "AddPlayerDataLoader.h"

// なにもしない時の減速.
const float Car::defaultDecel = 0.01f;
// 障害物にぶつかったときの減速率.
const float Car:: colideDecel = 0.08f;
// グリップの減速.
const float Car::gripDecel = 0.2f;
/// <summary>
/// 初期化
/// </summary>
/// <param name="param"></param>
Car::Car(ObjectInit::InitObjKind kind)
	:Actor(kind)
{
	InitSpeedParamater();
	tag = ObjectTag::player;
	ReflectsVelocity();
	wheels = std::make_unique<Wheels>();
}
/// <summary>
/// タイヤの開放
/// </summary>
Car::~Car()
{
	SAFE_RESET(wheels);
}
/// <summary>
/// 車がぶつかった時の関数
/// </summary>
/// <param name="conflictInfo">ぶつかった時の結果</param>
void Car::ConflictReaction(CollisionResultInfo conflictInfo)
{
	conflictVec = conflictInfo.bounceVec;
	conflictVec.y = 0;
	//減速
	accelPower -= accelPower * colideDecel;
	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;
	ReflectsVelocity();
}
/// <summary>
/// 進む方向と速さを更新する
/// </summary>
void Car::UpdateVelocity()
{
	//加速する
	UpdateAccelPower();
	//移動量を作成
	VECTOR accelVec = VScale(direction, accelPower);
	//タイヤの向きから進行方向のずれを所得
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	//早いほど曲がりにくくなるようにする
	theta *= speedParamator.gripPower - accelPower / speedParamator.maxSpeed;
	//加速量をタイヤの向きで変化させる
	velocity = VTransform(accelVec, MGetRotY(theta));
	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// modelの描画場所を更新
/// </summary>
void Car::ReflectsVelocity()
{
	//更新する前のポジションを保存
	prevPos = position;
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) > 0.1f)
	{
		direction = VNorm(velocity);
	}
	//ぶつかった時の衝撃影響タイマーがNewされているなら
	if (isBounce)
	{
		auto scale = static_cast<float>(bounceTimer->GetRemainingTime() / bounceTimer->GetLimitTime());
		//ぶつかった時の衝撃で移動
		velocity = VScale(conflictVec, scale);
		position = VAdd(position, velocity);
		//吹っ飛ぶ時間を過ぎたなら
		if (bounceTimer->IsOverLimitTime())
		{
			isBounce = false;
			SAFE_RESET(bounceTimer);
		}
	}
	else //衝撃が無くなったら運転できる
	{
		// ポジションを更新.
		position = VAdd(position, velocity);
	}
}
/// <summary>
/// このフレームの間に進む量を出す
/// </summary>
/// <returns>進む量</returns>
void Car::UpdateAccelPower()
{
	//ジョイパッドだったらブレーキの対応ボタンを変更
	UserInput::InputState breakInput = UserInput::GetInputState(UserInput::KeyInputKind::Down);
	if (UserInput::IsInputPad())
	{
		breakInput = UserInput::GetInputState(UserInput::KeyInputKind::Space);
	}
	//ブレーキした
	if (breakInput == UserInput::InputState::Hold)
	{
		accelPower -= accelPower * speedParamator.breakPower;
	}
	else//してないなら加速
	{
		accelPower += speedParamator.acceleSpeed;
		if (accelPower > speedParamator.maxSpeed)//上限
		{
			accelPower = speedParamator.maxSpeed;
		}
	}
	//左右に曲がろうとしていたら減速
	if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Hold && UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Hold)
	{
		//左右に曲がろうとしたら減速する
		accelPower -= accelPower * gripDecel;
	}
	//最低速度
	if (accelPower < speedParamator.lowestSpeed)
	{
		accelPower = speedParamator.lowestSpeed;
	}
}
/// <summary>
/// 移動速度などの初期化
/// </summary>
/// <param name="kind"></param>
void Car::InitSpeedParamater()
{
	//速さ関連の情報を所得
	auto loader = std::make_unique<AddPlayerDataLoader>();
	auto strVec = loader->GetLoadData();
	//車の性能を初期化
	speedParamator.acceleSpeed = STR_TO_F(strVec[static_cast<int>(CarInitKind::acceleSpeed)]);
	speedParamator.lowestSpeed = STR_TO_F(strVec[static_cast<int>(CarInitKind::lowestSpeed)]);
	speedParamator.maxSpeed = STR_TO_F(strVec[static_cast<int>(CarInitKind::maxSpeed)]);
	speedParamator.turboAddSpeed = STR_TO_F(strVec[static_cast<int>(CarInitKind::turboSpeed)]);
	speedParamator.turboTime = STR_TO_F(strVec[static_cast<int>(CarInitKind::turboTime)]);
	speedParamator.gripPower = STR_TO_F(strVec[static_cast<int>(CarInitKind::gripPower)]);
	speedParamator.breakPower = STR_TO_F(strVec[static_cast<int>(CarInitKind::breakePower)]);
	speedParamator.turboChargeTime = STR_TO_F(strVec[static_cast<int>(CarInitKind::turboChargeTime)]);
	SAFE_RESET(loader);
}