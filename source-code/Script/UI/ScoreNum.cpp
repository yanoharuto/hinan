#include "ScoreNum.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "UIDrawer.h"
#include <fstream>
#include <string>
/// <summary>
/// スコアの評価の線引きを所得
/// </summary>
ScoreNum::ScoreNum()
    :NumUI(UIKind::totalScoreNum)
{
    StageDataManager::ScoreBorder info = StageDataManager::GetScoreBorder();
    first = info.gold;
    second = info.silver;
    third = info.bronze;
}
/// <summary>
/// highScoreUIの削除
/// </summary>
ScoreNum::~ScoreNum()
{
    UIManager::DeleteUIGraph(&highScoreUIData);
}
/// <summary>
/// スコアによって大きさ変更
/// </summary>
/// <param name="num"></param>
void ScoreNum::Draw(int num)const
{
    VECTOR numColor = firstColor;
    UIData data = numUIData;
    //スコアの段階によって色と大きさを変更する
    if (num < third)
    {
        numColor = thirdUnderColor;
        data.size = numUIData.size * thirdUnderFontSize;
    }
    else if (num < second)
    {
        numColor = thirdColor;
        data.size = numUIData.size * thirdBorderFontSize;
    }
    else if (num < first)
    {
        numColor = secondColor;
        data.size = numUIData.size * secondBorderFontSize;
    }
    //スコアの描画
    SetDrawBright(static_cast<int>(numColor.x), static_cast<int>(numColor.y), static_cast<int>(numColor.z));
    NumUI::Draw(data, num);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
}