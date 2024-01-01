#pragma once
#include "SceneBase.h"
#include <string>
#include <iostream>
#include <memory>
//四つに分けて処理を行う

#define PlaySceneProcess 3
class Menu;
class PostGameEndStagingProcess;
class PrePlayGameProcess;
class PlayGameProcess;
class ActorControllerManager;
class GameCamera;
class ShadowMap;
class ConflictManager;
class GameScreen;
class PlayerObserver;
class CollectItemObserver;
class CameraObserver;
/// <summary>
/// ゲームを遊ぶシーン
/// </summary>
class PlayScene final: public SceneBase
{
public:
    /// <summary>
    /// メニュー画面とゲームの流れの確保と音をロード
    /// </summary>
    PlayScene();
    /// <summary>
    /// メニューとゲームの開放
    /// </summary>
    ~PlayScene() override;
    /// <summary>
    /// ゲームを遊ぶ
    /// </summary>
    /// <returns></returns>
    SceneType Update() override;
    /// <summary>
    /// メニューを開いている時と遊んでいるときで処理が違う
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// エフェクトの更新処理
    /// </summary>
    void UpdateEffect();
    /// <summary>
    /// カウントダウン終了までの処理
    /// </summary>
    void UpdatePreStartCountdownEnd();
    /// <summary>
    /// 遊んでいるときの処理
    /// </summary>
    void UpdatePlayGame();
    /// <summary>
    /// 全部アイテムを回収した後の処理
    /// </summary>
    void UpdatePostGameEndProcess();
    /// <summary>
    /// カウントダウン終了までの描画
    /// </summary>
    void DrawPreStartCountdownEnd()const;
    /// <summary>
    /// 遊んでいるときの描画
    /// </summary>
    void DrawPlayGame()const;
    /// <summary>
    /// 全部アイテムを回収した後の処理
    /// </summary>
    void DrawPostGameEndProcess()const;
    //ゲーム中断機能
    std::unique_ptr<Menu> menu;
    //ゴール後の処理
    std::unique_ptr<PostGameEndStagingProcess> postGameEndProcess;
    //遊んでいるときの処理
    std::unique_ptr<PlayGameProcess> playGameProcess;
    //レース前の処理
    std::unique_ptr <PrePlayGameProcess> gamePrevProcess;
    //シャドウマップ
    std::unique_ptr<ShadowMap> shadowMap;
    //衝突判判定クラス
    std::unique_ptr<ConflictManager> conflictManager;
    //各オブジェクトの管理役
    std::shared_ptr<ActorControllerManager> controllerManager;
    //カメラの向きを伝えるクラス
    std::shared_ptr<CameraObserver>  cameraObserver;
    //カメラ
    std::shared_ptr<GameCamera> camera;
    //描画状況を保存する
    std::unique_ptr<GameScreen> screen;
    /// <summary>
    /// プレイシーンの段階
    /// </summary>
    enum class PlaySceneProgress
    {
        start,//最初の処理
        game,//遊んでいるときの処理
        postGameEnd,//ゴールし終わった時の処理
    };
    //今何の処理を行うか決める変数
    PlaySceneProgress nowProgress;
    //各シーンの処理の関数ポインタ
    void (PlayScene::* UpdateFunc[PlaySceneProcess])() = { &PlayScene::UpdatePreStartCountdownEnd ,&PlayScene::UpdatePlayGame ,&PlayScene::UpdatePostGameEndProcess };
    //描画処理
    void (PlayScene::* DrawFunc[PlaySceneProcess])()const = { &PlayScene::DrawPreStartCountdownEnd ,&PlayScene::DrawPlayGame ,&PlayScene::DrawPostGameEndProcess };
};