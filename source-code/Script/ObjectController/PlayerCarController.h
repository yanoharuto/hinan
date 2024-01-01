#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
class SphereHitChecker;
class PlayerObserver;
class SoundListener;
class PlayerDrawModel;
class PlayerCar;
/// <summary>
/// プレイヤーの車の管理
/// </summary>
class PlayerCarController final : public ActorController
{
public:
    /// <summary>
    /// プレイヤーの車の初期化
    /// </summary>
    PlayerCarController();
    /// <summary>
    /// 車とLisnerのDelete
    /// </summary>
    ~PlayerCarController();
    /// <summary>
    /// 車の位置とかを渡す
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<PlayerObserver> CreatePlayerObserver() const;
    /// <summary>
    /// 音を聞くために場所を更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever) const override;
private:
    //プレイヤーの車の当たり判定
    std::shared_ptr<SphereHitChecker> collider;
    //操作する車
    std::shared_ptr<PlayerCar> car;
    //描画に使う
    std::unique_ptr<PlayerDrawModel> playerDrawer;
    //音を聞く場所の更新
    std::unique_ptr<SoundListener> listener = nullptr;
    //ダメージを受けるクールタイム
    const float setDamageCoolTime = 0.1f;
    //プレイヤーの情報を共有するためのポインタ
    std::shared_ptr<PlayerObserver> playerObserver;
};