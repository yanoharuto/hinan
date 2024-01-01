#include "MouseInput.h"
#include <iostream>
/// <summary>
/// 画面の大きさとマウスの位置を更新
/// </summary>
MouseInput::MouseInput()
{
    int color;
    //画面サイズ
    GetScreenState(&width, &height, &color);
    GetMousePoint(&mouseX, &mouseY);
}
MouseInput::~MouseInput()
{
}
/// <summary>
/// マウスの位置を更新
/// </summary>
void MouseInput::UpdateMousePosition()
{
    GetMousePoint(&mouseX, &mouseY);
}
/// <summary>
/// マウスの位置によってベクトルの向きを変更する
/// </summary>
/// <param name="forwardVec">前方ベクトル</param>
/// <returns>マウスの位置によって変わる向きベクトル</returns>
VECTOR MouseInput::GetNormDirection(VECTOR forwardVec) const
{
    //引数の横ベクトル
    VECTOR cross = VCross(forwardVec, VGet(0, 1, 0));
    //画面の幅に対するマウスのXとYの割合
    float yP = static_cast<float>(mouseY) / static_cast<float>(height);
    float xP = static_cast<float>(mouseX) / static_cast<float>(width);
    //回転量XとZを決める
    float rotaX = std::lerp(-forwardVec.x, forwardVec.x, yP);
    rotaX += std::lerp(-cross.x, cross.x, xP);
    float rotaZ = std::lerp(-forwardVec.z, forwardVec.z, yP);
    rotaZ += std::lerp(-cross.z, cross.z, xP);
    return VNorm(VGet(rotaX, 0, rotaZ ));
}
/// <summary>
/// マウスのホイールの回転で引数をマイナスかプラスにする
/// </summary>
/// <returns>マイナスかプラスになった引数</returns>
int MouseInput::GetWheelIncreaseValue(int increaseValue)const
{
    int wheelValue = GetMouseWheelRotVol();
    if (wheelValue > 0)
    {
        return increaseValue;
    }
    else if (wheelValue < 0)
    {
        return -increaseValue;
    }
    return 0;
}
