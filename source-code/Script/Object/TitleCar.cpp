#include "TitleCar.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "Wheels.h"
#include "Timer.h"
/// <summary>
/// 位置などの初期化とエフェクトのロード
/// </summary>
/// <param name="setPos">初期位置</param>
/// <param name="setDir">初期向き</param>
/// <param name="initTimer">定期的に初期位置に戻すためのタイマー</param>
TitleCar::TitleCar(VECTOR setPos, VECTOR setDir, std::weak_ptr<Timer> setInitTimer)
    :Car(ObjectInit::InitObjKind::player)
{
	firstPosY = position.y;
	position = setPos;
	firstPos = setPos;
	position.y = firstPosY;
	prevPos = position;
	direction = setDir;
	firstDir = setDir;
	EffectManager::LoadEffect(EffectKind::carWind);
	speedParamator.acceleSpeed = setAcceleSpeed;
	speedParamator.maxSpeed = setMaxSpeed;
	initTimer = setInitTimer;
}
/// <summary>
/// タイヤとエフェクト解放
/// </summary>
TitleCar::~TitleCar()
{
	SAFE_RESET(wheels);

	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		runEffect = -1;
	}
}
/// <summary>
/// 一定方向に走る
/// </summary>
void TitleCar::Update()
{
	//タイマーが計測終えたら初期位置に
	if (initTimer.lock()->IsOverLimitTime())
	{
		position = firstPos;
	}
	//速度を更新
	UpdateVelocity();
	//位置の更新
	ReflectsVelocity();
	//エフェクトの更新
	EffectUpdate();
}
/// <summary>
/// エフェクトの更新
/// </summary>
void TitleCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//エフェクトが出てなかったら出す
	if (runEffect == -1)
	{
		//エフェクトが消えてたら出す
		runEffect = EffectManager::GetPlayEffect3D(EffectKind::carWind);
	}
	//車の場所と回転に合わせる
	SetPosPlayingEffekseer3DEffect(runEffect, position.x, 0, position.z);
	if (VCross(VGet(1, 0, 0), direction).y < 0)
	{
		SetRotationPlayingEffekseer3DEffect(runEffect, 0, -degree * RAGE, 0);
	}
	else
	{
		SetRotationPlayingEffekseer3DEffect(runEffect, 0, degree * RAGE, 0);
	}
}
/// <summary>/
/// 走る速さベクトルの所得
/// </summary>
/// <returns></returns>
void TitleCar::UpdateAccelPower()
{
	// 加速処理.
	accelPower += speedParamator.acceleSpeed;
	if (accelPower > speedParamator.maxSpeed)
	{
		accelPower = speedParamator.maxSpeed;
	}
}
