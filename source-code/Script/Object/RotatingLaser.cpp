#include "RotatingLaser.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "Timer.h"
#include "ObjectObserver.h"
//回転速度
const float RotatingLaser::rotaSpeed = 2.0f;
//回転半径
const float RotatingLaser::rotateRadius = 1.333f;
/// <summary>
/// レーザーのエフェクトを読み込み位置を引数のオブジェクトから出す
/// </summary>
/// <param name="setObserver">発射オブジェクトの位置等を通達してもらう</param>
RotatingLaser::RotatingLaser(std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(ObjectInit::InitObjKind::laser, std::move(setObserver))
{
    EffectManager::LoadEffect(EffectKind::laser);
    //向きとエフェクト
    EffectManager::LoadEffect(EffectKind::laserTrack);
    direction = observer->GetSubjectDir();
}
/// <summary>
/// エフェクトと当たり判定の削除
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
/// レーザーを回転させる　発射しているオブジェクトの位置を追従する
/// </summary>
void RotatingLaser::Update()
{
    position = observer->GetSubjectPos();
    //エフェクト終了したらもう一回撃つ
    if (laserEffect == -1 || IsEffekseer3DEffectPlaying(laserEffect) == -1)
    {
        laserEffect = EffectManager::GetPlayEffect3D(EffectKind::laser);
    }
    //y軸回転
    YRotate();
}
/// <summary>
/// レーザーのy軸回転
/// </summary>
/// <param name="rotaSpeed">回転速度</param>
/// <param name="rotateRange">回転半径</param>
void RotatingLaser::YRotate()
{
    //方向変更　エフェクトの向きを変える
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction) * RAGE;
    //レーザーの終着点
    laserTrackPos = VAdd(position, VScale(direction, position.y * rotateRadius));
    laserTrackPos.y = 0;
    //エフェクトの向きとか場所を修正
    SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
    if (VCross(VGet(1, 0, 0), direction).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, -effectRota, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
    }
    //地面にレーザー跡エフェクト
    SetLaserTrack();
}
/// <summary>
/// レーザーを撃った場所に後を出す
/// </summary>
void RotatingLaser::SetLaserTrack()
{
    //レーザー跡のエフェクトが表示し終えたら
    if (IsEffekseer3DEffectPlaying(trackEffect) == -1)
    {
        trackEffect = EffectManager::GetPlayEffect3D(EffectKind::laserTrack);
    }
    SetPosPlayingEffekseer3DEffect(trackEffect, laserTrackPos.x, 0, laserTrackPos.z);
}