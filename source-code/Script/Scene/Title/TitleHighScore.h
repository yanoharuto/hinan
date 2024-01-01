#pragma once
#include "NumUI.h"
/// <summary>
/// タイトルで表示するハイスコア
/// </summary>
class TitleHighScore : private NumUI
{
public:
    /// <summary>
    /// タイトルで表示するハイスコア
    /// </summary>
    TitleHighScore();
    /// <summary>
    /// 現在選ばれているステージのハイスコア表示
    /// </summary>
    void Draw()const;
private:
    //各ステージのハイスコア
    UIData highScoreUI;
};

