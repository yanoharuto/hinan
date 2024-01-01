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
/// �v���C���[�����삷���
/// </summary>
/// <param name="firstPos"></param>
/// <param name="setDirection"></param>
PlayerCar::PlayerCar(PlacementData arrangementData)
	:Car(ObjectInit::InitObjKind::player)
{
	//�����ʒu�ݒ�
	firstPosY = position.y;
	position.x = arrangementData.posX;
	position.z = arrangementData.posZ;
	position.y = firstPosY;
	prevPos = position;
	direction = VGet(arrangementData.dirX,0,arrangementData.dirZ);
	//�G�t�F�N�g��ǂݍ��܂���
	EffectManager::LoadEffect(EffectKind::carConflict);
	EffectManager::LoadEffect(EffectKind::carWind);
	EffectManager::LoadEffect(EffectKind::carDamage);
	EffectManager::LoadEffect(EffectKind::turboCourse);
	EffectManager::LoadEffect(EffectKind::burner);
	EffectManager::LoadEffect(EffectKind::chargeBurner);
	EffectManager::LoadEffect(EffectKind::turboBurner);
	//����ǂݍ��܂���
	SoundPlayer::LoadAndInitSound(SoundKind::playerFlight);
	SoundPlayer::LoadAndInitSound(SoundKind::playerCharge);
	SoundPlayer::LoadAndInitSound(SoundKind::playerDamage);
	reSpownDirection = direction;
	reSpownPosition = position;
	collectCount = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	SAFE_RESET(wheels);
	SAFE_RESET(bounceTimer);
	SAFE_RESET(turboTimer);
	//������
	SoundPlayer::StopSound(SoundKind::playerFlight);
	SoundPlayer::StopSound(SoundKind::playerDamage);
	//�܂��G�t�F�N�g���o�Ă�����I��
	DeleteEffect(defaultBurnerEffect);
	DeleteEffect(turboBurnerEffect);
	DeleteEffect(turboCourceEffect);
	DeleteEffect(chargeBurnerEffect);
	DeleteEffect(damageEffect);
	DeleteEffect(clashEffect);
	DeleteEffect(windEffect);
}

/// <summary>
/// �X�V
/// </summary>
void PlayerCar::Update()
{	
	//���X�|�[�����Ȃ�
	if (isReSpown)
	{
		PostReSpownProcess();
	}
	else
	{
		//���X�|�[���{�^������������ʒu���Ō�ɕ�΂�������Ƃ���܂Ŗ߂�
		if (UserInput::GetInputState(UserInput::KeyInputKind::AKey) == UserInput::InputState::Push)
		{
			ReSpown();
		}
		else
		{	
			//�@�̂��X����
			UpdateRotate();
			//���x���X�V
			UpdateVelocity();
			//�ʒu�̍X�V
			ReflectsVelocity();
			//�^�C���̍X�V
			wheels->Update();
			UpdateEffects();
		}
	}
}


