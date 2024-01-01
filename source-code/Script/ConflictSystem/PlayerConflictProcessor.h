#pragma once
#include "ConflictProcessor.h"
class PlayerCar;
class PlayerObserver;
/// <summary>
/// �v���C���[�̏Փˏ������s��
/// </summary>
class PlayerConflictProcessor : public ConflictProcessor
{
public:
    /// <summary>
    /// �v���C���[�̏Փˏ������s��
    /// </summary>
    PlayerConflictProcessor(std::shared_ptr<PlayerCar>& car, std::shared_ptr<PlayerObserver>& observer);
    /// <summary>
    /// �Փˌ��ʎ��s��
    /// </summary>
    /// <param name="resultInfo">�Փˌ���</param>
    void OnConflict(CollisionResultInfo resultInfo)override;
private:
    std::shared_ptr<PlayerObserver> observer;
};