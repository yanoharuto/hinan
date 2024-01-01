#include "TitleCamera.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"

/// <summary>
/// �^�C�g����ʂ̃J�����@�Ԃ̎΂ߐ��ʂ��f��
/// </summary>
TitleCamera::TitleCamera(std::shared_ptr<ObjectObserver>& target)
    :Camera(CameraDataLoader::UseCameraSceneKind::title)
{
    targetObserver = target;
    VECTOR pos = targetObserver->GetSubjectPos();
    position = { 0,posY,0 };
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// �v���C���[�̈ʒu�ɍ��킹�ăJ�����̈ʒu���C��
/// </summary>
void TitleCamera::Update()
{
    auto target = targetObserver;
    if (target != nullptr)return;
    //�J�����̌����ʒu
    VECTOR aimPos = target->GetSubjectPos();
    //�Ԃ̌�������኱���炵�Ă���ɗ����
    VECTOR between = VScale(OriginalMath::GetYRotateVector(target->GetSubjectDir(),cameraRotate),targetBetweenSize);
    position = VAdd(VAdd(aimPos, VScale(target->GetSubjectDir(), targetBetweenSize)), between);
    position.y = posY;
    //�J�����̌�����ύX
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}