#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorMenu.h"
#include "StageTimeLimitEditor.h"
#include "EditorManager.h"
#include "UserInput.h"
#include "EditorCamera.h"
#include "EditorEffect.h"
#include "EditManual.h"
#include "CameraObserver.h"
#include "StageObjectController.h"
#include "StageDataEditor.h"
#include "MouseInput.h"
#include "EditorInput.h"
#include "EffekseerForDXLib.h"
#include "EditorObject.h"
#include "EditorUI.h"
/// <summary>
/// メニュー画面やカメラ、編集クラスなどを確保
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::editor)
{
    SetMouseDispFlag(true);
    //カメラ
    camera = std::make_shared<EditorCamera>();
    cameraObserver = std::make_unique<CameraObserver>(camera);
    //編集オブジェクトの種類を変更するクラス
    drawManager = std::make_unique<EditorDrawModelManager>();
    //メニュー画面
    menu = std::make_unique< EditorMenu>();
    //操作説明説明
    manual = std::make_unique< EditManual>();
    //エフェクト
    editorEffect = std::make_unique< EditorEffect>();
    //背景
    stage = std::make_unique< StageObjectController>();
    //現在の編集クラス
    editor = std::make_shared<StageDataEditor>();
    //編集オブジェクト
    editObject = std::make_unique< EditorObject>();
    //編集中の入力を調べる
    input = std::make_shared<EditorInput>();
    //マウス
    mouse = std::make_shared<MouseInput>();
    //制限時間の変更
    timeEditor = std::make_shared<StageTimeLimitEditor>();
    //UI
    ui = std::make_shared< EditorUI>();
    //移動フラグ
    isMove = true;
}
/// <summary>
/// コンストラクタで確保した物を開放
/// </summary>
EditorScene::~EditorScene()
{
    SAFE_RESET(menu);
    SAFE_RESET(ui);
    SAFE_RESET(drawManager);
    camera.reset();
    SAFE_RESET(manual);
    SAFE_RESET(editorEffect);
    SetMouseDispFlag(false);
    SAFE_RESET(stage);
    mouse.reset();
}
/// <summary>
/// メニューとEditorの更新
/// </summary>
/// <returns>タイトルに戻ったりゲームを終了したりEditorを再読み込みしたりする</returns>
SceneType EditorScene::Update()
{
    mouse->UpdateMousePosition();
    menu->Update(mouse);//メニュー画面の更新
    auto returnType = menu->GetMenuState();
    //タイトルシーンを選択したなら戻る
    switch (returnType)
    {
    case EditorMenu::EditMenuOptions::timeLimitChange:
        ChangeTimeLimit();
        break;
    case EditorMenu::EditMenuOptions::returnTitle:
        return SceneType::title;
        break;
    default:
        break;
    }
    //メニュー画面開いてなかったら
    if (!menu->IsMenuOpen())
    {
        std::weak_ptr<EditorUI> weakUI = ui;
        std::weak_ptr<MouseInput> weakMouse = mouse;
        //入力状況を更新
        input->Update(weakMouse,weakUI);
        //入力によって挙動を変える
        auto inputMode = input->GetEditMode();
        if (inputMode == EditorInput::EditMode::PlayEditStage)
        {
            return SceneType::play;
        }
        (this->*EditFunc[CAST_I(inputMode)])();
        //カメラの位置を変える
        camera->UpdatePosition(weakMouse);
    }
    return nowSceneType;
}
/// <summary>
/// メニュー画面とEditorの描画
/// </summary>
void EditorScene::Draw() const
{
    //メニュー画面を開いていたら
    if (menu->IsMenuOpen())
    {
        menu->Draw(timeEditor);
    }
    else
    {
        std::weak_ptr<CameraObserver> weakCamera = cameraObserver;
        //ステージに配置されている物
        stage->Draw(weakCamera);
        //編集中、編集済みオブジェクトを描画
        drawManager->Draw(editObject->GetPlacementData());
        drawManager->Draw(editor->GetNowFaseEditEndPlacementData());
        ui->Draw(editor);
        //エフェクト更新
        Effekseer_Sync3DSetting();
        UpdateEffekseer3D();
        DrawEffekseer3D();
    }
}
/// <summary>
/// オブジェクトの移動処理準備
/// </summary>
void EditorScene::MoveObject()
{
    //移動出来るようにする
    isMove = true;
    isRotate = false;
}
/// <summary>
/// オブジェクトの回転処理準備
/// </summary>
void EditorScene::RotateObject()
{
    //回転出来るようにする
    isRotate = true;
    isMove = false;
}
/// <summary>
/// オブジェクトの削除
/// </summary>
void EditorScene::DeleteObject()
{
    if (editor->IsReEdit())
    {
        editor->OnEraceEditData();
        isReEdit = false;
    }
}
/// <summary>
/// オブジェクトの配置
/// </summary>
void EditorScene::PutObject()
{
    editor->OnPut(editObject->GetPlacementData());
}
/// <summary>
/// 編集フェーズを変更
/// </summary>
void EditorScene::ChangeFase()
{
    //今編集しているオブジェクトの出るタイミングを変更する
    editor->ChangeAppearFase(mouse);
}
/// <summary>
/// タイムリミットを変更
/// </summary>
void EditorScene::ChangeTimeLimit()
{
    timeEditor->ChangeTimeLimit(mouse);
}
/// <summary>
/// カメラの距離を変更
/// </summary>
void EditorScene::ScalingCameraBetween()
{
    std::weak_ptr<MouseInput> weakMouse = mouse;
    camera->UpdateTargetPosition(weakMouse);
}

/// <summary>
/// 編集段階を戻す
/// </summary>
void EditorScene::StepBackEditState()
{
    editor->OnBackStepPrevState();
}
/// <summary>
/// なにも押されていない時
/// </summary>
void EditorScene::FreeButtonUpdate()
{
    if (isMove)
    {
        editObject->Move(cameraObserver, mouse);
    }
    else if(isRotate)
    {
        editObject->Rotate(cameraObserver, mouse);
    }
    //再編集中は移動と回転と消去と再配置以外できない
    if(!isReEdit)
    {
        //種類の変更
        editObject->UpdateKind(mouse);
        //重なっている物を調べる
        editor->UpdateEditTarget(editObject->GetPlacementData());
        //編集対象に触れていたらエフェクトを出す
        if (editor->IsReEdit())
        {
            editorEffect->Start();
            editorEffect->UpdatePositionAndDirection(editor->GetEditData());
        }
        else
        {
            editorEffect->Stop();
        }
    }
}
/// <summary>
/// オブジェクトを選択したとき
/// </summary>
void EditorScene::SelectObject()
{
    //isReEditがfalseなら再編集する対象を所得
    if (editor->IsReEdit() && !isReEdit)
    {
        //再編集
        editObject->SetArrangementData(editor->GetEditData());
        isReEdit = true;
    }
    else
    {
        PutObject();
        isReEdit = false;
    }
}
/// <summary>
/// 編集を一つ前から一つ先にやり直す
/// </summary>
void EditorScene::StepEditState()
{
    editor->OnStepState();
}