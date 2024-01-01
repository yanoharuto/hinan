#pragma once
#include "UIManager.h"
/// <summary>
///　点滅しながら描画するUI
/// </summary>
class FlashUI
{
public:
    /// <summary>
    /// 点滅表示したいUIを引数に渡す
    /// </summary>
    /// <param name="uiKind"></param>
    FlashUI(UIKind uiKind);
    /// <summary>
    /// pressKeyDataの削除
    /// </summary>
    ~FlashUI();
    /// <summary>
    /// アルファ値の更新
    /// </summary>
    void Update();
    /// <summary>
    /// 徐々に薄くなったり濃くなったりしながら描画
    /// </summary>
    void Draw()const;
private:
    //スペースキーUI
    UIData pressKeyUIData;
    //アルファ値
    int aValue;
    //アルファ値の増加速度
    const int aSpeed = 10;
    //アルファ値の最低値
    const int lowtestAvalue = 60;
    //アルファ値を増やすかどうか
    bool isAValueIncrement = false;
};