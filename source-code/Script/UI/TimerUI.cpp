#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
#include "Timer.h"
#include "UIManager.h"
#include "NumUI.h"

/// <summary>
/// 残り時間のセットと数字画像の読み込み
/// </summary>
/// <param name="setTimer">残り時間タイマー</param>
TimerUI::TimerUI(std::weak_ptr<Timer> setTimer)
{
    timer = setTimer;
    frameUIData = UIManager::CreateUIData(UIKind:: timerFrame);
    pointUIData = UIManager::CreateUIData(UIKind::point);
    numUI = std::make_unique<NumUI>(UIKind::timeNum);
    //タイマーの枠の横位置
    frameX = frameUIData.x + numUI->GetNumWidthSize() * 2;
}
/// <summary>
/// タイマーのロック解除　UI削除
/// </summary>
TimerUI::~TimerUI()
{
    timer.reset();
    UIManager::DeleteUIGraph(&frameUIData);
    UIManager::DeleteUIGraph(&pointUIData);
}
/// <summary>
/// タイマーの残り時間を描画
/// </summary>
void TimerUI::Draw()
{
    //タイマーの枠を描画　中央にするために
    DrawRotaGraph(frameX , frameUIData.y, frameUIData.size, 0, frameUIData.dataHandle[0], true);
    //残り時間の描画
    float limit = static_cast<float>(timer.lock()->GetRemainingTime());
    numUI->Draw(limit);
}