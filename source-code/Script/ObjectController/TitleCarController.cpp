#include "TitleCarController.h"
#include "TitleCar.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "Object.h"
#include "DrawModel.h"
/// <summary>
/// �^�C�g���ő��点���
/// </summary>
/// <param name="setPos">�����ʒu</param>
/// <param name="setDir">��������</param>
/// <param name="initTimer">����I�ɏ����ʒu�ɖ߂����߂̃^�C�}�[</param>
TitlteCarController::TitlteCarController(VECTOR setPos, VECTOR setDir, std::shared_ptr<Timer> initTimer)
    :ActorController(ObjectInit::InitObjKind::player)
{
    titleCar = std::make_shared<TitleCar>(setPos, setDir,initTimer);
    observer = std::make_shared<ObjectObserver>(titleCar);
    drawModel = std::make_unique<DrawModel>(ObjectInit::InitObjKind::player);
}
/// <summary>
/// �����Ă���Ԃƕ`����̊J��
/// </summary>
TitlteCarController::~TitlteCarController()
{
    SAFE_RESET(titleCar);
    observer.reset();
    SAFE_RESET(drawModel);
}
/// <summary>
/// �Ԃ̈ړ�
/// </summary>
void TitlteCarController::Update()
{
    titleCar->Update();
}
/// <summary>
/// �`��
/// </summary>
void TitlteCarController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    drawModel->Draw(titleCar->GetPos(),titleCar->GetDir());
}
/// <summary>
/// �Ԃ̈ʒu�Ȃǂ��J�����Ȃǂɓn����悤�ɂ���
/// </summary>
/// <returns>�ԏ��`�B��</returns>
std::shared_ptr<ObjectObserver> TitlteCarController::CreateCarObserver()
{
    return observer;
}
