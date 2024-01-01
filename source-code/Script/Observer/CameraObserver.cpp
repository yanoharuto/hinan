#include "CameraObserver.h"
#include "Camera.h"
#include "OriginalMath.h"
#include "Object.h"
/// <summary>
/// �J���������L���Ă��炤
/// </summary>
/// <param name="setCamera">���L���Ă��炤�J����</param>
CameraObserver::CameraObserver(std::shared_ptr<Camera> setCamera)
{
    camera = setCamera;
}
/// <summary>
/// �J�����J��
/// </summary>
CameraObserver::~CameraObserver()
{
    camera.reset();
}
/// <summary>
/// �J�����̌���������
/// </summary>
/// <returns>�ҏW�J�����̌���</returns>
VECTOR CameraObserver::GetCameraDir() const
{
    return camera->GetNormDirection();
}
/// <summary>
/// �J�����̃^�[�Q�b�g�̈ʒu��n��
/// </summary>
/// <returns>�^�[�Q�b�g�̈ʒu</returns>
VECTOR CameraObserver::GetTargetPosition() const
{
    return camera->GetTargetPosition();
}
/// <summary>
/// �J�����̈ʒu
/// </summary>
/// <returns></returns>
VECTOR CameraObserver::GetCameraPos() const
{
    return camera->GetPosition();
}

/// <summary>
/// �����̂��̂��J�����͈͓̔������ׂ�
/// </summary>
/// <param name="obj">���ׂ����I�u�W�F�N�g</param>
/// <returns>�J�����͈͓̔��Ȃ�True</returns>
bool CameraObserver::IsLookingCamera(std::weak_ptr<Object>& weakObj) const
{
    auto obj = weakObj.lock();
    if (obj != nullptr)
    {
        VECTOR between = VSub(obj->GetPos(), camera->GetPosition());
        return OriginalMath::GetDegreeMisalignment(between, camera->GetNormDirection()) < camera->GetLookingAngle();
    }
}
/// <summary>
/// �J�����ƃ^�[�Q�b�g�Ƃ̋���
/// </summary>
/// <returns></returns>
float CameraObserver::GetTargetBetweenSize() const
{
    return camera->GetTargetBetweenSize();
}
