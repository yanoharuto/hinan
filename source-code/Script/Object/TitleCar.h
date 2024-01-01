#pragma once
#include <iostream>
#include <memory>
#include "Car.h"
class Timer;
/// <summary>
/// タイトル画面で走らせる車
/// </summary>
class TitleCar : public Car
{
public:
    /// <summary>
    /// 位置などの初期化とエフェクトのロード
    /// </summary>
    /// <param name="setPos">初期位置</param>
    /// <param name="setDir">初期向き</param>
    /// <param name="initTimer">定期的に初期位置に戻すためのタイマー</param>
    TitleCar(VECTOR setPos,VECTOR setDir ,std::weak_ptr<Timer> setInitTimer);
    /// <summary>
    /// タイヤとエフェクト解放
    /// </summary>
    ~TitleCar()override;

    /// <summary>
    /// 一定方向に走る
    /// </summary>
    void Update()override;
private:
    /// <summary>
    /// エフェクトの更新
    /// </summary>
    void EffectUpdate();
    /// <summary>
    /// 走る速さベクトルの所得
    /// </summary>
    /// <returns></returns>
    void UpdateAccelPower()override;
    //走るエフェクト
    int runEffect = -1;
    //初期位置
    VECTOR firstPos;
    //初期向き
    VECTOR firstDir;
    //加速度
    const float setAcceleSpeed = 2;
    //最大値
    const float setMaxSpeed = 5;
    //初期化するのに必要なタイマー
    std::weak_ptr<Timer> initTimer;
};