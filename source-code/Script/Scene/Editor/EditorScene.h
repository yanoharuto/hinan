#pragma once
#include <iostream>
#include <memory>
#include "SceneBase.h"
class StageDataEditor;
class StageObjectController;
class StageTimeLimitEditor;
class EditorMenu;
class CameraObserver;
class EditorDrawModelManager;
class EditManual;
class EditorEffect;
class EditorCamera;
class EditorObject;
class EditorInput;
class MouseInput;
class EditorUI;
/// <summary>
/// 編集シーンクラス
/// </summary>
class EditorScene final : public SceneBase
{
public:
    /// <summary>
    /// メニュー画面やカメラ、編集クラスなどを確保
    /// </summary>
    EditorScene();
    /// <summary>
    /// コンストラクタで確保した物を開放
    /// </summary>
    ~EditorScene()override;
    /// <summary>
    /// メニューとEditorの更新
    /// </summary>
    /// <returns>タイトルに戻ったりゲームを終了したりEditorを再読み込みしたりする</returns>
    SceneType Update()override;
    /// <summary>
    /// メニュー画面とEditorの描画
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// オブジェクトの移動処理準備
    /// </summary>
    void MoveObject();
    /// <summary>
    /// オブジェクトの回転処理準備
    /// </summary>
    void RotateObject();
    /// <summary>
    /// オブジェクトの削除
    /// </summary>
    void DeleteObject();
    /// <summary>
    /// オブジェクトの配置
    /// </summary>
    void PutObject();
    /// <summary>
    /// 編集フェーズを変更
    /// </summary>
    void ChangeFase();
    /// <summary>
    /// タイムリミットを変更
    /// </summary>
    void ChangeTimeLimit();
    /// <summary>
    /// カメラの距離を変更
    /// </summary>
    void ScalingCameraBetween();
    /// <summary>
    /// 編集段階を戻す
    /// </summary>
    void StepBackEditState();
    /// <summary>
    /// なにも押されていない時
    /// </summary>
    void FreeButtonUpdate();
    /// <summary>
    /// オブジェクトを選択したとき
    /// </summary>
    void SelectObject();
    /// <summary>
    /// 編集を一つ前から一つ先にやり直す
    /// </summary>
    void StepEditState();
    //関数ポインタ
    void (EditorScene::* EditFunc[12])() = {
        &EditorScene::MoveObject,&EditorScene::RotateObject,& EditorScene::DeleteObject,
        &EditorScene::PutObject,&EditorScene::ChangeFase,&EditorScene::ChangeTimeLimit,
        & EditorScene::ScalingCameraBetween,& EditorScene::StepBackEditState,& EditorScene::FreeButtonUpdate,& EditorScene::SelectObject,& EditorScene::StepEditState
    };
    //メニュー
    std::unique_ptr<EditorMenu> menu;
    //編集物の種類を変更する
    std::unique_ptr<EditorDrawModelManager> drawManager;
    //編集操作説明
    std::unique_ptr<EditManual> manual;
    //編集時に出てくるエフェクトの更新役
    std::unique_ptr <EditorEffect> editorEffect;
    //マウスで移動する時に使う
    std::shared_ptr<MouseInput> mouse;
    //カメラ
    std::shared_ptr<EditorCamera> camera;
    //カメラの向きを編集オブジェクトに伝えるクラス
    std::shared_ptr<CameraObserver> cameraObserver;
    //ステージの端
    std::unique_ptr<StageObjectController> stage;
    //現在編集している物
    std::shared_ptr<StageDataEditor> editor;
    //現在編集中のオブジェクト
    std::unique_ptr<EditorObject> editObject;
    //UI
    std::shared_ptr<EditorUI> ui;
    //時間の変更
    std::shared_ptr<StageTimeLimitEditor> timeEditor;
    //編集中の入力を管理
    std::shared_ptr<EditorInput> input;
    //再編集中か
    bool isReEdit = false;
    //回転モード中
    bool isRotate = false;
    //移動
    bool isMove = false;
};