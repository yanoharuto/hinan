#include "PlayerCarController.h"
#include "PlayerCar.h"
#include "SphereHitChecker.h"
#include "SoundPlayer.h"
#include "SoundListener.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "PlayerDrawModel.h"
#include "PlayerObserver.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ConflictManager.h"
/// <summary>
/// �v���C���[�̎Ԃ̏�����
/// </summary>
PlayerCarController::PlayerCarController()
    :ActorController(ObjectInit::InitObjKind::player)
{
    //�����ʒu
    std::vector<PlacementData> editData = FirstPositionGetter::GetPlaceData(InitObjKind::player);
    //�Ԃ̊J��
    car = std::make_shared<PlayerCar>(editData[0]);
    playerObserver = std::make_shared<PlayerObserver>(car);
    //�����蔻���ǉ�
    std::shared_ptr<Actor> actor = car;
    auto colider = std::make_shared<SphereHitChecker>(car);
    auto conflictProccesor = std::make_unique<ConflictProcessor>(car);
    ConflictManager::AddConflictProcessor(conflictProccesor, colider);
    //�v���C���[�̈ʒu���特���W�߂郊�X�i�[�̐ݒ�
    listener = std::make_unique<SoundListener>(CreatePlayerObserver());
    //�v���C���[�`���
    playerDrawer = std::make_unique<PlayerDrawModel>();
}
/// <summary>
/// �Ԃ�Lisner��Delete
/// </summary>
PlayerCarController::~PlayerCarController()
{
    SAFE_RESET(car);
    SAFE_RESET(listener);
}
/// <summary>
/// �Ԃ̈ʒu�Ƃ���n��
/// </summary>
/// <returns></returns>
std::shared_ptr<PlayerObserver> PlayerCarController::CreatePlayerObserver() const
{
    return playerObserver;
}
/// <summary>
/// ���𕷂����߂ɏꏊ���X�V
/// </summary>
void PlayerCarController::Update()
{
    car->Update();
    listener->Update();
}
/// <summary>
/// �`��
/// </summary>
void PlayerCarController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    playerDrawer->Draw(car->GetPos(),car->GetDir(),car->GetModelRotateVec());
}
