#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
class CollectItemController;
class PlayerObserver;
/// <summary>
/// 収集アイテムの数等を伝えるクラス
/// </summary>
class CollectItemObserver final
{
public:
    /// <summary>
    /// 管理クラスを所得
    /// </summary>
    /// <param name="collectItemController">収集アイテムの管理クラス</param>
    CollectItemObserver(std::shared_ptr<CollectItemController>& collectItemController);
    /// <summary>
    /// 管理クラスを開放
    /// </summary>
    ~CollectItemObserver();
    /// <summary>
    /// 最初にステージに配置される枚数
    /// </summary>
    /// <returns>ステージに配置された最大数</returns>
    int GetTotalItemNum ()const;
    /// <summary>
    /// 引数と収集アイテムの距離
    /// </summary>
    /// <param name="pos">収集アイテムとの距離を調べたい位置</param>
    /// <returns>引数と収集アイテムの距離ベクトル</returns>
    VECTOR GetItemBetween(VECTOR pos)const;
    /// <summary>
    /// アイテムの残り枚数
    /// </summary>
    /// <returns>プレイヤーに取られると減る</returns>
    int GetRemainingItemNum ()const;
    /// <summary>
    /// 今の収集アイテムが何番目のアイテムか
    /// </summary>
    /// <returns>取られたら増える</returns>
    int GetCollectCount()const;
    /// <summary>
    /// 最後の一つのアイテムが回収されたか
    /// </summary>
    /// <returns>回収されたらTrue</returns>
    bool IsCollectLastOne()const;
private:
    //収集アイテムの数や位置を教えてもらう
    std::shared_ptr<CollectItemController> collectController;
};