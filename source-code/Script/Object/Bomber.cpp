#include "Bomber.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "ObjectObserver.h"
//�������x
 const float Bomber::setFallingSpeed = 0.3f;
//�d��
 const float Bomber::gravityPower = 0.1f;
 //�Փˌ�̃G�t�F�N�g�̑傫��
 const float Bomber::effectRadius = 200.0f;
/// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
Bomber::Bomber(std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(ObjectInit::InitObjKind::bomber,std::move(setObserver))
{
    //�����ʒu�͔��˂����L�����̈ʒu�ɏ���
    position = observer->GetSubjectPos();
    //�������Z�b�g
    fallingSpeed = setFallingSpeed;
    //�G�t�F�N�g
    EffectManager::LoadEffect(EffectKind::bombExplosion);
    //�����Ƒ��x
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
}
/// <summary>
/// �������蔻��폜
/// </summary>
Bomber::~Bomber()
{
    StopEffekseer3DEffect(burnEffect);
    observer.reset();
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="deltaTime"></param>
void Bomber::Update()
{
    //�n�ʂɂԂ���O�͗����Ă���
    if (burnEffect == -1)
    {
        //���񂾂�������Ȃ��痎���Ă���
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        
        //�n�ʂɂԂ��肻���ɂȂ�������G�t�F�N�g���o��
        float positionY = position.y - radius;
        if (positionY < 0.0f)
        {
            burnEffect = EffectManager::GetPlayEffect3D(EffectKind::bombExplosion);
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        }
    }
    else
    {
        //�G�t�F�N�g��`�悵�I�������I��
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            objState = ObjectState::dead;
        }
    }
}
/// <summary>
/// �Փˌ�̏���
/// </summary>
void Bomber::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject && burnEffect == -1)
    {
        //�_���[�W����̂���I�u�W�F�N�g�ȊO�ɏՓˌ�G�t�F�N�g���o��
        burnEffect = EffectManager::GetPlayEffect3D(EffectKind::bombExplosion);
        float positionY = position.y - radius;
        radius = effectRadius;
        SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        //���������̂��v���C���[�������瓖���蔻�����
        if (resultInfo.tag == ObjectTag::player)
        {
            objState = ObjectState::activeEnd;
        }
    }
}
