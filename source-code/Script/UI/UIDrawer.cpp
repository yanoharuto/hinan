#include "UIDrawer.h"
#include "DxLib.h"
#include "Utility.h"

//横幅
 int UIDrawer::screenWidth = Utility::SCREEN_WIDTH;
//縦幅
 int UIDrawer::screenHeight = Utility::SCREEN_HEIGHT;
//横幅比率
 float UIDrawer:: widthRaito = 0.0f;
//縦幅比率
 float UIDrawer:: heightRaito = 0.0f;
 //画面の大きさ比率
 float UIDrawer::UIDrawer::screenSizeRaito = 1.0f;
 /// <summary>
/// 画面サイズ所得する
/// </summary>
 UIDrawer::UIDrawer()
 {
     int color;
     //画面サイズ
     GetScreenState(&screenWidth, &screenHeight, &color);
     //横幅比率
     widthRaito = static_cast<float>(screenWidth / Utility::SCREEN_WIDTH);
     //縦幅比率
     heightRaito = static_cast<float>(screenHeight / Utility::SCREEN_HEIGHT);
     //HDの大きさと比較した大きさ
     screenSizeRaito = static_cast<float>((screenWidth + screenHeight) / (Utility::SCREEN_WIDTH + Utility::SCREEN_HEIGHT));
 }
 /// <summary>
 /// drawRotaGraphを画面のサイズに合わせて出来るようにする
 /// </summary>
 /// <param name="data">描画したいUI</param>
 /// <param name="gHIndex">描画したいUIの添え字</param>
 /// <param name="angle">UIを傾ける</param>
 /// <param name="trans">透明度有効フラグ</param>
 /// <returns>失敗するとfalse</returns>
bool UIDrawer::DrawRotaUI(UIData data, int gHIndex, float angle, bool trans)
{
   gHIndex = gHIndex % data.dataHandle.size();
   //画面サイズに合わせた描画
   int x = static_cast<int>(data.x * widthRaito);
   int y = static_cast<int>(data.y * heightRaito);
   double size = static_cast<double>(data.size * screenSizeRaito);
   int success = DrawRotaGraph(x, y, size, angle, data.dataHandle[gHIndex], trans);
   return success != -1;
}
/// <summary>
/// スクリーンの想定の大きさとの差を倍率で渡す
/// </summary>
/// <returns></returns>
float UIDrawer::GetScreenRaito()
{
    return screenSizeRaito;
}