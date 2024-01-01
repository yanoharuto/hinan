#include "GameScreen.h"
#include "Utility.h"
int GameScreen::screen = -1;
/// <summary>
/// 画像を保存されていたら削除
/// </summary>
GameScreen::GameScreen()
{
    if (screen != -1)
    {
        DeleteGraph(screen);
        screen = -1;
    }
}
/// <summary>
/// 画像を保存されていたら削除
/// </summary>
GameScreen::~GameScreen()
{
    if (screen != -1)
    {
        DeleteGraph(screen);
        screen = -1;
    }
}
/// <summary>
/// 描画している画像を更新
/// </summary>
void GameScreen::ScreenUpdate()
{
    //今保存している画面を削除
    DeleteGraph(screen);
    //今の画面を保存
    screen = MakeGraph(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, screen);
}
