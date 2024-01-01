#include "UserInput.h"
#include "Utility.h"
//入力情報
UserInput::InputState UserInput::keyInputState[KEY_INPUT_KIND_NUM];
//パッドの情報
XINPUT_STATE UserInput::xInput;
//ゲームパッドで入力するか
bool UserInput::isInputPad;
/// <summary>
/// 入力したキーがどれか分かるように準備
/// </summary>
UserInput::UserInput()
{
    //ゲームパッド入力ならTrue
    isInputPad = GetJoypadNum() != 0;
}
/// <summary>
/// 入力状況更新
/// </summary>
void UserInput::Update()
{
    if (isInputPad)//パッド操作
    {
        UpdateGamePadButton();
    }
    else//キーボード操作
    {
        //現在入力されたボタンを所得
        int inputKey = GetJoypadInputState(DX_INPUT_KEY);
        for (int i = 0; i < KEY_INPUT_KIND_NUM - EDIT_KEY_KIND; i++)
        {
            UpdateButton(inputKey & keyInputCode[i], &keyInputState[i]);
        }
    }
    //マウス入力
    int inputKey = GetMouseInput();
    UpdateButton(inputKey & keyInputCode[CAST_I(KeyInputKind::MouseLeft)], &keyInputState[CAST_I(KeyInputKind::MouseLeft)]);
    UpdateButton(inputKey & keyInputCode[CAST_I(KeyInputKind::MouseRight)], &keyInputState[CAST_I(KeyInputKind::MouseRight)]);
    UpdateButton(KeyInputKind::CtrKey);
    UpdateButton(KeyInputKind::ZKey);
    UpdateButton(KeyInputKind::YKey);
    //ゲームパッド入力ならTrue
    isInputPad = GetJoypadNum() != 0;
}

/// <summary>
/// ボタンの入力情報
/// </summary>
/// <param name="inputKind"></param>
/// <returns></returns>
UserInput::InputState UserInput::GetInputState(KeyInputKind inputKind)
{
    return keyInputState[CAST_I(inputKind)];
}
/// <summary>
/// キーボードボタンの入力更新
/// </summary>
/// <param name="_Input">入力状況</param>    
/// <param name="_Button">更新したいボタン</param>
void UserInput::UpdateButton(bool inputJudge, InputState* _Button)
{    
    //ボタンが押されてたら
    if (inputJudge)
    {
        //今押されたか押しっぱか
        switch (*_Button)
        {
        default:
            *_Button = InputState::Free;
            break;
        case InputState::Free:
            *_Button = InputState::Push;
            break;
        case InputState::Push:
            *_Button = InputState::Hold;
            break;
        case InputState::Hold:
            *_Button = InputState::Hold;
            break;
        }
    }
    else
    {
        //押してから離したか、押されていないか
        switch (*_Button)
        {
        default:
            *_Button = InputState::Free;
            break;
        case InputState::Detach:
            *_Button = InputState::Free;
            break;
        case InputState::Push:
            *_Button = InputState::Detach;
            break;
        case InputState::Hold:
            *_Button = InputState::Detach;
            break;
        }
    }
}
/// <summary>
/// 編集で使うボタンの更新
/// </summary>
/// <param name="code"></param>
void UserInput::UpdateButton(KeyInputKind code)
{
    auto key = keyInputCode[CAST_I(code)];
    UpdateButton(CheckHitKey(key) != 0,&keyInputState[CAST_I(code)]);
}
/// <summary>
/// ゲームパッドの入力更新
/// </summary>
void UserInput::UpdateGamePadButton()
{
    //ゲームパッドの場合のボタン入力を所得
    GetJoypadXInputState(DX_INPUT_KEY_PAD1, &xInput);

    UpdateButton(xInput.ThumbLY > LEVER_VALUE - 1, &keyInputState[CAST_I(KeyInputKind::Up)]);
    UpdateButton(xInput.ThumbLY < -LEVER_VALUE, &keyInputState[CAST_I(KeyInputKind::Down)]);
    UpdateButton(xInput.ThumbLX > LEVER_VALUE - 1, &keyInputState[CAST_I(KeyInputKind::Right)]);
    UpdateButton(xInput.ThumbLX < -LEVER_VALUE, &keyInputState[CAST_I(KeyInputKind::Left)]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_B] == 1, &keyInputState[CAST_I(KeyInputKind::Space)]);
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_BACK] == 1, &keyInputState[CAST_I(KeyInputKind::EscapeKey)]);   
    UpdateButton(xInput.Buttons[XINPUT_BUTTON_X] == 1, &keyInputState[CAST_I(KeyInputKind::AKey)]);   
}
