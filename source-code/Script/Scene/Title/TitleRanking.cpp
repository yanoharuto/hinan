#include "TitleRanking.h"
#include "NumUI.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// タイトルで各ステージのスコアランキング上位三名を描画
/// </summary>
TitleRanking::TitleRanking()
{
    //スコアUI
    highUI = std::make_unique<NumUI>(UIKind::titleHiScoreNum);
    secondUI = std::make_unique<NumUI>(UIKind::titleSecondScoreNum);
    thirdUI = std::make_unique<NumUI>(UIKind::titleThirdScoreNum);
    //順位UI
    highRankUI = std::make_unique<NumUI>(UIKind::rank1);
    secondRankUI = std::make_unique<NumUI>(UIKind::rank2);
    thirdRankUI = std::make_unique<NumUI>(UIKind::rank3);
    //HighScoreの文字
    rankUIData = UIManager::CreateUIData(UIKind::titleHighScore);
}
/// <summary>
/// ランキングを構成する数字UIを消去
/// </summary>
TitleRanking::~TitleRanking()
{
    highUI.reset();
    secondUI.reset();
    thirdUI.reset();
    highRankUI.reset();
    secondRankUI.reset();
    thirdRankUI.reset();
    UIManager::DeleteUIGraph(&rankUIData);
}
/// <summary>
/// ランキングの上位三名を描画
/// </summary>
void TitleRanking::Draw() const
{
    auto borders = StageDataManager::GetScoreBorder();
    //1位スコアの描画
    Draw(highUI.get(), borders.highScore, firstColor);
    Draw(highRankUI.get(), 1, firstColor);
    //2位スコアの描画
    Draw(secondUI.get(), borders.second, secondColor);
    Draw(secondRankUI.get(), 2, secondColor);
    //3位スコアの描画
    Draw(thirdUI.get(), borders.third, thirdColor);
    Draw(thirdRankUI.get(), 3, thirdColor);
    //HighScoreの文字
    UIDrawer::DrawRotaUI(rankUIData);
}
/// <summary>
/// 引数の要素を使って描画
/// </summary>
/// <param name="ui">使いたい数字描画UI</param>
/// <param name="num">描画したい数字</param>
/// <param name="color">数字の色</param>
void TitleRanking::Draw(NumUI* ui, int num, VECTOR color) const
{
    SetDrawBright(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
    ui->Draw(num);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
}
