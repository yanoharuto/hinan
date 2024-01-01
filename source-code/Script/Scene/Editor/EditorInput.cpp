#include "EditorInput.h"
#include "UserInput.h"
#include "MouseInput.h"
#include "Utility.h"
#include "EditorUI.h"
/// <summary>
/// 編集の入力内容を変更
/// </summary>
EditorInput::EditorInput()
{
    inputMode = EditMode::Free;
    holdMouseX = 0;
    holdMouseY = 0;
    
}
/// <summary>
/// 左クリックを押しているときは編集処理を変更・決定する
/// </summary>
void EditorInput::Update(std::weak_ptr<MouseInput>& input,std::weak_ptr<EditorUI>& ui)
{
    auto lockUI = ui.lock();
    auto lockInput = input.lock();
    if (lockUI == nullptr || lockInput == nullptr)return;
    //左クリックしたなら
    bool isPushLeft = UserInput::GetInputState(UserInput::KeyInputKind::MouseLeft) == UserInput::InputState::Push;
    inputMode = EditMode::Free;
    int x = lockInput->GetMouseX();
    int y = lockInput->GetMouseY();
    
    switch (lockUI->GetUIOnMouse(x, y))
    {
    case EditorUI::EditUIKind::time://タイムリミットを変更
        inputMode = EditMode::ChangeTimeLimit;
        break;
    case EditorUI::EditUIKind::faseChange://フェーズの変更
        inputMode = EditMode::ChangeFase;
        break;
    case EditorUI::EditUIKind::stagePlay://ステージを遊ぶ
        if (isPushLeft)
        {
            inputMode = EditMode::PlayEditStage;
        }
        break;
    }
    if (inputMode != EditMode::Free) return;//もうすでに何かのUIをクリックしていたら
    //カメラの距離を変更
    if (UserInput::GetInputState(UserInput::KeyInputKind::MouseRight)==UserInput::InputState::Hold)
    {
        inputMode = EditMode::ScalingCameraBetween;
    }
    else if (isPushLeft)//配置する
    {
        inputMode = EditMode::SelectObject;
    }
    //回転させる
    else if (UserInput::GetInputState(UserInput::KeyInputKind::WKey) == UserInput::InputState::Push)
    {
        inputMode = EditMode::Rotate;
    }
    //移動させる
    else if (UserInput::GetInputState(UserInput::KeyInputKind::SKey) == UserInput::InputState::Push)
    {
        inputMode = EditMode::Move;
    }
    //削除する
    else if (UserInput::GetInputState(UserInput::KeyInputKind::DKey) == UserInput::InputState::Push)
    {
        inputMode = EditMode::Delete;
    }
    if (UserInput::GetInputState(UserInput::KeyInputKind::CtrKey) == UserInput::InputState::Hold)
    {
        if (UserInput::GetInputState(UserInput::KeyInputKind::ZKey) == UserInput::InputState::Push)
        {
            inputMode = EditMode::BackEditState;//ひとつ前に戻る
        }
        if (UserInput::GetInputState(UserInput::KeyInputKind::YKey) == UserInput::InputState::Push)
        {
            inputMode = EditMode::StepEditState;//一つ先に戻る
        }
    }
}
/// <summary>
/// 今何をするべきか返す　
/// </summary>
/// <returns>今何をするべきか返す.左ボタンを長押しならHoldLeftButtonが返る</returns>
EditorInput::EditMode EditorInput::GetEditMode() const
{
    return inputMode;
}