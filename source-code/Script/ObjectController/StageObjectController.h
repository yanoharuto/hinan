#pragma once
#include <string>
#include <vector>
#include "ActorController.h"
class StageWall;
class Rock;
class FirstPositionGetter;
/// <summary>
/// ����ꏊ
/// </summary>
class StageObjectController final : public ActorController
{
public:
    /// <summary>
    /// ������
    /// </summary>
    StageObjectController();
    /// <summary>
    /// �X�e�[�W���͂ރI�u�W�F�N�g�̉��
    /// </summary>
    ~StageObjectController() override;
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const override;
private:
    //�n��
    int floorModelHandle;
    //��
    int skyDomeModelHandle;
    //��
    std::unique_ptr<StageWall> stageWall;
};