#pragma once
#include "ConflictProcessor.h"
class PlayerCar;
class PlayerObserver;
/// <summary>
/// プレイヤーの衝突処理実行役
/// </summary>
class PlayerConflictProcessor : public ConflictProcessor
{
public:
    /// <summary>
    /// プレイヤーの衝突処理実行役
    /// </summary>
    PlayerConflictProcessor(std::shared_ptr<PlayerCar>& car, std::shared_ptr<PlayerObserver>& observer);
    /// <summary>
    /// 衝突結果実行役
    /// </summary>
    /// <param name="resultInfo">衝突結果</param>
    void OnConflict(CollisionResultInfo resultInfo)override;
private:
    std::shared_ptr<PlayerObserver> observer;
};