#pragma once
#include "DxLib.h"
/// <summary>
/// マウスやスクリーンの大きさを他に伝える
/// </summary>
class MouseInput
{
public:
    MouseInput();
    ~MouseInput();
    /// <summary>
    /// マウスのXY座標を更新
    /// </summary>
    void UpdateMousePosition();
    /// <summary>
    /// マウスのX座標
    /// </summary>
    /// <returns></returns>
    int GetMouseX()const { return mouseX; };
    /// <summary>
    /// マウスのY座標
    /// </summary>
    /// <returns></returns>
    int GetMouseY()const { return mouseY; };
    /// <summary>
    /// スクリーンの縦幅
    /// </summary>
    /// <returns></returns>
    int GetHeight()const { return height; };
    /// <summary>
    /// スクリーンの横幅
    /// </summary>
    /// <returns></returns>
    int GetWidth()const { return width; };
    /// <summary>
    /// マウスの位置によってベクトルの向きを変更する
    /// </summary>
    /// <param name="forwardVec">前方ベクトル</param>
    /// <returns>マウスの位置によって変わる向きベクトル</returns>
    VECTOR GetNormDirection(VECTOR forwardVec)const;
    /// <summary>
    /// マウスのホイールの回転で引数をマイナスかプラスにする
    /// </summary>
    /// <returns>マイナスかプラスになった引数</returns>
    int GetWheelIncreaseValue(int increaseValue = 1)const;
private:
    //スクリーンの縦の大きさ
    int height;
    //スクリーンの横の大きさ
    int width;
    //マウスの位置X
    int mouseX;
    //マウスの位置Y
    int mouseY;
};

