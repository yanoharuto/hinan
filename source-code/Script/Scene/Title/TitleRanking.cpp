#include "TitleRanking.h"
#include "NumUI.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// �^�C�g���Ŋe�X�e�[�W�̃X�R�A�����L���O��ʎO����`��
/// </summary>
TitleRanking::TitleRanking()
{
    //�X�R�AUI
    highUI = std::make_unique<NumUI>(UIKind::titleHiScoreNum);
    secondUI = std::make_unique<NumUI>(UIKind::titleSecondScoreNum);
    thirdUI = std::make_unique<NumUI>(UIKind::titleThirdScoreNum);
    //����UI
    highRankUI = std::make_unique<NumUI>(UIKind::rank1);
    secondRankUI = std::make_unique<NumUI>(UIKind::rank2);
    thirdRankUI = std::make_unique<NumUI>(UIKind::rank3);
    //HighScore�̕���
    rankUIData = UIManager::CreateUIData(UIKind::titleHighScore);
}
/// <summary>
/// �����L���O���\�����鐔��UI������
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
/// �����L���O�̏�ʎO����`��
/// </summary>
void TitleRanking::Draw() const
{
    auto borders = StageDataManager::GetScoreBorder();
    //1�ʃX�R�A�̕`��
    Draw(highUI.get(), borders.highScore, firstColor);
    Draw(highRankUI.get(), 1, firstColor);
    //2�ʃX�R�A�̕`��
    Draw(secondUI.get(), borders.second, secondColor);
    Draw(secondRankUI.get(), 2, secondColor);
    //3�ʃX�R�A�̕`��
    Draw(thirdUI.get(), borders.third, thirdColor);
    Draw(thirdRankUI.get(), 3, thirdColor);
    //HighScore�̕���
    UIDrawer::DrawRotaUI(rankUIData);
}
/// <summary>
/// �����̗v�f���g���ĕ`��
/// </summary>
/// <param name="ui">�g�����������`��UI</param>
/// <param name="num">�`�悵��������</param>
/// <param name="color">�����̐F</param>
void TitleRanking::Draw(NumUI* ui, int num, VECTOR color) const
{
    SetDrawBright(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
    ui->Draw(num);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
}
