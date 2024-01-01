#pragma once
#include "UIManager.h"
/// <summary>
/// スクリーンの大きさによって描画位置とかを変える
/// </summary>
class UIDrawer
{
public:
    /// <summary>
    /// drawRotaGraphを画面のサイズに合わせて出来るようにする
    /// </summary>
    /// <param name="data">描画したいUI</param>
    /// <param name="gHIndex">描画したいUIの添え字</param>
    /// <param name="angle">UIを傾ける</param>
    /// <param name="trans">透明度有効フラグ</param>
    /// <returns>失敗するとfalse</returns>
    static bool DrawRotaUI(UIData data, int gHIndex = 0, float angle = 0, bool trans = true);
    /// <summary>
    /// スクリーンの想定の大きさとの差を倍率で渡す
    /// </summary>
    /// <returns></returns>
    static float GetScreenRaito();
    /// <summary>
    /// 画面サイズ所得してサイズによってUIの大きさを変更できるようにする
    /// </summary>
    UIDrawer();
    //位置と文字列の構造体
    struct Format
    {
        int addX;//開始位置X
        int addY;//開始位置Y
        std::string string;//文章
    };
private:
    //スクリーン横幅
    static int screenWidth;
    //スクリーン縦幅
    static int screenHeight;
    //横幅比率
    static float widthRaito;
    //縦幅比率
    static float heightRaito;
    //画面の大きさ比率
    static float screenSizeRaito;
};