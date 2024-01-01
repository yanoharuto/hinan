#pragma once
#include "UIManager.h"

/// <summary>
/// タイトル画面でステージ選ぶ時に使う
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// ステージ選択UIの読み込み
    /// 一番最初のステージに変更
    /// </summary>
    StageSelect();
    /// <summary>
    /// UIの削除
    /// </summary>
    ~StageSelect();
    /// <summary>
    /// 十字キーで遊ぶステージ変更
    /// </summary>
    void Update();
    /// <summary>
    /// 現在選んでいるステージを表示
    /// </summary>
    void Draw()const;
    /// <summary>
    /// ステージの番号所得
    /// </summary>
    /// <returns>今選択しているステージの番号</returns>
    int GetSelectStageNum()const;
    /// <summary>
    /// 編集ステージに移行するかどうか
    /// </summary>
    /// <returns></returns>
    bool IsEditStage()const { return isEditStage; };
private:
    // 編集ステージに移行するかどうか
    bool isEditStage = false;
    //ステージ番号
    int selectStageNum;
    //選択しているステージだけ強調表示
    const float selectSizeCoefficient = 1.4f;
    //選んでいるステージの名前を表示
    UIData stageNameUIData;
    //ステージを決定するときのボタンを表示
    UIData selectButtonUIData;
};
