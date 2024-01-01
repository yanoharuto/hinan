#include "ScoreNum.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "UIDrawer.h"
#include <fstream>
#include <string>
/// <summary>
/// �X�R�A�̕]���̐�����������
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
/// highScoreUI�̍폜
/// </summary>
ScoreNum::~ScoreNum()
{
    UIManager::DeleteUIGraph(&highScoreUIData);
}
/// <summary>
/// �X�R�A�ɂ���đ傫���ύX
/// </summary>
/// <param name="num"></param>
void ScoreNum::Draw(int num)const
{
    VECTOR numColor = firstColor;
    UIData data = numUIData;
    //�X�R�A�̒i�K�ɂ���ĐF�Ƒ傫����ύX����
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
    //�X�R�A�̕`��
    SetDrawBright(static_cast<int>(numColor.x), static_cast<int>(numColor.y), static_cast<int>(numColor.z));
    NumUI::Draw(data, num);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
}