#include "EndCountDown.h"
#include "Utility.h"
#include "UIManager.h"
#include "UIDrawer.h"
/// <summary>
/// ゲーム終了時のカウントダウン
/// </summary>
/// <param name="timer">ゲームの残り時間タイマー</param>
EndCountDown::EndCountDown(std::weak_ptr<Timer> timer)
	:CountDown(timer)
{
	endUIData = UIManager::CreateUIData(UIKind::onGameEndCountDownEnd);
}
/// <summary>
/// カウントダウンの数字と終わりを表示
/// </summary>
void EndCountDown::DrawUI() const
{
	if (uiHIndex != -1 && !isCountDownEnd)
	{
		//終了前に薄く表示
		int colorValue = Utility::MAX_ONE_BYTE_RANGE;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//α値をいじる
		UIDrawer::DrawRotaUI(countDownUIData, uiHIndex);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
	}
	else if (isCountDownEnd)//終わった時のUI
	{
		UIDrawer::DrawRotaUI(endUIData);
	}
}
