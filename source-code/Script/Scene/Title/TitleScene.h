#pragma once
#include <iostream>
#include <memory>
#include "SceneBase.h"
#include "UIManager.h"
class GameScreen;
class StageSelect;
class FlashUI;
class TitleCamera;
class TitleObject;
class TitleRanking;
class CameraObserver;
/// <summary>
/// タイトル
/// </summary>
class TitleScene final : public SceneBase
{
public:
    /// <summary>
    /// TitleSceneFlowを確保
    /// </summary>
    TitleScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~TitleScene()override;
    /// <summary>
    /// タイトルでの処理
    /// </summary>
    /// <returns>ゲーム終了かEditorモードかPlayシーンに遷移</returns>
    SceneType Update()override;
    /// <summary>
    /// ステージ選択やスコアのランキング、後ろで走る車を描画
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// タイトルの状態
    /// </summary>
    enum class TitleState
    {
        //スペースキーを押す前の状態
        waitSpaceKey,
        //ステージの選択
        stageSelect,
        //タイトルシーンでの処理終了
        processEnd
    };
    /// <summary>
    /// スペースキーを押したらtitleStateを変更
    /// </summary>
    /// <param name="c
    /// edState">タイトルシーンを変更する先</param>
    void OnPressSpaceKeyProcess(TitleState changedState);
    /// <summary>
    /// スペースキーを押すのを待つ
    /// </summary>
    void WaitPressSpaceKey();
    /// <summary>
    /// ステージ選択処理
    /// </summary>
    void SelectStageProcess();
    //ステージの情報
    std::unique_ptr<StageSelect> stageSelect;
    //スペースキーを押してもらうためのUI
    std::unique_ptr<FlashUI> spaceKeyUI;
    //タイトルの後ろで走らせる
    std::unique_ptr<TitleObject> titleObject;
    //描画した状態を保存する
    std::unique_ptr<GameScreen> screen;
    //タイトル画面に表示するハイスコア
    std::unique_ptr<TitleRanking> titleScore;
    //タイトルロゴ
    UIData titleLogoUIData;
    //タイトルの状態
    TitleState titleState;
};