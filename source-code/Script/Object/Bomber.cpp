#include "Bomber.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "ObjectObserver.h"
//落下速度
 const float Bomber::setFallingSpeed = 0.3f;
//重力
 const float Bomber::gravityPower = 0.1f;
 //衝突後のエフェクトの大きさ
 const float Bomber::effectRadius = 200.0f;
/// <summary>
/// 上から下に落とす爆弾
/// </summary>
Bomber::Bomber(std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(ObjectInit::InitObjKind::bomber,std::move(setObserver))
{
    //落下位置は発射したキャラの位置に準拠
    position = observer->GetSubjectPos();
    //初速をセット
    fallingSpeed = setFallingSpeed;
    //エフェクト
    EffectManager::LoadEffect(EffectKind::bombExplosion);
    //向きと速度
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
}
/// <summary>
/// 球当たり判定削除
/// </summary>
Bomber::~Bomber()
{
    StopEffekseer3DEffect(burnEffect);
    observer.reset();
}
/// <summary>
/// 更新
/// </summary>
/// <param name="deltaTime"></param>
void Bomber::Update()
{
    //地面にぶつかる前は落ちていく
    if (burnEffect == -1)
    {
        //だんだん加速しながら落ちていく
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        
        //地面にぶつかりそうになかったらエフェクトを出す
        float positionY = position.y - radius;
        if (positionY < 0.0f)
        {
            burnEffect = EffectManager::GetPlayEffect3D(EffectKind::bombExplosion);
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        }
    }
    else
    {
        //エフェクトを描画し終わったら終了
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            objState = ObjectState::dead;
        }
    }
}
/// <summary>
/// 衝突後の処理
/// </summary>
void Bomber::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject && burnEffect == -1)
    {
        //ダメージ判定のあるオブジェクト以外に衝突後エフェクトを出す
        burnEffect = EffectManager::GetPlayEffect3D(EffectKind::bombExplosion);
        float positionY = position.y - radius;
        radius = effectRadius;
        SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        //当たったのがプレイヤーだったら当たり判定消失
        if (resultInfo.tag == ObjectTag::player)
        {
            objState = ObjectState::activeEnd;
        }
    }
}
