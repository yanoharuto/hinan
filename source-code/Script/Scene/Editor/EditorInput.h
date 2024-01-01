#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "UIManager.h"
#include "UIDrawer.h"
//入力するために必要なマウスの運動量
constexpr int INPUT_RANGE = 60;
constexpr int EDIT_MODE_KIND = 12;
class MouseInput;
class EditorUI;
/// <summary>
/// マウスで編集するときに何を入力したか
/// 知らせるクラス
/// </summary>
class EditorInput
{
public:
    /// <summary>
    /// 編集の入力内容を変更
    /// </summary>
    EditorInput();
    /// <summary>
    /// 左クリックを押しているときは編集処理を変更・決定する
    /// </summary>
    void Update(std::weak_ptr<MouseInput>& input,std::weak_ptr<EditorUI>& ui);
    //左クリック中にマウスを移動させると使える機能
    enum class EditMode
    {
        //何も入力していない時は移動
        Move,
        //オブジェクトを回転させる
        Rotate,
        //削除
        Delete,
        //配置
        Put,
        //出てくるタイミングの変更
        ChangeFase,
        //制限時間の調整
        ChangeTimeLimit,
        //カメラの拡大縮小
        ScalingCameraBetween,
        //ひとつ前の状態に戻す
        BackEditState,
        //何もしていない時
        Free,
        //新しくオブジェクトを配置する　再編集する
        SelectObject,
        //編集をやり直す
        StepEditState,
        //編集したステージを遊ぶ
        PlayEditStage,
    };
    /// <summary>
    /// 今何をするべきか返す　
    /// </summary>
    /// <returns>今何をするべきか返す.左ボタンを長押しならHoldLeftButtonが返る</returns>
    EditorInput::EditMode GetEditMode()const;
    
private:
    //今何を入力したか
    EditMode inputMode;
    //回転モードフラグ
    bool isRotateMode = true;
    //編集フラグ
    bool isEditObject = false;
    //左ボタン長押し時のマウスX座標
    int holdMouseX;
    //左ボタン長押し時のマウスY座標
    int holdMouseY;
};