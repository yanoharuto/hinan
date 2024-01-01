#include "TitleHighScore.h"
#include "StageDataManager.h"
#include "UIDrawer.h"
/// <summary>
/// �^�C�g���ŕ\������n�C�X�R�A
/// </summary>
TitleHighScore::TitleHighScore()
    :NumUI(titleHiScoreNum)
{
    
}

/// <summary>
/// ���ݑI�΂�Ă���X�e�[�W�̃n�C�X�R�A�\��
/// </summary>
/// <param name="num"></param>
void TitleHighScore::Draw() const
{
    int prevHiScore = StageDataManager::GetScoreBorder().highScore;

    NumUI::Draw(prevHiScore);   
}