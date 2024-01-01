#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"
#include "ObjectObserver.h"

/// <summary>
/// プレイヤーを中心に近くにアイテムがあるか調べさせる
/// </summary>
class MiniMap
{
public:
    /// <summary>
    /// 収集アイテムとかを描画するための奴
    /// </summary>
    MiniMap(std::weak_ptr<ObjectObserver> player);
    /// <summary>
    /// 描画するマーカーを消去
    /// </summary>
    ~MiniMap();
    /// <summary>
    /// ミニマップに表示するマーカーの位置を更新
    /// </summary>
    void Update();
    /// <summary>
    /// マップに表示する点とレーダーの枠
    /// </summary>
    void Draw()const;
    /// <summary>
    /// マップに反映させたいアイテムの追加
    /// </summary>
    /// <param name="obserber"></param>
    static void AddMarker(std::unique_ptr<ObjectObserver> obserber);
private:
    /// <summary>
    /// 描画するマーカーのポジション
    /// </summary>
    /// <param name="subjectPos">書きたいマーカーのオブジェクトのポジション</param>
    void UpdateDrawPosList(VECTOR subjectPos);
    /// <summary>
    /// ミニマップの大きさに変換する
    /// </summary>
    /// <param name="between">中央のアイテムからの距離</param>
    /// <returns></returns>
    VECTOR ConvertPosition(VECTOR between);
    //プレイヤーのマーカーの色
    const unsigned int playerColor = GetColor(180,200,0);
    //収集物の色
    const unsigned int coinColor = GetColor(0,115,255);
    //北の印の色
    const unsigned int northColor = GetColor(255,0,0);
    //自機のIconの大きさ
    static const int iconSize = 5;
    //ミニマップの画像の幅
    int mapGraphWidth;
    //収集物の位置の縮尺
    float betweenSize = 0.25f;
    //ミニマップ
    static UIData miniMapUIData;
    //マップの中心軸にする
    std::weak_ptr<ObjectObserver> playerObserver;
    //マーカーの位置を更新するためのリスト
    static std::list<std::unique_ptr<ObjectObserver>> markerObserverList;
    //描画位置のリスト
    std::list<VECTOR> drawPosList;
    //北の位置
    VECTOR northPos;
};