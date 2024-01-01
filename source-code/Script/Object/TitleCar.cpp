#include "TitleCar.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "Wheels.h"
#include "Timer.h"
/// <summary>
/// �ʒu�Ȃǂ̏������ƃG�t�F�N�g�̃��[�h
/// </summary>
/// <param name="setPos">�����ʒu</param>
/// <param name="setDir">��������</param>
/// <param name="initTimer">����I�ɏ����ʒu�ɖ߂����߂̃^�C�}�[</param>
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
/// �^�C���ƃG�t�F�N�g���
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
/// �������ɑ���
/// </summary>
void TitleCar::Update()
{
	//�^�C�}�[���v���I�����珉���ʒu��
	if (initTimer.lock()->IsOverLimitTime())
	{
		position = firstPos;
	}
	//���x���X�V
	UpdateVelocity();
	//�ʒu�̍X�V
	ReflectsVelocity();
	//�G�t�F�N�g�̍X�V
	EffectUpdate();
}
/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
void TitleCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//�G�t�F�N�g���o�ĂȂ�������o��
	if (runEffect == -1)
	{
		//�G�t�F�N�g�������Ă���o��
		runEffect = EffectManager::GetPlayEffect3D(EffectKind::carWind);
	}
	//�Ԃ̏ꏊ�Ɖ�]�ɍ��킹��
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
/// ���鑬���x�N�g���̏���
/// </summary>
/// <returns></returns>
void TitleCar::UpdateAccelPower()
{
	// ��������.
	accelPower += speedParamator.acceleSpeed;
	if (accelPower > speedParamator.maxSpeed)
	{
		accelPower = speedParamator.maxSpeed;
	}
}
