#include "RotatingLaser.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "Timer.h"
#include "ObjectObserver.h"
//��]���x
const float RotatingLaser::rotaSpeed = 2.0f;
//��]���a
const float RotatingLaser::rotateRadius = 1.333f;
/// <summary>
/// ���[�U�[�̃G�t�F�N�g��ǂݍ��݈ʒu�������̃I�u�W�F�N�g����o��
/// </summary>
/// <param name="setObserver">���˃I�u�W�F�N�g�̈ʒu����ʒB���Ă��炤</param>
RotatingLaser::RotatingLaser(std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(ObjectInit::InitObjKind::laser, std::move(setObserver))
{
    EffectManager::LoadEffect(EffectKind::laser);
    //�����ƃG�t�F�N�g
    EffectManager::LoadEffect(EffectKind::laserTrack);
    direction = observer->GetSubjectDir();
}
/// <summary>
/// �G�t�F�N�g�Ɠ����蔻��̍폜
/// </summary>
RotatingLaser::~RotatingLaser()
{
    StopEffekseer3DEffect(laserEffect);
    laserEffect = -2;
    StopEffekseer3DEffect(trackEffect);
    trackEffect = -2;
    observer.reset();
}
/// <summary>
/// ���[�U�[����]������@���˂��Ă���I�u�W�F�N�g�̈ʒu��Ǐ]����
/// </summary>
void RotatingLaser::Update()
{
    position = observer->GetSubjectPos();
    //�G�t�F�N�g�I�������������񌂂�
    if (laserEffect == -1 || IsEffekseer3DEffectPlaying(laserEffect) == -1)
    {
        laserEffect = EffectManager::GetPlayEffect3D(EffectKind::laser);
    }
    //y����]
    YRotate();
}
/// <summary>
/// ���[�U�[��y����]
/// </summary>
/// <param name="rotaSpeed">��]���x</param>
/// <param name="rotateRange">��]���a</param>
void RotatingLaser::YRotate()
{
    //�����ύX�@�G�t�F�N�g�̌�����ς���
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction) * RAGE;
    //���[�U�[�̏I���_
    laserTrackPos = VAdd(position, VScale(direction, position.y * rotateRadius));
    laserTrackPos.y = 0;
    //�G�t�F�N�g�̌����Ƃ��ꏊ���C��
    SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
    if (VCross(VGet(1, 0, 0), direction).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, -effectRota, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
    }
    //�n�ʂɃ��[�U�[�ՃG�t�F�N�g
    SetLaserTrack();
}
/// <summary>
/// ���[�U�[���������ꏊ�Ɍ���o��
/// </summary>
void RotatingLaser::SetLaserTrack()
{
    //���[�U�[�Ղ̃G�t�F�N�g���\�����I������
    if (IsEffekseer3DEffectPlaying(trackEffect) == -1)
    {
        trackEffect = EffectManager::GetPlayEffect3D(EffectKind::laserTrack);
    }
    SetPosPlayingEffekseer3DEffect(trackEffect, laserTrackPos.x, 0, laserTrackPos.z);
}