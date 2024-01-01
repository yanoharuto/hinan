#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
#include "DxLib.h"
class TitleCar;
class Timer;
class ObjectObserver;
/// <summary>
/// タイトルで走らせる
/// </summary>
class TitlteCarController : public ActorController
{
public:
    /// <summary>
    /// タイトルで走らせる車
    /// </summary>
    /// <param name="setPos">初期位置</param>
    /// <param name="setDir">初期向き</param>
    /// <param name="initTimer">定期的に初期位置に戻すためのタイマー</param>
    TitlteCarController(VECTOR setPos, VECTOR setDir, std::shared_ptr<Timer> initTimer);
    /// <summary>
    /// 走っている車と描画役の開放
    /// </summary>
    ~TitlteCarController()override;
    /// <summary>
    /// 車の移動
    /// </summary>
    void Update()override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const override;
    /// <summary>
    /// 車の位置などをカメラなどに渡せるようにする
    /// </summary>
    /// <returns>車情報伝達役</returns>
    std::shared_ptr<ObjectObserver> CreateCarObserver();
private:
    //タイトルで走る車
    std::shared_ptr<TitleCar> titleCar;
    //車の位置などを伝える
    std::shared_ptr<ObjectObserver> observer;
};