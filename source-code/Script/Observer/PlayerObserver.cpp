#include "PlayerObserver.h"
#include "PlayerCar.h"
/// <summary>
/// �v���C���[�̏���n�����
/// </summary>
/// <param name="playerCar">�v���C���[</param>
PlayerObserver::PlayerObserver(std::shared_ptr<PlayerCar>& playerCar)
    :ObjectObserver()
{
    subject = playerCar;
    player = playerCar;
}
/// <summary>
/// ���W�A�C�e��������������
/// </summary>
/// <returns></returns>
int PlayerObserver::GetCollectCount()const
{
    return player->GetCollectCount();
}