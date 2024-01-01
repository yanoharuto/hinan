#include "CollectItem.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
#include "InitActor.h"
//回転量
const float CollectItem::rotateY = 2.5f;
//コサインで使う
const float CollectItem::moveYValue = 0.2f;
//Y移動速度
const float CollectItem::moveYSpeed = 4.0f;

/// <summary>
/// 初期化
/// </summary>
/// <param name="arrangementData"></param>
CollectItem::CollectItem(PlacementData arrangementData)
    :Actor(ObjectInit::InitObjKind::collect)
{
    //位置
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    firstY = position.y;
    //エフェクトと音
    SoundPlayer::LoadAndInitSound(SoundKind::coinGet);
    EffectManager::LoadEffect(EffectKind::getCollect);
    EffectManager::LoadEffect(EffectKind::collectAura);
    tag = ObjectTag::collect;
}
/// <summary>
/// エフェクトの終了
/// </summary>
CollectItem::~CollectItem()
{
    //エフェクト終了
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
/// くるくる回転
/// </summary>
void CollectItem::Update()
{
    if (objState == ObjectState::sleep)
    {
        objState = ObjectState::active;
    }
    //上下に回転しながら移動
    MoveAndRotate();
    //車にぶつかってたら当たり判定を削除
    if (isCarConflict == true)
    {
        //効果音がなり終わって終了
        if(!SoundPlayer::IsPlaySound(SoundKind::coinGet))
        {
            objState = ObjectState::dead;
        }
    }
    //コインの出すオーラが途切れたら再開させる
    if (IsEffekseer3DEffectPlaying(coinAuraEffect) == -1)
    {
        coinAuraEffect = EffectManager::GetPlayEffect3D(EffectKind::collectAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y - radius, position.z);
    }
    //Velocityを反映
    ReflectsVelocity();
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="conflictInfo"></param>
void CollectItem::OnConflict(const CollisionResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player && objState == ObjectState::active)
    {
       //エフェクトと音を出す
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
/// 上下に回転しながら移動
/// </summary>
void CollectItem::MoveAndRotate()
{
    //向きを変更
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //ちょっと上下に動く
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
}
