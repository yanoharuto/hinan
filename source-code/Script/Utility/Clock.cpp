#include "Clock.h"
#include "DxLib.h"
#include "Utility.h"
#include "Menu.h"
//経過秒数
double Clock::gameTime;
/// <summary>
/// ゲーム開始の瞬間を保存
/// </summary>
Clock::Clock()
{
    // 現在のカウントを取得する
    timeD = static_cast<double>(GetNowHiPerformanceCount());
    gameTime = static_cast<double>(GetNowHiPerformanceCount()) / 1000000;
}
/// <summary>
/// タイマーを更新する
/// </summary>
void Clock::Update()
{
    // １７ミリ秒(約秒間６０フレームだった時の１フレームあたりの経過時間)
   double temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
   // 経過するまでここで待つ
    while (temp < Utility::DELTATIME)
    {
        temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    }

    // 現在のカウントを取得する
    timeD =  static_cast<double>(GetNowHiPerformanceCount());
    
    gameTime = timeD / 1000000;
}
/// <summary>
/// ゲームの経過時間を1000m秒にして渡す
/// </summary>
/// <returns></returns>
double Clock::GetNowGameTime()
{
    return gameTime - Menu::GetOpenMenuTime();
}