/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::OnConflict(CollisionResultInfo conflictInfo)
{
	if (conflictInfo.hit == HitSituation::Enter)
	{
		if (conflictInfo.tag == ObjectTag::damageObject)//�_���[�W���󂯂�
		{
			ReactionDamage(conflictInfo);
		}
		else if (conflictInfo.tag == ObjectTag::collect)//���W�A�C�e���ɂԂ�������ďo���ʒu��ݒ�
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
/// �@�̂̌X����n��
/// </summary>
/// <returns></returns>
VECTOR PlayerCar::GetModelRotateVec()const
{
	//y����]
	float rotaY = 0;
	//�_���[�W���󂯂Ă����炮�邮���]
	if (isBounce)
	{
		rotaY = static_cast<float> (bounceTimer->GetElaspedTime() / setDamageReactionTime);
		rotaY *= damageReactionRotaValue;
	}

	return VGet(0,rotaY,twistZRota);
}

/// <summary>
/// �����p�x�N�g�����X�V
/// </summary>
/// <returns></returns>
void PlayerCar::UpdateVelocity()
{
	Car::UpdateAccelPower();

	//������
	VECTOR accelVec = VScale(direction, accelPower);

	//�_���[�W���󂯂Ă��Ȃ�������^�[�{
	if (!isBounce)
	{
		accelVec = VAdd(accelVec, VScale(direction, GetTurboPower()));
	}
	//�^�C���̌�������i�s���������
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	theta *= speedParamator.gripPower - (accelPower - speedParamator.lowestSpeed) / speedParamator.maxSpeed * speedParamator.gripPower;
	velocity = VTransform(accelVec, MGetRotY(theta));
	// �㉺�����ɂ����Ȃ��悤�Ƀx���V�e�B�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);
}
/// <summary>
/// ���͂���Ƌ@�̂��X��
/// </summary>
void PlayerCar::UpdateRotate()
{
	//�E�����������Ă���@�̂��X����
	if (UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Hold)
	{
		twistZRota = twistZRota + twistZRotaSpeed > twistZMaxRota ? twistZMaxRota : twistZRota + twistZRotaSpeed;//����l���z�������Ȃ�MaxRota���Z�b�g
	}
	else if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Hold)
	{
		twistZRota = twistZRota - twistZRotaSpeed < -twistZMaxRota? -twistZMaxRota : twistZRota - twistZRotaSpeed;
	}
	//�������Ă��Ȃ�����㉺�{�^���������Ă���Ƃ��͋@�̂𐅕��ɖ߂�
	else
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
}
/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
void PlayerCar::UpdateEffects()
{
	if (IsEffekseer3DEffectPlaying(clashEffect) != -1)//�Ԃ��������̃G�t�F�N�g�����@�̈ʒu�ɍ��킹��
	{
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
	}
	//�Ԃ̌���
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	
	if (isBounce)//�_���[�W���󂯂Ă�����
	{
		//�@�̂���o�鉊������
		if (defaultBurnerEffect != -1)
		{
			StopEffekseer3DEffect(defaultBurnerEffect);
			defaultBurnerEffect = -1;
		}
		//�X�s�[�h�o�Ă��Ȃ�������G�t�F�N�g������
		if (windEffect != -1)
		{
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
		}
		//�^�[�{���Ă���Ƃ��ɏo��i�s�������o��
		if (turboCourceEffect != -1)
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
		}
		if (damageEffect != -1)//�_���[�W�G�t�F�N�g��Ǐ]������
		{
			SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		}
	}
	else
	{
		if (isTurbo)//�}�������ɏo��G�t�F�N�g
		{
			SetEffectPosAndDir(&windEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), EffectKind::carWind);
			SetEffectPosAndDir(&turboBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), EffectKind::turboBurner);
		}
		else//�����I��
		{
			StopEffekseer3DEffect(turboBurnerEffect);
			turboBurnerEffect = -1;
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
		}
		//�^�[�{�������Ȃ�
		if (isTurboReserve)
		{
			SetEffectPosAndDir(&turboCourceEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), EffectKind::turboCourse);
			SetEffectPosAndDir(&chargeBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), EffectKind::chargeBurner);
		}
		else//�^�[�{�`���[�W���G�t�F�N�g�I��
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
			StopEffekseer3DEffect(chargeBurnerEffect);
			chargeBurnerEffect = -1;
		}
		//�^�[�{�����������Ă��Ȃ��Ȃ�
		if (!(isTurbo || isTurboReserve))
		{
			//�����Ă���Ƃ��o��G�t�F�N�g
			SetEffectPosAndDir(&defaultBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), EffectKind::burner);
		}
	}
	
}
/// <summary>
/// �_���[�W��^�������̃��A�N�V����
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ReactionDamage(CollisionResultInfo returnInfo)
{
	//�ʒu�Ɛ�����уx�N�g��������Ă���
	conflictVec = VScale(returnInfo.bounceVec,returnInfo.bouncePower);
	conflictVec.y = 0;
	SAFE_RESET(bounceTimer);
	//������Ԏ���
	bounceTimer = std::make_unique<Timer>(setDamageReactionTime);
	
	position = returnInfo.pos;
	position.y = firstPosY;
	
	if (!isBounce)
	{
		//�_���[�W���󂯂����̃G�t�F�N�g�Ɖ�
		damageEffect = EffectManager::GetPlayEffect3D(EffectKind::carDamage);
		SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(SoundKind::playerDamage);
		isBounce = true;
		twistZRota = 0.0f;
		//�������I��
		isTurbo = false;
		isTurboReserve = false;
		SAFE_RESET(turboTimer);
		//���̉�������
		DeleteEffect(chargeBurnerEffect);
		DeleteEffect(turboBurnerEffect);
		DeleteEffect(defaultBurnerEffect);
	}
}
/// <summary>
/// �Փˎ��̃��A�N�V����
/// </summary>
/// <param name="returnInfo"></param>
void PlayerCar::ReactionConflict(CollisionResultInfo returnInfo)
{
	//�^�[�{���Ȃ�
	if (isTurbo)
	{
		//�Ԃ��������̉��ƃG�t�F�N�g
		clashEffect = EffectManager::GetPlayEffect3D(EffectKind::carConflict);
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(SoundKind::playerDamage);
	}
	
	//����
	accelPower -= accelPower * colideDecel;

	//�Փ˂��Ĉړ�
	position = returnInfo.pos;
	position.y = firstPosY;
	
	//�G�t�F�N�g���ړ�
	UpdateEffects();
}
/// <summary>
/// ���E�ɉ����Ȃ��牺�𗣂��ƃu�[�X�g
/// </summary>
/// <returns></returns>
float PlayerCar::GetTurboPower()
{
	//�W���C�p�b�h��������Ή��{�^����ύX
	UserInput::InputState turboInput = UserInput::GetInputState(UserInput::KeyInputKind::Down);
	if (GetJoypadNum() != 0)
	{
		turboInput = UserInput::GetInputState(UserInput::KeyInputKind::Space);
	}
	//�������ɓ��͂���ƃ^�[�{��������
	if (turboInput == UserInput::InputState::Hold && ! isTurbo)
	{
		turboChargeTime += Utility::DELTATIME;
		//���߂ă^�[�{������
		if (!isTurboReserve)
		{
			//�`���[�W���o�[�i�[�ɕύX���ďI��
			StopEffekseer3DEffect(defaultBurnerEffect);
			chargeBurnerEffect = EffectManager::GetPlayEffect3D(EffectKind::chargeBurner);
			isTurboReserve = true;
			SoundPlayer::Play3DSE(SoundKind::playerCharge);
		}
		return 0;
	}
	else 
	{	
		//��������`���[�W�I��
		if (turboInput == UserInput::InputState::Detach)
		{
			//�\���Ƀ`���[�W�o������^�[�{�ɓ���
			if (!isTurbo && turboChargeTime > speedParamator.turboChargeTime)
			{
				//���̃^�C�}�[�̊ԋ}����
				turboTimer = std::make_unique<Timer>(speedParamator.turboTime);
				isTurbo = true;
				//��������Ƃ��̓G�t�F�N�g�Ɖ�������
				StopEffekseer3DEffect(chargeBurnerEffect);
				turboBurnerEffect = EffectManager::GetPlayEffect3D(EffectKind::turboBurner);
				SoundPlayer::Play3DSE(SoundKind::playerFlight);
			}
			//�I�������特������
			isTurboReserve = false;
			turboChargeTime = 0;
			SoundPlayer::StopSound(SoundKind::playerCharge);
		}
	}
	//�^�[�{���Ԓ�
	if (isTurbo)
	{
		//����
		if (turboTimer != nullptr && !turboTimer->IsOverLimitTime())
		{
			//�����ʂ�n��
			return static_cast<float>(turboTimer->GetRemainingTime() * speedParamator.turboAddSpeed);
		}
		else//�I����
		{
			isTurbo = false;
			SAFE_RESET(turboTimer);
		}
	}
	return 0;
}
/// <summary>
/// �G�t�F�N�g�̈ʒu�ƕ������Z�b�g
/// </summary>
/// <param name="playEffect"></param>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="effectKind"></param>
void PlayerCar::SetEffectPosAndDir(int* playEffect, VECTOR pos, VECTOR dir, EffectKind effectKind)
{
	//�G�t�F�N�g���o�ĂȂ�������o��
	if (*playEffect == -1 || IsEffekseer3DEffectPlaying(*playEffect))
	{
		*playEffect = EffectManager::GetPlayEffect3D(effectKind);
	}
	//�Ԃ̏ꏊ�ƌ����ɍ��킹��
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
/// �G�t�F�N�g������
/// </summary>
/// <param name="effectHandle">���������G�t�F�N�g</param>
void PlayerCar::DeleteEffect(int effectHandle)
{
	if (effectHandle != -1)
	{
		StopEffekseer3DEffect(effectHandle);
		effectHandle = -2;
	}
}
/// <summary>
/// ����̏ꏊ�܂Ŗ߂�
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
/// ���X�|�[����̏���
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
