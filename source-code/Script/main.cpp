#include <iostream>
#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "EditorScene.h"
#include "Utility.h"
#include "UserInput.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "SoundPlayer.h"
#include "InitActor.h"
#include "EffectManager.h"
#include "UIManager.h"
#include "UIDrawer.h"
#include "StageDataManager.h"
//シーンを作るのに必要
std::unique_ptr<SceneBase> MakeScene(SceneType _NowSceneType);

//ひとつ前のシーン
SceneType prevSceneType = SceneType::title;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	ChangeWindowMode(true);
	// 画面の解像度と色ビット深度を設定
	SetGraphMode(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, 32);
	SetZBufferBitDepth(24);
	
	// １メートルに相当する値を設定する
	Set3DSoundOneMetre(16.0f);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	//Effekseerを初期化する
	if (Effect_Initialize() == -1) 
	{
		DxLib_End();
		return -1;
	}

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
	//今のシーン
	SceneType nowSceneType = SceneType::title;
	
	auto uiDrawer = std::make_unique <UIDrawer>();//画面サイズに合わせて描画できるようにする
	auto userInput = std::make_unique <UserInput>();//ユーザーの入力を所得する
	auto clock = std::make_unique <Clock>();//ゲーム内の時間
	auto stageDataManager = std::make_unique <StageDataManager>();//各ステージの情報管理
	auto uiManager = std::make_unique <UIManager>();//UIの管理
	auto initActor = std::make_unique <InitActor>();//各actorのパラメータの初期化を行う
	auto soundPlayer = std::make_unique <SoundPlayer>();//音の管理
	auto effectManager = std::make_unique <EffectManager>();//エフェクトの管理
	
	//シーンを生成
	std::unique_ptr<SceneBase> scene = std::make_unique<TitleScene>();
	FadeInFadeOut::FadeIn();
	
	//ゲームループ
	while (ProcessMessage() == 0 && nowSceneType != SceneType::escape)
	{

#ifdef _DEBUG
		clsDx(); // printfDx の結果をリセットするための関数.
#endif	// ここでDEBUG用の処理を終了.
		
		//更新
		clock->Update();
		userInput->Update();
		nowSceneType = scene->Update();
		//画面を初期化する
		ClearDrawScreen();
		scene->Draw();//描画
		//裏画面の内容を表画面に反映させる
		ScreenFlip();
		//Updateで次のシーンに更新したなら
		if (nowSceneType != prevSceneType)
		{
			SAFE_RESET(scene);//シーンの開放
			FadeInFadeOut::FadeOut();
			//新しいシーンの作成
			scene = MakeScene(nowSceneType);
			FadeInFadeOut::FadeIn();
		}
	}
	SAFE_RESET(scene);
	SAFE_RESET(uiDrawer);
	SAFE_RESET(uiManager);
	SAFE_RESET(initActor);
	SAFE_RESET(soundPlayer);
	SAFE_RESET(effectManager);
	SAFE_RESET(clock);
	SAFE_RESET(userInput);

	Effect_Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

/// <summary>
/// 新しく使うシーンを確保
/// </summary>
/// <param name="_NowSceneType"></param>
/// <returns></returns>
std::unique_ptr<SceneBase> MakeScene(SceneType _NowSceneType)
{
	std::unique_ptr<SceneBase> retScene = nullptr;
	switch (_NowSceneType)
	{
	case SceneType::reload:
		retScene = MakeScene(prevSceneType);
		break;
	case SceneType::title:
		retScene = std::make_unique <TitleScene>();
		prevSceneType = SceneType::title;
		break;
	case SceneType::play:
		retScene = std::make_unique<PlayScene>();
		prevSceneType = SceneType::play;
		break;
	case SceneType::editor:
		retScene = std::make_unique<EditorScene>();
		prevSceneType = SceneType::editor;
		break;
	default:
		break;
	}
	return retScene;
}