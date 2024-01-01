#pragma once
#include "ObjectObserver.h"
class PlayerCar;
/// <summary>
/// �v���C���[�̏���n�����
/// </summary>
class PlayerObserver : public ObjectObserver
{
public:
    /// <summary>
    /// �v���C���[�̏���n�����
    /// </summary>
    /// <param name="playerCar">�v���C���[</param>
    PlayerObserver(std::shared_ptr<PlayerCar>& playerCar);
    /// <summary>
    /// ���W�A�C�e��������������
    /// </summary>
    /// <returns></returns>
    int GetCollectCount()const;
private:
    //�v���C���[�̊Ď���
    std::shared_ptr<PlayerCar> player;
};