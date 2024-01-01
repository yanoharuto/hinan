#pragma once
#include <iostream>
#include <memory>
#define SCORE_KIND_NUM 4
class PlayerObserver;
class Timer;
/// <summary>
/// �ŏI�I�ȃX�R�A�̕ۑ���
/// </summary>
class ResultScore
{
public:
    /// <summary>
    /// �Q�[���N���A�����Ƃ��̃X�R�A���v�Z����
    /// </summary>
    /// <param name="player">�W�߂��A�C�e���̐��������Ă��炤</param>
    /// <param name="timer">�N���A�^�C������������</param>
    ResultScore(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer);
    //�X�R�A�̎��
    enum class ScoreKind
    {
        //�c�莞�ԃ{�[�i�X
        timeBonus = 0,
        //���W�A�C�e���{�[�i�X
        collectBonus = 1,
        //���v
        total = 2
    };
    /// <summary>
    /// �X�R�A����
    /// </summary>
    /// <param name="scoreKind">�~�����X�R�A�̎��</param>
    /// <returns>�����̃X�R�A��</returns>
    int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// �X�R�A�̔{��������
    /// </summary>
    /// <param name="scoreKind">�~�����X�R�A�̎��</param>
    /// <returns>�����̃X�R�A�̔{��</returns>
    int GetScoreBonus(ScoreKind scoreKind);
    /// <summary>
    /// �n�C�X�R�A���X�V���ꂽ��
    /// </summary>
    /// <returns>�n�C�X�R�A���X�V����Ă�����True</returns>
    bool IsUpdateHiScore();
    /// <summary>
    /// �X�e�[�W�̃n�C�X�R�A�𕶎���ɂ�������
    /// </summary>
    /// <returns>�X�e�[�W�̃n�C�X�R�A�𕶎���ɂ�������</returns>
    int GetUpdateScore()const;
private:
    /// <summary>
    /// �X�R�A���m�肳����
    /// </summary>
    /// <param name="remainingTime">�N���A�^�C������</param>
    /// <param name="getCollectNum">�v���C���[�̏����������W�A�C�e����</param>
    void FixScore(int remainingTime, int getCollectNum);
    //�c�莞�Ԃ̃X�R�A
    int timeScore = 0;
    //���W�A�C�e�����W�߂��X�R�A
    int collectScore = 0;
    //�n�C�X�R�A�X�V�t���O
    bool isUpdateHighScore = false;
    //�X�R�A�L�^�X�V�����Ƃ��̃X�R�A
    int updateScore;
    //�c�莞�Ԃ̃{�[�i�X
    static const int clearTimeBonus;
    //�R�C���̓{�[�i�X
    static const int getCollectBonus;
};

