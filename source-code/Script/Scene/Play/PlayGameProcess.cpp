#include "PlayGameProcess.h"
#include "ConflictManager.h"
#include "ActorControllerManager.h"
#include "GamePlayUI.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "SoundPlayer.h"
#include "PostGameEndStagingProcess.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "StopTimer.h"

/// <summary>
/// BGMとゲーム終了タイマーを起動
/// </summary>
/// <param name="player">UIにプレイヤー情報を渡す</param>
/// <param name="collectItemObserver">UIに収集アイテム情報を渡す</param>
PlayGameProcess::PlayGameProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<CollectItemObserver> const collectItemObserver)
{
	timer = StageDataManager::CreateGameTimer();
	playUI = new GamePlayUI(player, timer, collectItemObserver);
	SoundPlayer::LoadAndInitSound(SoundKind::playBGM);
}
/// <summary>
/// UIとタイマーの解放
/// </summary>
PlayGameProcess::~PlayGameProcess()
{
	SAFE_DELETE(playUI);
	timer.reset();
}
/// <summary>
/// 遊んでいるときの更新
/// </summary>
/// <param name="collectObserver">収集アイテムの残り数を教えてもらう</param>
void PlayGameProcess::Update(std::weak_ptr<CollectItemObserver> const collectObserver)
{
	if (isFirstUpdate)//初回ならタイマー再起動
	{
		timer->Reset();
		isFirstUpdate = false;
	}
	//収集アイテムが全部消え終わった,制限時間をオーバーしたなら終了
	if (collectObserver.lock()->GetRemainingItemNum() == 0 || timer->IsOverLimitTime())
	{
		isEndProcess = true;
	}
	//最後の一つを回収したならタイマーを止める
	if (collectObserver.lock()->IsCollectLastOne())
	{
		//タイマーストップ
		timer->Stop();
	}
	//BGMが鳴ってなかったら再生
	if (!SoundPlayer::IsPlaySound(SoundKind::playBGM))
	{
		SoundPlayer::Play2DSE(SoundKind::playBGM);
	}
	playUI->Update();
}
/// <summary>
/// 描画
/// </summary>
void PlayGameProcess::Draw() const
{
	playUI->Draw();
}
/// <summary>
/// ゲームの残り時間タイマーを渡す
/// </summary>
/// <returns> ゲームの残り時間タイマーを渡す</returns>
std::shared_ptr<Timer> PlayGameProcess::GetGameTimer()
{
	return timer;
};
