#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "EndCountDown.h"
#include "CollectCompass.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
/// <summary>
/// プレイヤーや制限時間、収集アイテムの数などを表示できるようにする
/// </summary>
/// <param name="player">プレイヤーの位置</param>
/// <param name="timer">制限時間</param>
/// <param name="collectItemObserver">収集アイテム情報</param>
GamePlayUI::GamePlayUI(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer, std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    //残り時間
    gameTimerUI = std::make_unique <TimerUI>(timer);
    //ミニマップ
    minimapUI = std::make_unique <MiniMap>(player);
    //残りの収集アイテムの数
    allCollectNum = collectItemObserver->GetTotalItemNum();
    firstCollectNumUI = std::make_unique<NumUI>(UIKind::allCollectItemNum);
    //現在取った数
    getNumUI = std::make_unique<NumUI>(UIKind::getCollectItemNum);
    remainingNumUI = std::make_unique<NumUI>(UIKind::remainingCollectItemNum);
    //収集アイテムに関するUIの枠
    frameUIData = UIManager::CreateUIData(UIKind::collectItemFrameUI);
    //残り収集アイテムについてのコメントUI
    remainingFrazeUIData = UIManager::CreateUIData(UIKind::remainingCollectItemPhrase);
    //プレイヤーのアイテム所得情報を教えてもらう
    playerObserver = player;
    //収集アイテムの方向を出す
    collectCompass = std::make_unique <CollectCompass>(player, collectItemObserver);
    //ゲーム終了カウントダウン
    countDown = std::make_unique <EndCountDown>(timer);
    //残り時間
    remainingNumDrawTimer = std::make_unique <ReusableTimer>(remainingNumDrawTime);
    //操作方法
    playManual = std::make_unique <PlayManual>();
}

/// <summary>
/// 各UIを開放
/// </summary>
GamePlayUI::~GamePlayUI()
{
    SAFE_RESET(gameTimerUI);
    SAFE_RESET(minimapUI);
    getNumUI.reset();
    firstCollectNumUI.reset();
    remainingNumUI.reset();
    SAFE_RESET(countDown);
    SAFE_RESET(collectCompass);
    SAFE_RESET(remainingNumDrawTimer);
    SAFE_RESET(playManual);
    playerObserver.reset();
    UIManager::DeleteUIGraph(&remainingFrazeUIData);
    UIManager::DeleteUIGraph(&frameUIData);
}
/// <summary>
/// ミニマップの更新や収集アイテムの枚数を更新
/// </summary>
void GamePlayUI::Update()
{
    int tempNum = nowGetCollectNum;
    //収集アイテムの数
    nowGetCollectNum = playerObserver.lock()->GetCollectCount();
    //ゲットしたアイテムの数が増えたらUIを表示
    if (nowGetCollectNum != tempNum)
    {
        isDrawGetNum = true;
        remainingNumDrawTimer->Reuse();
    }
    //表示しきったらfalseにする
    if (remainingNumDrawTimer->IsOverLimitTime())
    {
        isDrawGetNum = false;
    }
    //ゲームの残り時間が短くなったら動く
    countDown->Update();
    //ミニマップ
    minimapUI->Update();
    //収集アイテムの位置を教えてくれる
    collectCompass->Update();
    //操作方法更新
    playManual->Update();
}
/// <summary>
/// 描画
/// </summary>
void GamePlayUI::Draw()const
{
    if (isDrawGetNum)//収集アイテムを取ってしばらくの間、残りの数を出す
    {
        int safeNum = 0;
        switch (allCollectNum - nowGetCollectNum)//残りのアイテムの数に応じて取った時のメッセージを変える
        {
        case 0:
            break;
        case 1:
            safeNum = 1;
            //残りの収集アイテムについてのメッセージ
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            break;
        default:
            //残りの収集アイテムについてのメッセージ
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            remainingNumUI->Draw(allCollectNum - nowGetCollectNum);
            break;
        }
        
    }
    //収集アイテムの数等を表示
    UIDrawer::DrawRotaUI(frameUIData);
    firstCollectNumUI->Draw(allCollectNum);
    getNumUI->Draw(nowGetCollectNum);
    //残り時間
    gameTimerUI->Draw();
    //ミニマップ
    minimapUI->Draw();
    //残り時間わずかになると動くカウントダウン
    countDown->DrawUI();
    //操作方法描画
    playManual->Draw();
}