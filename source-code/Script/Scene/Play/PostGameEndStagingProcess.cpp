#include "PostGameEndStagingProcess.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "GameScreen.h"
#include "SpaceKeyUI.h"
#include "NumUI.h"
#include "Timer.h"
#include "GameScreen.h"
#include "PlayerObserver.h"
#include "Object.h"
#include "UIDrawer.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "ScoreNum.h"
#include "PlayerObserver.h"
/// <summary>
/// �S�[����̉��o������
/// </summary>
/// <param name="player">ResultScore�Ƀv���C���[����n��</param>
/// <param name="gameTimer">�N���A�^�C�����󂯎��</param>
PostGameEndStagingProcess::PostGameEndStagingProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<Timer> gameTimer)
{
    //�X�R�A���m��
    resultScore = std::make_unique< ResultScore>(player,gameTimer);
    //��������
    SoundPlayer::StopAllSound();
    SoundPlayer::LoadAndInitSound(SoundKind::clap);
    SoundPlayer::LoadAndInitSound(SoundKind::scoreEndSE);
    SoundPlayer::LoadAndInitSound(SoundKind::scoreStartSE);
    SoundPlayer::LoadAndInitSound(SoundKind::sceneNextSE);
    SoundPlayer::LoadAndInitSound(SoundKind::gameEndFanfare);
    
    //�v���C���[�̏����������W�A�C�e��
    getCollectNum = player.lock()->GetCollectCount();
    drawCollectIconNum = 0;
    //�ŏ��̏���
    nowConvertScore = ResultScore::ScoreKind::timeBonus;
    //�^�C���{�[�i�X
    timeScoreUI = GetScoreUI(UIKind::timeScore);
    
    //���W�A�C�e���{�[�i�X
    collectScoreUI = GetScoreUI(UIKind::collectScore);
    collectUIData = UIManager::CreateUIData(UIKind::collectScoreIcon);
    //���v�X�R�A
    totalScoreUI = GetScoreUI(UIKind::totalScore);
    totalScoreNumUI = std::make_unique< ScoreNum>();
    //�n�C�X�R�A�X�VUI
    highScoreUIData = UIManager::CreateUIData(UIKind::PraiseWord);
    //�Q�[���I�������
    gameEndScreen = GameScreen::GetScreen();
    //�X�y�[�X�L�[�Ñ�
    pressSpaceKeyUI = std::make_unique< FlashUI>(UIKind::resultSpaceKey);
    //�N���A�^�C���ۑ�
    clearTime = static_cast<float>(gameTimer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = std::make_unique<NumUI>(UIKind::timeScoreNum);
    //�Q�[���I���A�i�E���X
    finishAnnounceUIData = UIManager::CreateUIData(UIKind::finishAnnounce);
    finishAnnounceUIData.x = Utility::SCREEN_WIDTH;
    larpMoveAnnounceTimer = std::make_unique<Timer>(finishAnounceTime);
    //�Ԑ���
    EffectManager::LoadEffect(EffectKind::confetti);
}
/// <summary>
/// �eUI���폜����
/// </summary>
PostGameEndStagingProcess::~PostGameEndStagingProcess()
{
    SAFE_RESET(larpConvertScoreTimer);
    SAFE_RESET(clearTimeUI);
    SAFE_RESET(pressSpaceKeyUI);
    SAFE_RESET(larpMoveAnnounceTimer);
    SAFE_RESET(totalScoreNumUI);
    SAFE_RESET(resultScore);
    UIManager::DeleteUIGraph(&highScoreUIData);
    UIManager::DeleteUIGraph(&finishAnnounceUIData);
    UIManager::DeleteUIGraph(&collectUIData);
    StopEffekseer2DEffect(confettiEffect);
}
/// <summary>
/// �X�R�A�̐��������X�ɏo���Ă�������
/// </summary>
/// <returns></returns>
void PostGameEndStagingProcess::Update()
{
    if (!isEndFinishAnnounce)//�I���A�i�E���X���o��
    {
        EndAnnounceProcess();
    }
    else if (isEndConvertScore)//���Z�����I����͉��Z��������
    {
        SoundPlayer::StopSound(SoundKind::scoreEndSE);

        pressSpaceKeyUI->Update();
        //�X�y�[�X�L�[�������ďI��
        if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
            isEndProcess = true;
        }
    }
    else
    {
        //�e�X�R�A�𑍍��X�R�A�ɕϊ�
        switch (nowConvertScore)
        {
        case ResultScore::ScoreKind::timeBonus:
            ConvertTimeScotre();
            break;
        case ResultScore::ScoreKind::collectBonus:
            ConvertCollectScotre();
            break;
        }
    }
}

