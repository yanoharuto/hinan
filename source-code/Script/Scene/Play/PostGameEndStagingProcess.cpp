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
/// ゴール後の演出をする
/// </summary>
/// <param name="player">ResultScoreにプレイヤー情報を渡す</param>
/// <param name="gameTimer">クリアタイムを受け取る</param>
PostGameEndStagingProcess::PostGameEndStagingProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<Timer> gameTimer)
{
    //スコアを確定
    resultScore = std::make_unique< ResultScore>(player,gameTimer);
    //音を所得
    SoundPlayer::StopAllSound();
    SoundPlayer::LoadAndInitSound(SoundKind::clap);
    SoundPlayer::LoadAndInitSound(SoundKind::scoreEndSE);
    SoundPlayer::LoadAndInitSound(SoundKind::scoreStartSE);
    SoundPlayer::LoadAndInitSound(SoundKind::sceneNextSE);
    SoundPlayer::LoadAndInitSound(SoundKind::gameEndFanfare);
    
    //プレイヤーの所得した収集アイテム
    getCollectNum = player.lock()->GetCollectCount();
    drawCollectIconNum = 0;
    //最初の処理
    nowConvertScore = ResultScore::ScoreKind::timeBonus;
    //タイムボーナス
    timeScoreUI = GetScoreUI(UIKind::timeScore);
    
    //収集アイテムボーナス
    collectScoreUI = GetScoreUI(UIKind::collectScore);
    collectUIData = UIManager::CreateUIData(UIKind::collectScoreIcon);
    //合計スコア
    totalScoreUI = GetScoreUI(UIKind::totalScore);
    totalScoreNumUI = std::make_unique< ScoreNum>();
    //ハイスコア更新UI
    highScoreUIData = UIManager::CreateUIData(UIKind::PraiseWord);
    //ゲーム終了時画面
    gameEndScreen = GameScreen::GetScreen();
    //スペースキー催促
    pressSpaceKeyUI = std::make_unique< FlashUI>(UIKind::resultSpaceKey);
    //クリアタイム保存
    clearTime = static_cast<float>(gameTimer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = std::make_unique<NumUI>(UIKind::timeScoreNum);
    //ゲーム終了アナウンス
    finishAnnounceUIData = UIManager::CreateUIData(UIKind::finishAnnounce);
    finishAnnounceUIData.x = Utility::SCREEN_WIDTH;
    larpMoveAnnounceTimer = std::make_unique<Timer>(finishAnounceTime);
    //花吹雪
    EffectManager::LoadEffect(EffectKind::confetti);
}
/// <summary>
/// 各UIを削除する
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
/// スコアの数字を徐々に出していく処理
/// </summary>
/// <returns></returns>
void PostGameEndStagingProcess::Update()
{
    if (!isEndFinishAnnounce)//終了アナウンスを出す
    {
        EndAnnounceProcess();
    }
    else if (isEndConvertScore)//加算処理終了後は加算音を消す
    {
        SoundPlayer::StopSound(SoundKind::scoreEndSE);

        pressSpaceKeyUI->Update();
        //スペースキーを押して終了
        if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
            isEndProcess = true;
        }
    }
    else
    {
        //各スコアを総合スコアに変換
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
/// スコアの描画
/// </summary>
void PostGameEndStagingProcess::Draw()const
{
    //ゲーム終了時の画面を暗く表示
    SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
    DrawGraph(0, 0, gameEndScreen, false);
    SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);

    //終了アナウンス
    if (!isEndFinishAnnounce) 
    {
        int safeNum = static_cast<int>(larpMoveAnnounceTimer->GetElaspedTime()) % finishAnnounceUIData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceUIData,safeNum);
    }
    else//各スコアの描画
    {
        CollectScoreDraw();
        TimeScoreDraw();
        UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
        //総合スコアのUIと数字
        totalScoreNumUI->Draw(totalScoreUI.score);
    }
    //全スコア変換処理が終わったらスペースキー催促
    if (isEndConvertScore)
    {
        pressSpaceKeyUI->Draw();
        //前回のハイスコアより大きかったら
        if (resultScore->IsUpdateHiScore())
        {
            //ハイスコア更新の文字
            UIDrawer::DrawRotaUI(highScoreUIData);
        }
    }
}
/// <summary>
/// 処理を終了したか
/// </summary>
/// <returns></returns>
bool PostGameEndStagingProcess::IsEndProcess() const
{
    return isEndProcess;
}
/// <summary>
/// クリアタイムのスコア変換
/// </summary>
void PostGameEndStagingProcess::ConvertTimeScotre()
{
    if (!SoundPlayer::IsPlaySound(SoundKind::sceneNextSE))
    {
        //スコアを換算し終えたか、スペースキーを押したら終了
        if ((larpConvertScoreTimer->IsOverLimitTime() || clearTime < 0 || UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push))
        {
            //次の処理
            nowConvertScore = ResultScore::ScoreKind::collectBonus;
                //タイムボーナスを表示したら終了
                SoundPlayer::StopSound(SoundKind::scoreStartSE);
                timeScoreUI.score = resultScore->GetScore(ResultScore::ScoreKind::timeBonus);
                drawClearTime = 0.0000f;
        }
        //タイマーが動いている間はスコア換算
        else
        {
            //残り時間をスコアに換算
            float larpValue = static_cast<float>(larpConvertScoreTimer->GetElaspedTime() / scoreLarpTime);

            timeScoreUI.score = static_cast<int>(larpValue * resultScore->GetScore(ResultScore::ScoreKind::timeBonus));
            //描画するクリアタイムを更新
            drawClearTime = clearTime - static_cast<float>(clearTime * larpValue);
            //スコア加算中はずっと鳴る
            if (!SoundPlayer::IsPlaySound(SoundKind::scoreStartSE))
            {
                SoundPlayer::Play2DSE(SoundKind::scoreStartSE);
            }
        }
    }
    //各スコアを合計
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// 収集アイテムのスコア変換
/// </summary>
void PostGameEndStagingProcess::ConvertCollectScotre()
{
    //一つ一つスコアに変換する工程をスキップ
    bool isSkip = UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push;
    //効果音が鳴り終わったタイミングで入手した宝石をスコアに変換する
    if (!SoundPlayer::IsPlaySound(SoundKind::scoreEndSE) || isSkip)
    {
        //描画したアイテムの数が獲得したアイテムの数と同じ以上にになったら
        if (isSkip || (drawCollectIconNum >= getCollectNum && !isEndConvertScore))
        {
            //描画するスコアなどを記録と統一
            collectScoreUI.score = resultScore->GetScore(ResultScore::ScoreKind::collectBonus);
            drawCollectIconNum = getCollectNum;
            isEndConvertScore = true;
            ////花吹雪エフェクト開始
            confettiEffect = EffectManager::GetPlayEffect2D(EffectKind::confetti);
            SetPosPlayingEffekseer2DEffect(confettiEffect, Utility::SCREEN_WIDTH / 2, Utility::SCREEN_HEIGHT, 5);
            //ファンファーレ効果音
            SoundPlayer::Play2DSE(SoundKind::gameEndFanfare);
        }
        else
        {        //収集アイテムを一個ずつ配置
            SoundPlayer::Play2DSE(SoundKind::scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(ResultScore::ScoreKind::collectBonus) * drawCollectIconNum;
        }
    }
    //各スコアを合計
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// ゲーム終了のアナウンスを流すプロセス
/// </summary>
void PostGameEndStagingProcess::EndAnnounceProcess()
{
    //最初の一回だけ拍手する
    if (!isSoundClapSE)
    {
        SoundPlayer::Play2DSE(SoundKind::clap);
        isSoundClapSE = true;
    }
    //larp移動が終了したら
    if (larpMoveAnnounceTimer->IsOverLimitTime())
    {
        isEndFinishAnnounce = true;
        larpConvertScoreTimer = std::make_unique<Timer>(scoreLarpTime);
        SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
    }
    else//移動させる
    {
        float larpTime = static_cast<float>(larpMoveAnnounceTimer->GetElaspedTime() / finishAnounceTime);
        //総数移動距離
        float graphWidth = finishAnnounceUIData.width / finishAnnounceUIData.dataHandle.size() * finishAnnounceUIData.size;
        float moveBetween = (Utility::SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
        finishAnnounceUIData.x = static_cast<int>(Utility::SCREEN_WIDTH * UIDrawer::GetScreenRaito() - larpTime * (moveBetween));
    }
}
/// <summary>
/// スコアに関するUIを所得
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
/// 残り時間スコアの描画
/// </summary>
void PostGameEndStagingProcess::TimeScoreDraw() const
{
    //クリアタイムの描画
    UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
    clearTimeUI->Draw(drawClearTime);
}
/// <summary>
/// 収集アイテムスコアの描画
/// </summary>
void PostGameEndStagingProcess::CollectScoreDraw() const
{
    //収集アイテムスコアのUI
    UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
    //所得したアイテムを少しずつ描画
    for (int i = 1; i <= drawCollectIconNum; i++)
    {
        UIData icon = collectUIData;
        icon.x += static_cast<int>(collectUIData.width * UIDrawer::GetScreenRaito() * icon.size * i);//右にずらしていく
        UIDrawer::DrawRotaUI(icon);
    }
}
