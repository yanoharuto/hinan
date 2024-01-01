#include "TitleHighScore.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// タイトルで表示するハイスコア
/// </summary>
TitleHighScore::TitleHighScore()
    :NumUI(titleHiScoreNum)
{
    
}

/// <summary>
/// 現在選ばれているステージのハイスコア表示
/// </summary>
/// <param name="num"></param>
void TitleHighScore::Draw() const
{
    int prevHiScore = StageDataManager::GetScoreBorder().highScore;

    NumUI::Draw(prevHiScore);   
}