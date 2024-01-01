#include "PlayerObserver.h"
#include "PlayerCar.h"
/// <summary>
/// プレイヤーの情報を渡すやつ
/// </summary>
/// <param name="playerCar">プレイヤー</param>
PlayerObserver::PlayerObserver(std::shared_ptr<PlayerCar>& playerCar)
    :ObjectObserver()
{
    subject = playerCar;
    player = playerCar;
}
/// <summary>
/// 収集アイテムを所得した回数
/// </summary>
/// <returns></returns>
int PlayerObserver::GetCollectCount()const
{
    return player->GetCollectCount();
}