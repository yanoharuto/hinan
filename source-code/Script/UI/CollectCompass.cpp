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
/// playerObserverとcollectControllerの所得
/// </summary>
/// <param name="player">プレイヤーの位置や向きが分かるやつ</param>
/// <param name="collectItemObserver">収集アイテムの距離などが分かるやつ</param>
CollectCompass::CollectCompass(std::weak_ptr<PlayerObserver> player, std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    collectObserver= collectItemObserver;
    playerObserver = player;
    EffectManager::LoadEffect(EffectKind::comPath);
}
/// <summary>
/// エフェクト終了
/// </summary>
CollectCompass::~CollectCompass()
{
    StopEffekseer3DEffect(compassEffect);
}
/// <summary>
/// エフェクトの位置と向きを設定
/// </summary>
void CollectCompass::Update()
{
    //エフェクトが止まってたらもう一度再生
    if (IsEffekseer3DEffectPlaying(compassEffect) == -1)
    {
        compassEffect = EffectManager::GetPlayEffect3D(EffectKind::comPath);
    }
    //エフェクトはプレイヤーの足元に表示
    VECTOR pos = playerObserver.lock()->GetSubjectPos();
    pos.y += addYPos;
    SetPosPlayingEffekseer3DEffect(compassEffect, pos.x, pos.y, pos.z);
    //プレイヤーとアイテムとの距離ベクトル
    VECTOR itemBetween = collectObserver.lock()->GetItemBetween(pos);
    
    float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), itemBetween);
    //方向を収集アイテムの方向に設定
    if (VCross(VGet(1, 0, 0), itemBetween).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(compassEffect, 0, -degree * RAGE, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(compassEffect, 0, degree * RAGE, 0);
    }
}