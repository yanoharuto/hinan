#include <fstream>
#include <sstream>
#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "PlayerObserver.h"
#include "StageDataManager.h"
#include "ScoreRecordWriter.h"
#include "StopTimer.h"
//���W�A�C�e���Q�b�g�{�[�i�X
const int ResultScore::getCollectBonus = 500;
//�c�莞�Ԃ̃{�[�i�X
const int ResultScore::clearTimeBonus = 50;
/// <summary>
/// �Q�[���N���A�����Ƃ��̃X�R�A���v�Z����
/// </summary>
/// <param name="player">�W�߂��A�C�e���̐��������Ă��炤</param>
/// <param name="timer">�N���A�^�C������������</param>
ResultScore::ResultScore(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer)
{
    //�c�莞��
    int scoreTime = timer.lock()->IsOverLimitTime() ? 0 : static_cast<int>(timer.lock()->GetRemainingTime());
    //�X�R�A���v�Z���Ċm�肳����
    FixScore(scoreTime, player.lock()->GetCollectCount());
}
/// <summary>
/// �X�R�A����
/// </summary>
/// <param name="scoreKind">�~�����X�R�A�̎��</param>
/// <returns>�����̎�ނ̃X�R�A��</returns>
int ResultScore::GetScore(ScoreKind scoreKind)
{
    switch (scoreKind)//�����̎�ނ̃X�R�A�̗ʂ�Ԃ�
    {
    case ResultScore::ScoreKind::timeBonus:
        return timeScore;
        break;
    case ResultScore::ScoreKind::collectBonus:
        return collectScore;
        break;
    case ResultScore::ScoreKind::total:
        return timeScore + collectScore;
        break;
    default:
        return 0;
        break;
    }
}
/// <summary>
/// �X�R�A�̔{��������
/// </summary>
/// <param name="scoreKind">�~�����X�R�A�̎��</param>
/// <returns>�����̃X�R�A�̔{��</returns>
int ResultScore::GetScoreBonus(ScoreKind scoreKind)
{
    switch (scoreKind)//�����̎�ނ̃X�R�A�̔{����Ԃ�
    {
    case ResultScore::ScoreKind::timeBonus:
        return clearTimeBonus;
        break;
    case ResultScore::ScoreKind::collectBonus:
        return getCollectBonus;
        break;
    default:
        return -1;
        break;
    }
}
/// <summary>
/// �n�C�X�R�A���X�V���ꂽ��
/// </summary>
/// <returns>�n�C�X�R�A���X�V����Ă�����True</returns>
bool ResultScore::IsUpdateHiScore()
{
    return isUpdateHighScore;
}
/// <summary>
/// �X�e�[�W�̃n�C�X�R�A�𕶎���ɂ�������
/// </summary>
/// <returns>�X�e�[�W�̃n�C�X�R�A�𕶎���ɂ�������</returns>
int ResultScore::GetUpdateScore() const
{
    return updateScore;
}
/// <summary>
/// �X�R�A���m�肳����
/// </summary>
/// <param name="remainingTime">�N���A�^�C������</param>
/// <param name="getCollectNum">�v���C���[�̏����������W�A�C�e����</param>
void ResultScore::FixScore(int remainingTime, int getCollectNum)
{
    //�X�R�A�̋L�^������
    StageDataManager::ScoreBorder score = StageDataManager::GetScoreBorder();
    //�������Ԃ𒴉߂��Ă���0
    timeScore = remainingTime * clearTimeBonus; 
    //���W�A�C�e��������Ă���{�[�i�X
    collectScore = getCollectNum * getCollectBonus;
    //���_
    updateScore = timeScore + collectScore;
    //������ߋ��̃n�C�X�R�A��葽��������True
    isUpdateHighScore = updateScore > score.highScore;
    //�X�R�A���X�V���ꂽ�Ȃ�
    if (updateScore > score.third)
    {
        ScoreRecordWriter* scoreRecordWriter = StageDataManager::GetScoreRecordWriter();
        //�X�R�A�̋L�^���X�V
        scoreRecordWriter->UpdateScoreRecord(this);
        SAFE_DELETE(scoreRecordWriter);
    }
}