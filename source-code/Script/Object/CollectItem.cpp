#include "CollectItem.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
#include "InitActor.h"
//��]��
const float CollectItem::rotateY = 2.5f;
//�R�T�C���Ŏg��
const float CollectItem::moveYValue = 0.2f;
//Y�ړ����x
const float CollectItem::moveYSpeed = 4.0f;

/// <summary>
/// ������
/// </summary>
/// <param name="arrangementData"></param>
CollectItem::CollectItem(PlacementData arrangementData)
    :Actor(ObjectInit::InitObjKind::collect)
{
    //�ʒu
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    firstY = position.y;
    //�G�t�F�N�g�Ɖ�
    SoundPlayer::LoadAndInitSound(SoundKind::coinGet);
    EffectManager::LoadEffect(EffectKind::getCollect);
    EffectManager::LoadEffect(EffectKind::collectAura);
    tag = ObjectTag::collect;
}
/// <summary>
/// �G�t�F�N�g�̏I��
/// </summary>
CollectItem::~CollectItem()
{
    //�G�t�F�N�g�I��
    if (IsEffekseer3DEffectPlaying(coinAuraEffect) != -1)
    {
        StopEffekseer3DEffect(coinAuraEffect);
    }
    if (IsEffekseer3DEffectPlaying(coinGetEffect) != -1)
    {
        StopEffekseer3DEffect(coinGetEffect);
    }
}
/// <summary>
/// ���邭���]
/// </summary>
void CollectItem::Update()
{
    if (objState == ObjectState::sleep)
    {
        objState = ObjectState::active;
    }
    //�㉺�ɉ�]���Ȃ���ړ�
    MoveAndRotate();
    //�ԂɂԂ����Ă��瓖���蔻����폜
    if (isCarConflict == true)
    {
        //���ʉ����Ȃ�I����ďI��
        if(!SoundPlayer::IsPlaySound(SoundKind::coinGet))
        {
            objState = ObjectState::dead;
        }
    }
    //�R�C���̏o���I�[�����r�؂ꂽ��ĊJ������
    if (IsEffekseer3DEffectPlaying(coinAuraEffect) == -1)
    {
        coinAuraEffect = EffectManager::GetPlayEffect3D(EffectKind::collectAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y - radius, position.z);
    }
    //Velocity�𔽉f
    ReflectsVelocity();
}
/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="conflictInfo"></param>
void CollectItem::OnConflict(const CollisionResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player && objState == ObjectState::active)
    {
       //�G�t�F�N�g�Ɖ����o��
       coinGetEffect = EffectManager::GetPlayEffect2D(EffectKind::getCollect);
       float effectX = Utility::SCREEN_WIDTH / 2;
       float effectY = Utility::SCREEN_HEIGHT / 2;
       SetPosPlayingEffekseer2DEffect(coinGetEffect,effectX, effectY, 5);
       SoundPlayer::Play3DSE(SoundKind::coinGet);
       isCarConflict = true;
       objState = ObjectState::activeEnd;
    }
}
/// <summary>
/// �㉺�ɉ�]���Ȃ���ړ�
/// </summary>
void CollectItem::MoveAndRotate()
{
    //������ύX
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //������Ə㉺�ɓ���
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
}
