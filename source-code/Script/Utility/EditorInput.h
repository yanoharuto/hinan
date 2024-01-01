#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "UIManager.h"
#include "UIDrawer.h"
//入力するために必要なマウスの運動量
constexpr int INPUT_RANGE = 60;
class MouseInput;
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
    void Update(std::weak_ptr<MouseInput> input);
    //左クリック中にマウスを移動させると使える機能
    enum class EditMode
    {
        //何も入力していない時は移動
        Move,
        //オブジェクトを回転させる
        Rotate,
        //ひとつ前の状態に戻す
        BackPrevState,
        //削除
        Delete,
        //配置
        Put,
        //出てくるタイミングの変更
        ChangeFase,
        //制限時間の調整
        ChangeTimeLimit,
        //カメラの拡大縮小
        ScalingCamera,
        //何もしていない時
        Free,
        //新しくオブジェクトを配置する　再編集する
        SelectObject,
        //左ボタン長押しだと他の選択肢が出る状態になっている
        HoldButton,
        //編集したステージを遊ぶ
        PlayEditStage,
    };
    /// <summary>
    /// 今何をするべきか返す　
    /// </summary>
    /// <returns>今何をするべきか返す.左ボタンを長押しならHoldLeftButtonが返る</returns>
    EditorInput::EditMode GetEditMode()const;
    /// <summary>
    /// 操作説明の描画
    /// </summary>
    void Draw()const;
private:
    /// <summary>
    /// 左ボタン長押しで編集する内容を変える
    /// </summary>
    void HoldChangeLeftMode(int mouseX,int mouseY);
    /// <summary>
    /// 右ボタン長押しで編集する内容を変える
    /// </summary>
    void HoldChangeRightMode(int mouseX,int mouseY);
    
    /// <summary>
    /// マウス左ボタンが長押しなら操作説明
    /// </summary>
    /// <param name="format"></param>
    void DrawFormat(UIDrawer::Format format)const;
    //描画したい文字列と位置
    UIDrawer::Format manual[8] = {
        {
            -INPUT_RANGE,0,"移動"
        },
        {
            -INPUT_RANGE,0,"回転"
        },
        {
            INPUT_RANGE,0,"ひとつ前に戻る"
        },
        {
            0,INPUT_RANGE,"削除"
        },
        {
            0,-INPUT_RANGE,"配置"
        },
        {
            INPUT_RANGE,0,"フェーズ"
        },
        {
              -INPUT_RANGE,0,"制限時間"
        },
        {
            0,INPUT_RANGE,"カメラ"
        },
    };
    //今何をするか
    EditMode leftMode;
    //右ボタンホールドしたときのモード
    EditMode rightMode;
    //文字の色
    unsigned int formatColor = GetColor(255,255,255);
    //回転モードフラグ
    bool isRotateMode = true;
    //再編集モード
    bool isEditObject = false;
    //左ボタンをホールドしているか
    bool isLeftHold = false;
    //右ボタンをホールドしているか
    bool isRightHold = false;
    //左ボタン長押し時のマウスX座標
    int holdMouseX;
    //左ボタン長押し時のマウスY座標
    int holdMouseY;
    //編集したステージを遊ぶ
    UIData playEditStageUI;
};