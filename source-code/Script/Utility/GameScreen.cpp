#include "GameScreen.h"
#include "Utility.h"
int GameScreen::screen = -1;
/// <summary>
/// ‰æ‘œ‚ğ•Û‘¶‚³‚ê‚Ä‚¢‚½‚çíœ
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
/// ‰æ‘œ‚ğ•Û‘¶‚³‚ê‚Ä‚¢‚½‚çíœ
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
/// •`‰æ‚µ‚Ä‚¢‚é‰æ‘œ‚ğXV
/// </summary>
void GameScreen::ScreenUpdate()
{
    //¡•Û‘¶‚µ‚Ä‚¢‚é‰æ–Ê‚ğíœ
    DeleteGraph(screen);
    //¡‚Ì‰æ–Ê‚ğ•Û‘¶
    screen = MakeGraph(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, screen);
}
