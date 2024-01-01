#pragma once
#include "DxLib.h"

/// <summary>
/// •`‰æ‚µ‚½‰æ‘œ‚ğ•Û‘¶‚·‚é
/// </summary>
class GameScreen
{
public:
    /// <summary>
    /// •Û‘¶Ï‚İ‰æ‘œ‚ğíœ
    /// </summary>
    GameScreen();
    /// <summary>
    /// •Û‘¶Ï‚İ‰æ‘œ‚ğíœ
    /// </summary>
    ~GameScreen();
    /// <summary>
    /// •`‰æ‚µ‚½‰æ–Ê‚ğ•Û‘¶
    /// </summary>
    void ScreenUpdate();
    /// <summary>
    /// ÅŒã‚É•Û‘¶‚µ‚½‰æ–Ê‚ğ“n‚·
    /// </summary>
    /// <returns>ÅŒã‚É•Û‘¶‚µ‚½‰æ–Ê</returns>
    static int GetScreen()
    {
        return screen;
    }
private:
    //ÅŒã‚É•Û‘¶‚µ‚½‰æ–Ê
   static int screen;
};

