#include "CollectCompass.h"
#include "UIManager.h"
#include "PlayerObserver.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
#include "CollectItemObserver.h"

/// <summary>
/// playerObserver��collectController�̏���
/// </summary>
/// <param name="player">�v���C���[�̈ʒu���������������</param>
/// <param name="collectItemObserver">���W�A�C�e���̋����Ȃǂ���������</param>
CollectCompass::CollectCompass(std::weak_ptr<PlayerObserver> player, std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    collectObserver= collectItemObserver;
    playerObserver = player;
    EffectManager::LoadEffect(EffectKind::comPath);
}
/// <summary>
/// �G�t�F�N�g�I��
/// </summary>
CollectCompass::~CollectCompass()
{
    StopEffekseer3DEffect(compassEffect);
}
/// <summary>
/// �G�t�F�N�g�̈ʒu�ƌ�����ݒ�
/// </summary>
void CollectCompass::Update()
{
    //�G�t�F�N�g���~�܂��Ă��������x�Đ�
    if (IsEffekseer3DEffectPlaying(compassEffect) == -1)
    {
        compassEffect = EffectManager::GetPlayEffect3D(EffectKind::comPath);
    }
    //�G�t�F�N�g�̓v���C���[�̑����ɕ\��
    VECTOR pos = playerObserver.lock()->GetSubjectPos();
    pos.y += addYPos;
    SetPosPlayingEffekseer3DEffect(compassEffect, pos.x, pos.y, pos.z);
    //�v���C���[�ƃA�C�e���Ƃ̋����x�N�g��
    VECTOR itemBetween = collectObserver.lock()->GetItemBetween(pos);
    
    float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), itemBetween);
    //���������W�A�C�e���̕����ɐݒ�
    if (VCross(VGet(1, 0, 0), itemBetween).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(compassEffect, 0, -degree * RAGE, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(compassEffect, 0, degree * RAGE, 0);
    }
}