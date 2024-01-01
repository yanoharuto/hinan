#include "EditorInput.h"
#include "UserInput.h"
#include "MouseInput.h"
#include "Utility.h"

/// <summary>
/// 編集の入力内容を変更
/// </summary>
EditorInput::EditorInput()
{
    leftMode = EditMode::Free;
    holdMouseX = 0;
    holdMouseY = 0;
    playEditStageUI = UIManager::CreateUIData(UIKind::playEditStage);
}
/// <summary>
/// 左クリックを押しているときは編集処理を変更・決定する
/// </summary>
void EditorInput::Update(std::weak_ptr<MouseInput> input)
{
    auto state = UserInput::GetInputState(UserInput::KeyInputKind::MouseLeft);
    int x = input.lock()->GetMouseX();
    int y = input.lock()->GetMouseY();
    switch (state)
    {
        //配置か削除したならDelete
    case UserInput::InputState::Free:
        if (!isEditObject)
        {
            leftMode = EditMode::Free;
        }
        else//編集中なら移動モードか回転モードに
        {
            leftMode = isRotateMode ? EditMode::Rotate : EditMode::Move;
        }
        break;
        //マウスの位置を更新 オブジェクトを選択もしくは配置
    case UserInput::InputState::Push:
        holdMouseX = x;
        holdMouseY = y;
        leftMode = isEditObject ? leftMode : EditMode::SelectObject;
        //編集したステージを遊ぶボタンをクリックしたら終了
        x = playEditStageUI.width / 2;
        y = playEditStageUI.width / 2;
        if (holdMouseX > playEditStageUI.x - x && holdMouseX < playEditStageUI.x +  x&&
            holdMouseY > playEditStageUI.y - y && holdMouseY < playEditStageUI.y + y)
        {
            leftMode = EditMode::PlayEditStage;
        }
        break;
        //選択肢が出る
    case UserInput::InputState::Hold:
        HoldChangeLeftMode(x, y);
        isLeftHold = true;
        break;
        //編集モードに入ったらisEditObjectがTrueになる
    case UserInput::InputState::Detach:
        isLeftHold = false;
        isRotateMode = leftMode == EditMode::Rotate;
        isEditObject = leftMode != EditMode::Put && leftMode != EditMode::Delete;
        break;
    default:
        break;
    }

    state = UserInput::GetInputState(UserInput::KeyInputKind::MouseRight);
    switch (state)
    {
    case UserInput::InputState::Push:
        holdMouseX = x;
        holdMouseY = y;
        break;
    case UserInput::InputState::Hold:
        isRightHold = true;
        HoldChangeRightMode(x,y);
        break;
    default:
        isRightHold = false;
        break;
    }
}
/// <summary>
/// 今何をするべきか返す　
/// </summary>
/// <returns>今何をするべきか返す.左ボタンを長押しならHoldLeftButtonが返る</returns>
EditorInput::EditMode EditorInput::GetEditMode() const
{
    if (isRightHold)
    {
        return rightMode;
    }
    else
    {
        return isLeftHold ? EditMode::HoldButton : leftMode;
    }
}
/// <summary>
/// 操作説明の描画
/// </summary>
void EditorInput::Draw() const
{
    if(isLeftHold)
    {
        switch (leftMode)//左長押し中に左右上下に動かすときの説明文
        {
        case EditMode::Move:
        case EditMode::Rotate:
            if (isRotateMode)//回転モード中は移動モードに切り替わる
            {
                DrawFormat(manual[CAST_I(EditMode::Move)]);
            }
            else
            {
                DrawFormat(manual[CAST_I(EditMode::Rotate)]);
            }
            break;
        case EditMode::BackPrevState:
            DrawFormat(manual[CAST_I(EditMode::BackPrevState)]);
            break;
        case EditMode::Put:
            DrawFormat(manual[CAST_I(EditMode::Put)]);
            break;
        case EditMode::Delete:
            DrawFormat(manual[CAST_I(EditMode::Delete)]);
            break;
        case EditMode::HoldButton:
            if (isRotateMode)//回転モード中は移動モードに切り替わる
            {
                DrawFormat(manual[CAST_I(EditMode::Move)]);
            }
            else
            {
                DrawFormat(manual[CAST_I(EditMode::Rotate)]);
            }
            DrawFormat(manual[CAST_I(EditMode::ChangeFase)]);
            DrawFormat(manual[CAST_I(EditMode::Put)]);
            DrawFormat(manual[CAST_I(EditMode::Delete)]);
            break;
        default:
            break;
        }
    }
    if(isRightHold)
    {
        switch (rightMode)//右長押し中に左右上下に動かすときの説明文
        {
        case EditMode::ChangeTimeLimit:
            DrawFormat(manual[CAST_I(EditMode::ChangeTimeLimit)]);
            break;
        case EditMode::ChangeFase:
            DrawFormat(manual[CAST_I(EditMode::ChangeFase)]);
            break;
        case EditMode::ScalingCamera:
            DrawFormat(manual[CAST_I(EditMode::ScalingCamera)]);
            break;
        case EditMode::HoldButton:
            DrawFormat(manual[CAST_I(EditMode::ChangeTimeLimit)]);
            DrawFormat(manual[CAST_I(EditMode::ChangeFase)]);
            DrawFormat(manual[CAST_I(EditMode::ScalingCamera)]);
            break;
        default:
            break;
        }
    }
    //編集したステージを遊ぶUI
    UIDrawer::DrawRotaUI(playEditStageUI);
}
/// <summary>
/// マウス操作で編集する内容を変える
/// </summary>
void EditorInput::HoldChangeLeftMode(int mouseX, int mouseY)
{
    mouseX -= holdMouseX;
    mouseY -= holdMouseY;
    leftMode = EditMode::HoldButton;
    //入力無し
    //マウスの上下左右で編集内容を変える
    if (abs(mouseX) > abs(mouseY) && abs(mouseX) > INPUT_RANGE)
    {
        if (mouseX < -INPUT_RANGE)//左にマウスをずらすと回転と移動を切り替える
        {
            //回転モードと移動モードを切り替える
            leftMode = isRotateMode ? EditMode::Move : EditMode::Rotate;
        }
        if (mouseX > INPUT_RANGE)//右にずらすとひとつ前の状態に戻す
        {
            leftMode = EditMode::BackPrevState;
        }
    }
    else if (abs(mouseY) > INPUT_RANGE)
    {
        //配置.再配置
        if (mouseY > -INPUT_RANGE)
        {
            leftMode = EditMode::Delete;
        }
        //再編集.再編集中のものを破棄
        else if (mouseY < INPUT_RANGE)
        {
            leftMode = EditMode::Put;
        }
    }
}
/// <summary>
/// 右ボタン長押しで編集する内容を変える
/// </summary>
void EditorInput::HoldChangeRightMode(int mouseX, int mouseY)
{
    mouseX -= holdMouseX;
    mouseY -= holdMouseY;
    rightMode = EditMode::HoldButton;
    //入力無し
    //マウスの上下左右で編集内容を変える
    if (abs(mouseX) > abs(mouseY) && abs(mouseX) > INPUT_RANGE)
    {
        if (mouseX < -INPUT_RANGE)//左にマウスをずらすと回転と移動を切り替える
        {
            //回転モードと移動モードを切り替える
            rightMode = EditMode::ChangeTimeLimit;
        }
        if (mouseX > INPUT_RANGE)//右にずらすと出てくる段階を変更できるようになる
        {
            rightMode = EditMode::ChangeFase;
        }
    }
    else if (abs(mouseY) > INPUT_RANGE)
    {
        //配置.再配置
        if (mouseY > -INPUT_RANGE)
        {
            rightMode = EditMode::ScalingCamera;
        }
    }
}
/// <summary>
/// マウス左ボタンが長押しなら操作説明
/// </summary>
void EditorInput::DrawFormat(UIDrawer::Format format)const
{
    DrawFormatString(format.addX + holdMouseX, format.addY + holdMouseY, formatColor, format.string.c_str());
}