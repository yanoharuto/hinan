#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class CollectItemObserver;
class PlayerObserver;
/// <summary>
/// 収集アイテムの方向を記すエフェクトを出す
/// </summary>
class CollectCompass
{
public:
    /// <summary>
    /// playerObserverとcollectControllerの所得
    /// </summary>
    /// <param name="player">プレイヤーの位置や向きが分かるやつ</param>
    /// <param name="collectItemObserver">収集アイテムの距離などが分かるやつ</param>
    CollectCompass(std::weak_ptr<PlayerObserver> player,std::shared_ptr<CollectItemObserver> collectItemObserver);
    /// <summary>
    /// エフェクト終了
    /// </summary>
    ~CollectCompass();
    /// <summary>
    /// エフェクトの位置と向きを設定
    /// </summary>
    void Update();
private:
    //プレイヤーの位置や向きを取ってくる
    std::weak_ptr<PlayerObserver> playerObserver;
    //収集アイテムの管理クラス
    std::weak_ptr<CollectItemObserver> collectObserver;
    //エフェクトハンドル
    int compassEffect = -1;
    //エフェクトのY座標
    const float addYPos = 13;
};