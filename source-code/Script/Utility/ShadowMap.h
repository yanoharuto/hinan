#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"

class ObjectObserver;

/// <summary>
/// 影を描画するクラス
/// </summary>
class ShadowMap final
{
public:
    /// <summary>
    /// プレイヤーを中心に影を描画できるようにする
    /// </summary>
    /// <param name="player">プレイヤーの位置を伝えるクラス</param>
    ShadowMap(std::weak_ptr<ObjectObserver> player);
    /// <summary>
    /// プレイヤーのオブザーバーのリセットとシャドウマップの削除
    /// </summary>
    ~ShadowMap();
    /// <summary>
    /// 影の描画範囲の変更
    /// </summary>
    void SetShadowMapArea();
    /// <summary>
    /// これから描画する影の準備
    /// </summary>
    void SetUpDrawShadow();
    /// <summary>
    /// 影を描画するの終了
    /// </summary>
    void EndDrawShadow();
    /// <summary>
    /// 書き込んだシャドウマップを使う
    /// </summary>
    void Use();
private:
    //シャドウマップの最小範囲を設定
    VECTOR DrawAreaMinPos = VGet(-300.0f, -1.0f, -300.0f);
    //シャドウマップの最大範囲を設定
    VECTOR DrawAreaMaxPos = VGet(300.0f, 700.0f, 300.0f);
    //シャドウマップ作製
    int shadowMap = MakeShadowMap(2048, 2048);
    //こいつを軸に影を作る範囲を決める
     std::weak_ptr<ObjectObserver> playerObserber;
};

