#pragma once
#include <string>
#include "DamageObject.h"
#include "EffectManager.h"
class LaserCollider;
class ObjectObserver;
/// <summary>
/// 回転レーザー
/// </summary>
class RotatingLaser :public DamageObject
{
public:
    /// <summary>
    /// レーザーのエフェクトを読み込み位置を引数のオブジェクトから出す
    /// </summary>
    /// <param name="setObserver">発射オブジェクトの位置等を通達してもらう</param>
    RotatingLaser(std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// エフェクトと当たり判定の削除
    /// </summary>
    ~RotatingLaser()override;
    /// <summary>
    /// レーザーを回転させる　発射しているオブジェクトの位置を追従する
    /// </summary>
    void Update();
private:
    /// <summary>
    /// レーザーのy軸回転
    /// </summary>
    void YRotate();
    /// <summary>
    /// レーザー跡を出す
    /// </summary>
    void SetLaserTrack();
    //レーザーの跡の位置
    VECTOR laserTrackPos = {};
    //線状当たり判定
    LaserCollider* collider;
    //エフェクトハンドル
    int laserEffect = -1;
    //焼き後
    int trackEffect = -1;
    //エフェクトの回転角（ラジアン）
    float effectRota;
    //回転速度
    static const float rotaSpeed;
    //回転半径
    static const float rotateRadius;
};