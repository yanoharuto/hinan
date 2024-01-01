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
 /// �v���C���[�����삷���
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	PlayerCar(PlacementData arrangementData);
	///�f�X�g���N�^
    ~PlayerCar()override;
    /// <summary>
    /// �ړ����� ��]��}���������Ȃ�
    /// </summary>
	void Update() override;
	/// <summary>
	/// �Ԃ��������̏���
	/// </summary>
	/// <param name="conflictInfo"></param>
	void OnConflict(CollisionResultInfo conflictInfo)override;
	/// <summary>
	/// �@�̂̌X����n��
	/// </summary>
	/// <returns></returns>
	VECTOR GetModelRotateVec()const;
	/// <summary>
	/// ���W�A�C�e���̉����
	/// </summary>
	/// <returns>���W�A�C�e���̉����</returns>
	int GetCollectCount()const { return collectCount; };
private:
	/// <summary>
	/// �����p�x�N�g�����X�V
	/// </summary>
	/// <returns></returns>
	void UpdateVelocity()override;
	/// <summary>
	/// ���͂����TwistZRota���ύX����
	/// </summary>
	void UpdateRotate();
	/// <summary>
	/// �����Ă���Ƃ��̃G�t�F�N�g���X�V
	/// </summary>
	void UpdateEffects();
	/// <summary>
	/// �_���[�W���󂯂����̃��A�N�V����
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ReactionDamage(CollisionResultInfo conflictInfo);
	/// <summary>
	/// �Ԃ��������̃��A�N�V����
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ReactionConflict(CollisionResultInfo conflictInfo);
	/// <summary>
	/// ���E�ɉ����Ȃ��牺�𗣂��ƃu�[�X�g
	/// </summary>
	/// <returns></returns>
	float GetTurboPower();
	/// <summary>
	/// �G�t�F�N�g�̈ʒu�ƕ������Z�b�g
	/// </summary>
	/// <param name="playEffect">�Ώۂ̃G�t�F�N�g�n���h��</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="dir">����</param>
	/// <param name="effectKind">�G�t�F�N�g�̎��</param>
	void SetEffectPosAndDir(int* playEffect,VECTOR pos,VECTOR dir,EffectKind effectKind);
	/// <summary>
	/// �G�t�F�N�g������
	/// </summary>
	/// <param name="effectHandle">���������G�t�F�N�g</param>
	void DeleteEffect(int effectHandle);
	/// <summary>
	/// ����̏ꏊ�܂Ŗ߂�
	/// </summary>
	void ReSpown();
	/// <summary>
	/// ���X�|�[����̏���
	/// </summary>
	void PostReSpownProcess();
	//�^�[�{����
	std::unique_ptr<Timer> turboTimer = nullptr;
	//���X�|�[�����t���O
	bool isReSpown = false;
	//���X�|�[�����|�W�V����
	VECTOR reSpownPosition;
	//���X�|�[�����̌���
	VECTOR reSpownDirection;
	//�����Ă���Ƃ��ɏo��G�t�F�N�g
	int windEffect = -1;
	//�Ԃ��������̃G�t�F�N�g
	int clashEffect = -1;
	//�_���[�W���󂯂����̃G�t�F�N�g
	int damageEffect = -1;
	//�^�[�{�������ɏo��G�t�F�N�g
	int turboCourceEffect = -1;
	//�ʏ펞�̌��̉�
	int defaultBurnerEffect = -1;
	//�`���[�W���̌��̉�
	int chargeBurnerEffect = -1;
	//�������̌��̉�
	int turboBurnerEffect = -1;
	//���W�A�C�e���̉����
	int collectCount = 0;
	//�}������
	bool isTurbo = false;
	//�}����������
	bool isTurboReserve = false;
	//�����`���[�W�^�C��
	float turboChargeTime = 0;
	//y����]
	float rotaY = 0;
	//�c�ɉ�]����
	float twistZRota = 0.0f;
	//�_���[�W���󂯂����̑���s�\���Ԃ̍��v
	const float setDamageReactionTime = 0.8f;
	//�_���[�W���󂯂����ɉ�]�����
	const float damageReactionRotaValue = 540.0f;
	//�Ȃ������肷��Ƃ��ɌX�����x
	const float twistZRotaSpeed = 1.7f * RAGE;
	//�ő�X���x
	const float twistZMaxRota = 27.0f * RAGE;
};