#pragma once
#include <list>
#include "ActorController.h"
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// 収集アイテムの操作
/// </summary>
class CollectItemController final : public ActorController
{
public:
    /// <summary>
    /// コインを予めNewして最大枚数を保存
    /// </summary>
    CollectItemController();
    /// <summary>
    /// actorListの先頭の収集アイテムだけ更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 収集アイテムの描画
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const override;
    /// <summary>
    /// ゲームが始まる前の処理
    /// </summary>
    void PrepareGame()override;
    /// <summary>
    /// 引数と収集アイテムの距離
    /// </summary>
    /// <param name="pos">収集アイテムとの距離を調べたい位置</param>
    /// <returns>引数と収集アイテムの距離ベクトル</returns>
    VECTOR GetItemBetween(VECTOR pos)const;
    /// <summary>
    /// 最初にステージに配置される枚数
    /// </summary>
    /// <returns>ステージに配置された最大数</returns>
    int GetTotalNum()const;
    /// <summary>
    /// アイテムの残り枚数
    /// </summary>
    /// <returns>プレイヤーに取られると減る</returns>
    int GetRemainingNum()const;
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
    //収集アイテムの最大数
    int totalCollectNum;
    //今の収集アイテムが何番目か
    int collectCount;
    //所得されたアイテムの数
    int remainingCollectNum;
    //今あるオブジェクトが取られたか
    bool isCollectLastOne;
    /// 現在動いている収集アイテムの位置
    VECTOR nowActiveCollectItemPos;
};
