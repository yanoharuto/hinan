#include "PrePlayGameProcess.h"
#include "DxLib.h"
#include "SoundPlayer.h"
#include "Utility.h"
#include "Timer.h"
#include "CountDown.h"
#include "NumUI.h"
#include "CollectController.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
/// <summary>
/// 操作説明やカウントダウン。音などを準備
/// </summary>
/// <param name="collectObserver">何個回収するか教えてもらう</param>
PrePlayGameProcess::PrePlayGameProcess(std::weak_ptr<CollectItemObserver> collectObserver)
{
    //音の確保
    SoundPlayer::LoadAndInitSound(SoundKind::fanfare);
    SoundPlayer::Play2DSE(SoundKind::fanfare);
    //UIの準備
    gamePuroseUIData = UIManager::CreateUIData(UIKind::gamePurose);
    collectIconUIData = UIManager::CreateUIData(UIKind::collectIcon);
    collectItemNum = std::make_unique<NumUI>(UIKind::collectTargetNumberUI);
    playManual = std::make_unique<PlayManual>();
    //フェードインフェードアウト用のタイマー
    frameByFrameTimer = std::make_unique<ReusableTimer>(gamePuroseUIData.frameSpeed);
    fadeValue = Utility::MAX_ONE_BYTE_RANGE;
    //アイテムの数を保存
    remainingCollectNum = collectObserver.lock()->GetTotalItemNum();
}
/// <summary>
/// カウントダウンなどを解放
/// </summary>
PrePlayGameProcess::~PrePlayGameProcess()
{
    SAFE_RESET(frameByFrameTimer);
    SAFE_RESET(countDown);
    SAFE_RESET(playManual);
    UIManager::DeleteUIGraph(&collectIconUIData);
    UIManager::DeleteUIGraph(&gamePuroseUIData);
    countDownTimer.reset();
    collectItemNum.reset();
}
/// <summary>
/// 遊び方とカウントダウンの描画
/// </summary>
void PrePlayGameProcess::Update()
{
    fadeValue--;
    //描画する画像のコマ送り用　何秒かごとに次のコマに行く
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Reuse();
        iconGHIndex++;
    }
    //ゲーム開始音が終わったら
    if (fadeValue < 1)
    {
        //タイマー開始
        if (countDownTimer == nullptr)
        {
            countDownTimer = std::make_shared<Timer>(startTimerLimit);
            countDown = std::make_unique<CountDown>(countDownTimer);
        }
        else
        {
            countDown->Update();
            //タイマーが終了したら処理終了
            processEnd = countDownTimer->IsOverLimitTime();
        }
    }
}
/// <summary>
/// 遊び方とカウントダウンの描画
/// </summary>
void PrePlayGameProcess::Draw() const
{
    if (fadeValue > 0)//フェードアウト中なら操作説明と目標を伝える
    {
        //ゲームの目的が見えにくいのでいったん後ろを白で埋める
        int colorValue = Utility::MAX_ONE_BYTE_RANGE;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
        DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
        //目標を説明
        UIDrawer::DrawRotaUI(gamePuroseUIData);
        int num = iconGHIndex % collectIconUIData.dataHandle.size();
        UIDrawer::DrawRotaUI(collectIconUIData,num);
        //何個集めるか
        collectItemNum->Draw(remainingCollectNum);
    }
    else
    {
        //カウントダウンと操作説明を表示
        countDown->DrawUI();
        playManual->Draw();
    }
}

/// <summary>
/// 処理が終了したか
/// </summary>
/// <returns>処理が終了したならTrue</returns>
bool PrePlayGameProcess::IsEndProcess()
{
    return processEnd;
}
