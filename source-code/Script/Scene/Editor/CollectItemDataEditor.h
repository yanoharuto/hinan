#pragma once
#include "StageDataEditor.h"
/// <summary>
/// 収集アイテムの編集クラス
/// </summary>
class CollectItemDataEditor final : public StageDataEditor
{
public:
    /// <summary>
    /// 収集アイテムの編集クラス
    /// </summary>
    CollectItemDataEditor();
    /// <summary>
    ///  親クラスと同じ更新と収集アイテムの数を更新する
    /// </summary>
    void Update(std::weak_ptr<CameraObserver> cameraObserever)override;
    /// <summary>
    /// 編集中や編集し終えたオブジェクトの描画
    /// </summary>
    void Draw()const override;
private:
    //今何個目の収集アイテムなのかの位置
    const int drawCollectNumY = 200;
    //今　何番目のミッションかの位置
    const int drawEditedCollectNumY = 0;
    //読み込む配置情報の書いてあるファイルのパス
    static const std::string loadFileName;
};

