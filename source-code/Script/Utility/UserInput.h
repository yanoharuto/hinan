#pragma once
#include "DxLib.h"
//入力の種類
constexpr int KEY_INPUT_KIND_NUM = 15;
//レバーの値の幅
constexpr int LEVER_VALUE = 12767;
//マウスのキーの種類
constexpr int EDIT_KEY_KIND = 5;
/// <summary>
/// ユーザーが入力した情報
/// </summary>
class UserInput
{
public:

    /// <summary>
    /// 入力したキーがどれか分かるように準備
    /// </summary>
    UserInput();
    ~UserInput() {};
    /// <summary>
    /// ボタンの入力状況
    /// </summary>
    enum class InputState
    {
        //何もしていない
        Free,
        //入力
        Push,
        //ずっと入力
        Hold,
        //離した
        Detach
    };
    /// <summary>
    /// ボタンの情報
    /// </summary>
    enum class KeyInputKind
    {
        //上入力
        Up = 0,
        //下入力
        Down = 1,
        //左
        Left = 2,
        //右
        Right = 3,
        //スペースキー
        Space = 4,
        //エスケープキー
        EscapeKey = 5,
        //Wキー
        WKey = 6,
        //Dキー
        DKey = 7,
        //Sキー
        SKey = 8,
        //Aキー
        AKey = 9,
        //マウスの左
        MouseLeft = 10,
        //マウスの右
        MouseRight = 11,
        //コントロールキー
        CtrKey = 12,
        //Zキー
        ZKey = 13,
        //Yキー
        YKey = 14
    };

    /// <summary>
    /// 入力状況更新
    /// </summary>
    void Update();
    /// <summary>
    /// ボタンの入力情報
    /// </summary>
    /// <param name="inputKind"></param>
    /// <returns></returns>
    static UserInput::InputState GetInputState(KeyInputKind inputKind);
    /// <summary>
    /// ゲームパッドで遊んでいるか
    /// </summary>
    /// <returns>遊んでいたらTrue</returns>
    static bool IsInputPad() { return isInputPad; };
private:
    /// <summary>
    /// ボタンの入力更新
    /// </summary>
    /// <param name="_Input">入力状況</param>    
    /// <param name="_Button">更新したいボタン</param>
    void UpdateButton(bool inputJudge,InputState* _Button);
    /// <summary>
    /// 編集で使うボタンの更新
    /// </summary>
    /// <param name="code"></param>
    void UpdateButton(KeyInputKind code);
    /// <summary>
    /// ゲームパッドの入力更新
    /// </summary>
    void UpdateGamePadButton();
    //ボタンの情報
    static InputState keyInputState[KEY_INPUT_KIND_NUM];
    //パッドの情報
    static XINPUT_STATE xInput;
    //Aボタンの割り当て番号
    const int aButtonNum = 12;
    //Bボタンの割り当て番号
    const int bButtonNum = 13;
    //ゲームパッドで入力するか
    static bool isInputPad;
    //対応しているボタンの一覧
    const int keyInputCode[KEY_INPUT_KIND_NUM] = { PAD_INPUT_UP ,PAD_INPUT_DOWN ,PAD_INPUT_LEFT ,PAD_INPUT_RIGHT ,PAD_INPUT_10 ,PAD_INPUT_9 ,PAD_INPUT_8 ,PAD_INPUT_6 ,PAD_INPUT_5,PAD_INPUT_4,MOUSE_INPUT_LEFT, MOUSE_INPUT_RIGHT,KEY_INPUT_LCONTROL,KEY_INPUT_Z,KEY_INPUT_Y };
};