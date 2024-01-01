#include "FadeInFadeOut.h"
#include "DxLib.h"
#include "Utility.h"
#include "GameScreen.h"
//画面が移り変わる値。高いほど白くなる
int FadeInFadeOut::fadeValue = 0;
//画面が移り変わる速度
const int FadeInFadeOut::fadeSpeed = 10;
//後ろの背景
int FadeInFadeOut::backScreen = -1;

/// <summary>
/// フェードイン
/// </summary>
void FadeInFadeOut::FadeIn()
{
	fadeValue = Utility::MAX_ONE_BYTE_RANGE;
	//切り替え前の画像が残ってたら消去
	if (backScreen != -1)
	{
		DeleteGraph(backScreen);
	}
	//風景が見えるようになるまで
	while (fadeValue > 0)
	{
		fadeValue -= fadeSpeed;//α値と色のRGB増加
		Fading();
	}
}
/// <summary>
/// だんだん白くなる
/// </summary>
void FadeInFadeOut::FadeOut()
{
	fadeValue = 0;
	backScreen = GameScreen::GetScreen();
	while (fadeValue < Utility::MAX_ONE_BYTE_RANGE)
	{
		fadeValue += fadeSpeed;//α値と色のRGB増加
		Fading();
	}
}
/// <summary>
/// アウト中なら白くなる　インなら周りのモデルとかが見える
/// </summary>
void FadeInFadeOut::Fading()
{
	//画面を初期化する
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
	int colorValue = Utility::MAX_ONE_BYTE_RANGE;
	DrawGraph(0, 0, backScreen, false);
	DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
	//裏画面の内容を表画面に反映させる
	ScreenFlip();
}