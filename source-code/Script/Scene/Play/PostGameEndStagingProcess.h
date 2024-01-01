#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "UIManager.h"
#include "ResultScore.h"
/// <summary>
/// �X�R�A�̕\��
/// </summary>
struct ScoreUI
{
    //�X�R�A�̎�ނɂ��Ă�UI��`�悷��
    UIData scoreKindData = {};
    //�X�R�A��
    int score = 0;
};
class Timer;
class NumUI;
class FlashUI;
class TimerUI;
class ScoreNum;
class PlayerObserver;
/// <summary>
/// �S�[����̉��o������
/// </summary>
class PostGameEndStagingProcess final
{
public:
    /// <summary>
    /// �S�[����̉��o������
    /// </summary>
    /// <param name="player">�v���C���[����n��</param>
    /// <param name="gameTimer">�N���A�^�C�����󂯎��</param>
    PostGameEndStagingProcess(std::weak_ptr<PlayerObserver> player,std::shared_ptr<Timer> gameTimer);
    /// <summary>
    /// �eUI���폜����
    /// </summary>
    ~PostGameEndStagingProcess();
    /// <summary>
    /// �X�R�A�̐��������X�ɏo���Ă�������
    /// </summary>
    /// <returns></returns>
    void Update();
    /// <summary>
    /// �X�R�A�̕`��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �������I��������
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const;
private:
    /// <summary>
    /// �N���A�^�C���̃X�R�A�ϊ�
    /// </summary>
    void ConvertTimeScotre();
    /// <summary>
    /// ���W�A�C�e���̃X�R�A�ϊ�
    /// </summary>
    void ConvertCollectScotre();
    /// <summary>
    /// �Q�[���I���̃A�i�E���X�𗬂��v���Z�X
    /// </summary>
    void EndAnnounceProcess();
    /// <summary>
    /// �X�R�A�Ɋւ���UI������
    /// </summary>
    /// <param name="kind"></param>
    /// <returns></returns>
    ScoreUI GetScoreUI(UIInit::UIKind kind);
    /// <summary>
    /// �c�莞�ԃX�R�A�̕`��
    /// </summary>
    void TimeScoreDraw() const;
    /// <summary>
    /// ���W�A�C�e���X�R�A�̕`��
    /// </summary>
    void CollectScoreDraw() const;
    //�X�y�[�X�L�[�Ñ�
    FlashUI* switchUI;
    //�N���A�^�C����\������p
    std::unique_ptr<NumUI> clearTimeUI;
    //���v�X�R�A�\��
    std::unique_ptr<ScoreNum> totalScoreNumUI;
    //�X�R�A�����X�ɕϊ����邽�߂̃^�C�}�[
    std::unique_ptr<Timer> larpConvertScoreTimer;
    //�S�[���A�i�E���X���\�����ꂫ��܂ł̎��Ԃ��v������
    std::unique_ptr<Timer> larpMoveAnnounceTimer;
    //�X�R�A�̕ۑ�
    std::unique_ptr<ResultScore> resultScore;
    //�X�y�[�X�L�[�Ñ�UI
    std::unique_ptr<FlashUI> pressSpaceKeyUI;
    //���v�X�R�A
    ScoreUI totalScoreUI;
    //���W�A�C�e�����W�߂ē���X�R�A
    ScoreUI collectScoreUI;
    //�c�莞�ԃ{�[�i�X�X�R�A
    ScoreUI timeScoreUI;
    //�n�C�X�R�A�̍X�V
    UIData highScoreUIData;
    //�I���̃A�i�E���X
    UIData finishAnnounceUIData;
    //���W�A�C�e���̃f�[�^
    UIData collectUIData;
    //�����̏������s���Ă��邩
    ResultScore::ScoreKind nowConvertScore;
    //�I���A�i�E���X
    bool isEndFinishAnnounce = false;
    //���������ׂčs������
    bool isEndProcess = false;
    //���v�X�R�A��`�悵����
    bool isEndConvertScore = false;
    //�N���A�^�C��
    float clearTime = 0;
    //���̉�ʂ̖��邳��Ⴍ����
    const int backScreenBright = 60;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�\������X�R�A���ϓ����Ă�������
    const float scoreLarpTime = 3.0f;
    //�I���A�i�E���X�Ɋ|���鎞��
    const float finishAnounceTime = 3.0f;
    //�`�悷��N���A�^�C���@�X�R�A�Ɋ��Z���Ă���
    float drawClearTime = 0;
    //�`�悷����W�A�C�e���̐�
    int drawCollectIconNum = 0;
    //�����U��Ԃт�
    int confettiEffect = -1;
    //�Q�b�g�����A�C�e���̐�
    int getCollectNum = 0;
    //�Q�[���I�����̉��
    int gameEndScreen = -1;
    //������ʉ�
    bool isSoundClapSE = false;
};