/// <summary>
/// �X�R�A�̕`��
/// </summary>
void PostGameEndStagingProcess::Draw()const
{
    //�Q�[���I�����̉�ʂ��Â��\��
    SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
    DrawGraph(0, 0, gameEndScreen, false);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);

    //�I���A�i�E���X
    if (!isEndFinishAnnounce) 
    {
        int safeNum = static_cast<int>(larpMoveAnnounceTimer->GetElaspedTime()) % finishAnnounceUIData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceUIData,safeNum);
    }
    else//�e�X�R�A�̕`��
    {
        CollectScoreDraw();
        TimeScoreDraw();
        UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
        //�����X�R�A��UI�Ɛ���
        totalScoreNumUI->Draw(totalScoreUI.score);
    }
    //�S�X�R�A�ϊ��������I�������X�y�[�X�L�[�Ñ�
    if (isEndConvertScore)
    {
        pressSpaceKeyUI->Draw();
        //�O��̃n�C�X�R�A���傫��������
        if (resultScore->IsUpdateHiScore())
        {
            //�n�C�X�R�A�X�V�̕���
            UIDrawer::DrawRotaUI(highScoreUIData);
        }
    }
}
/// <summary>
/// �������I��������
/// </summary>
/// <returns></returns>
bool PostGameEndStagingProcess::IsEndProcess() const
{
    return isEndProcess;
}
/// <summary>
/// �N���A�^�C���̃X�R�A�ϊ�
/// </summary>
void PostGameEndStagingProcess::ConvertTimeScotre()
{
    if (!SoundPlayer::IsPlaySound(SoundKind::sceneNextSE))
    {
        //�X�R�A�����Z���I�������A�X�y�[�X�L�[����������I��
        if ((larpConvertScoreTimer->IsOverLimitTime() || clearTime < 0 || UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push))
        {
            //���̏���
            nowConvertScore = ResultScore::ScoreKind::collectBonus;
                //�^�C���{�[�i�X��\��������I��
                SoundPlayer::StopSound(SoundKind::scoreStartSE);
                timeScoreUI.score = resultScore->GetScore(ResultScore::ScoreKind::timeBonus);
                drawClearTime = 0.0000f;
        }
        //�^�C�}�[�������Ă���Ԃ̓X�R�A���Z
        else
        {
            //�c�莞�Ԃ��X�R�A�Ɋ��Z
            float larpValue = static_cast<float>(larpConvertScoreTimer->GetElaspedTime() / scoreLarpTime);

            timeScoreUI.score = static_cast<int>(larpValue * resultScore->GetScore(ResultScore::ScoreKind::timeBonus));
            //�`�悷��N���A�^�C�����X�V
            drawClearTime = clearTime - static_cast<float>(clearTime * larpValue);
            //�X�R�A���Z���͂����Ɩ�
            if (!SoundPlayer::IsPlaySound(SoundKind::scoreStartSE))
            {
                SoundPlayer::Play2DSE(SoundKind::scoreStartSE);
            }
        }
    }
    //�e�X�R�A�����v
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// ���W�A�C�e���̃X�R�A�ϊ�
/// </summary>
void PostGameEndStagingProcess::ConvertCollectScotre()
{
    //���X�R�A�ɕϊ�����H�����X�L�b�v
    bool isSkip = UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push;
    //���ʉ�����I������^�C�~���O�œ��肵����΂��X�R�A�ɕϊ�����
    if (!SoundPlayer::IsPlaySound(SoundKind::scoreEndSE) || isSkip)
    {
        //�`�悵���A�C�e���̐����l�������A�C�e���̐��Ɠ����ȏ�ɂɂȂ�����
        if (isSkip || (drawCollectIconNum >= getCollectNum && !isEndConvertScore))
        {
            //�`�悷��X�R�A�Ȃǂ��L�^�Ɠ���
            collectScoreUI.score = resultScore->GetScore(ResultScore::ScoreKind::collectBonus);
            drawCollectIconNum = getCollectNum;
            isEndConvertScore = true;
            ////�Ԑ���G�t�F�N�g�J�n
            confettiEffect = EffectManager::GetPlayEffect2D(EffectKind::confetti);
            SetPosPlayingEffekseer2DEffect(confettiEffect, Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT, 5);
            //�t�@���t�@�[�����ʉ�
            SoundPlayer::Play2DSE(SoundKind::gameEndFanfare);
        }
        else
        {        //���W�A�C�e��������z�u
            SoundPlayer::Play2DSE(SoundKind::scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(ResultScore::ScoreKind::collectBonus) * drawCollectIconNum;
        }
    }
    //�e�X�R�A�����v
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// �Q�[���I���̃A�i�E���X�𗬂��v���Z�X
/// </summary>
void PostGameEndStagingProcess::EndAnnounceProcess()
{
    //�ŏ��̈�񂾂����肷��
    if (!isSoundClapSE)
    {
        SoundPlayer::Play2DSE(SoundKind::clap);
        isSoundClapSE = true;
    }
    //larp�ړ����I��������
    if (larpMoveAnnounceTimer->IsOverLimitTime())
    {
        isEndFinishAnnounce = true;
        larpConvertScoreTimer = std::make_unique<Timer>(scoreLarpTime);
        SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
    }
    else//�ړ�������
    {
        float larpTime = static_cast<float>(larpMoveAnnounceTimer->GetElaspedTime() / finishAnounceTime);
        //�����ړ�����
        float graphWidth = finishAnnounceUIData.width / finishAnnounceUIData.dataHandle.size() * finishAnnounceUIData.size;
        float moveBetween = (Utility::SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
        finishAnnounceUIData.x = static_cast<int>(Utility::SCREEN_WIDTH * UIDrawer::GetScreenRaito() - larpTime * (moveBetween));
    }
}
/// <summary>
/// �X�R�A�Ɋւ���UI������
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
ScoreUI PostGameEndStagingProcess::GetScoreUI(UIInit::UIKind kind)
{
    ScoreUI ui;
    ui.scoreKindData = UIManager::CreateUIData(kind);
    ui.score = 0;
    return ui;
}
/// <summary>
/// �c�莞�ԃX�R�A�̕`��
/// </summary>
void PostGameEndStagingProcess::TimeScoreDraw() const
{
    //�N���A�^�C���̕`��
    UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
    clearTimeUI->Draw(drawClearTime);
}
/// <summary>
/// ���W�A�C�e���X�R�A�̕`��
/// </summary>
void PostGameEndStagingProcess::CollectScoreDraw() const
{
    //���W�A�C�e���X�R�A��UI
    UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
    //���������A�C�e�����������`��
    for (int i = 1; i <= drawCollectIconNum; i++)
    {
        UIData icon = collectUIData;
        icon.x += static_cast<int>(collectUIData.width * UIDrawer::GetScreenRaito() * icon.size * i);//�E�ɂ��炵�Ă���
        UIDrawer::DrawRotaUI(icon);
    }
}
