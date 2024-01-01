#include "NumUI.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "UIDrawer.h"
/// <summary>
/// 数字を描画する
/// </summary>
NumUI::NumUI(UIKind kind)
{
    numUIData = UIManager::CreateUIData(kind);
    pointUIData = UIManager::CreateUIData(UIKind::point);
    pointUIData.y = numUIData.y;
    pointUIData.size = numUIData.size;
}
/// <summary>
/// UI削除
/// </summary>
NumUI::~NumUI()
{
    UIManager::DeleteUIGraph(&numUIData);
    UIManager::DeleteUIGraph(&pointUIData);
}
/// <summary>
/// 整数の描画
/// </summary>
/// <param name="num">整数</param>
void NumUI::Draw(int num) const
{
    Draw(numUIData, num);
}

/// <summary>
/// 数字を描画したい時用
/// </summary>
/// <param name="x">一番右端</param>
/// <param name="y">Y座標</param>
/// <param name="num">数字</param>
/// <param name="scale">文字の大きさ</param>
/// <returns>左端の座標</returns>
int NumUI::Draw(UIData data, int num) const
{
    //桁数
    int digits = static_cast<int>(OriginalMath::GetDigits(num));
    //表示位置を右端にいったん移動
    data.x -= static_cast<int> (data.size * data.width * digits);
    //桁数がゼロになるまで描画する　頭から描画する
    for (int i = digits; i > 0; i--)
    {
        //10のけたで割った時のあまり
        int drawNum = (static_cast<int>(num / pow(TIMER_FONT_NUM, i - 1))) % numUIData.dataHandle.size();
        //描画
        UIDrawer::DrawRotaUI(data,drawNum);
        //位置をずらす
        data.x += static_cast<int> (data.size * data.width);
        //次に描画したい数字の準備
        num -= static_cast<int>(drawNum * pow(TIMER_FONT_NUM, i - 1));
    }
    return data.x;
}
/// <summary>
/// 小数点も描画したい時用
/// </summary>
/// <param name="x">一番右端</param>
/// <param name="y">Y座標</param>
/// <param name="num">数字</param>
/// <param name="scale">文字の大きさ</param>
/// <returns>左端の座標</returns>
void NumUI::Draw(float num) const
{
    //整数部分
    int iNum = static_cast<int>(num);
    //小数第一位の部分
    int decimalNum1 = static_cast<int>((num - iNum) * 10);
    //小数部分第二位
    int decimalNum2 = static_cast<int>(((num - iNum) * 100 - decimalNum1 * 10));
    UIData data = numUIData;
    //描画終了した場所をedgeに渡す
    data.x = Draw(data, decimalNum2);
    data.x -= static_cast<int> (numUIData.size * numUIData.width);
    data.x = Draw(data, decimalNum1);
    data.x -= static_cast<int> (numUIData.size * numUIData.width);
    //整数部分を描画
    Draw(data, iNum);
    data.x -= static_cast<int> (numUIData.size * numUIData.width);
    //小数点
    UIData pData = pointUIData;
    pData.x = data.x;
    UIDrawer::DrawRotaUI(pData);
}
/// <summary>
/// 一文字の大きさ
/// </summary>
/// <returns></returns>
int NumUI::GetNumWidthSize()
{
    return numUIData.width;
}
