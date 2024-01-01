#pragma once
#include "DxLib.h"

/// <summary>
/// 描画した画像を保存する
/// </summary>
class GameScreen
{
public:
    /// <summary>
    /// 保存済み画像を削除
    /// </summary>
    GameScreen();
    /// <summary>
    /// 保存済み画像を削除
    /// </summary>
    ~GameScreen();
    /// <summary>
    /// 描画した画面を保存
    /// </summary>
    void ScreenUpdate();
    /// <summary>
    /// 最後に保存した画面を渡す
    /// </summary>
    /// <returns>最後に保存した画面</returns>
    static int GetScreen()
    {
        return screen;
    }
private:
    //最後に保存した画面
   static int screen;
};

