#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "FadeInFadeOut.h"
#include "UserInput.h"
#include "StageSelect.h"
#include "SpaceKeyUI.h"
#include "TitleObject.h"
#include "Timer.h"
#include "GameScreen.h"
#include "UIDrawer.h"
#include "TitleRanking.h"

/// <summary>
/// 車とかフェードインフェードアウトクラスの確保
/// </summary>
TitleScene::TitleScene()
    :SceneBase(SceneType::title)
{
    //ステージ選択
    stageSelect = std::make_unique<StageSelect>();
    //UIの所得
    spaceKeyUI = std::make_unique<FlashUI>(UIKind::titlePressSpaceKey);
    titleObject = std::make_unique <TitleObject>();
    titleScore = std::make_unique<TitleRanking>();
    titleLogoUIData = UIManager::CreateUIData(UIKind::tilteLogo);
    //音を所得
    SoundPlayer::LoadAndInitSound(SoundKind::titleBGM);
    SoundPlayer::LoadAndInitSound(SoundKind::sceneNextSE);
}
/// <summary>
/// デストラクタ 
/// </summary>
TitleScene::~TitleScene()
{
    SAFE_RESET(stageSelect);
    SAFE_RESET(spaceKeyUI);
    SAFE_RESET(titleObject);
    SAFE_RESET(titleScore);
    UIManager::DeleteUIGraph(&titleLogoUIData);
}
/// <summary>
/// タイトルでの処理
/// </summary>
/// <returns>ゲーム終了かEditorモードかPlayシーンに遷移</returns>
SceneType TitleScene::Update()
{
    //タイトルでの処理//車が勝手に動いたりする
    titleObject->Update();
    //BGM長しっぱ
    if (!SoundPlayer::IsPlaySound(SoundKind::titleBGM) && titleState != TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(SoundKind::titleBGM);
    }
    //状況によってやるべき処理を変更
    switch (titleState)
    {
    case TitleScene::TitleState::waitSpaceKey:
        WaitPressSpaceKey();//スペースキー待ち
        break;
    case TitleScene::TitleState::stageSelect:
        SelectStageProcess();//ステージ選択
        break;
    case TitleScene::TitleState::processEnd:
        SoundPlayer::StopSound(SoundKind::titleBGM);
        return stageSelect->IsEditStage() ? SceneType::editor : SceneType::play;//処理終了
        break;
    default:
        break;
    }

    //エスケープキーを押したら終了
    if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
    {
        return SceneType::escape;
    }
    return nowSceneType;
}
/// <summary>
/// ステージ選択やスコアのランキング、後ろで走る車を描画
/// </summary>
void TitleScene::Draw() const
{
    //車やステージを描画
    titleObject->Draw();
    //タイトルロゴの描画
    UIDrawer::DrawRotaUI(titleLogoUIData, 0, 0, true);

    if (titleState == TitleState::waitSpaceKey)
    {
        spaceKeyUI->Draw();//スペースキー待ちUI
    }
    else
    {
        stageSelect->Draw();//ステージ選択UI
        titleScore->Draw();
    }
    //描画内容保存
    screen->ScreenUpdate();
}
/// <summary>
/// スペースキーを押したらtitleStateを変更
/// </summary>
/// <param name="changedState">変更先の状態</param>
void TitleScene::OnPressSpaceKeyProcess(TitleState changedState)
{
    if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
    {
        SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
        titleState = changedState;
    }
}
/// <summary>
/// スペースキーを押すのを待つ
/// </summary>
void TitleScene::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// ステージ選択処理
/// </summary>
void TitleScene::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
