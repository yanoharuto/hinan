#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
#include "MouseInput.h"
/// <summary>
/// Editor��ʂ̃J����
/// </summary>
EditorCamera::EditorCamera()
    :Camera(CameraDataLoader::UseCameraSceneKind::editor)
{
    targetPos = {0,0,0};
    position = targetPos;
    position.z = 1.0f;
    position.y = posY;
    direction = VNorm(VSub(targetPos, position));
    targetBetweenSize = VSize(VSub(targetPos, position));
}
/// <summary>
/// �J�����̈ʒu��ύX
/// </summary>
/// <param name="targetPlaceData">���������ꏊ�̔z�u���</param>
void EditorCamera::UpdatePosition(std::weak_ptr<MouseInput>& input)
{   
    VECTOR moveVector = { 0,0,0 };
    //�}�E�X���͏��
    auto mouseInput = input.lock();
    if (mouseInput == nullptr) return;
    //���E�̒[�ɗ�����
    if (mouseInput->GetMouseX() > mouseInput->GetWidth() - mouseEdge || mouseInput->GetMouseX() < mouseEdge)
    {
        //�E�[�Ƀ}�E�X���ʒu����Ȃ�True
        bool isRightEdge = mouseInput->GetMouseX() > mouseInput->GetWidth() - mouseEdge;
        //�ړ��x�N�g���̓J�����̌�������O�ςłƂ���������
        moveVector = VCross(direction, VGet(0,0,isRightEdge ? cameraSpeed : -cameraSpeed));

    }
    //�㉺�̒[�ɗ�����
    else if (mouseInput->GetMouseY() > mouseInput->GetHeight() - mouseEdge || mouseInput->GetMouseY() < mouseEdge)
    {
        //���[�Ƀ}�E�X���ʒu����Ȃ�True
        bool isDownEdge = mouseInput->GetMouseY() > mouseInput->GetHeight() - mouseEdge;
        //�ړ��x�N�g���̓J�����̌��������̋t����
        moveVector = VCross(direction, VGet(isDownEdge ? cameraSpeed : -cameraSpeed, 0, 0));
    }
    position = VAdd(position, moveVector);
    //�^�[�Q�b�g�̈ʒu���ύX
    targetPos = VAdd(position, VScale(direction, targetBetweenSize));
    //�ʒu�ƌ������m��
    SetCameraPositionAndTarget_UpVecY(position, targetPos);
}
/// <summary>
/// �J�����̌����ƃ^�[�Q�b�g�̈ʒu���X�V�@
/// </summary>
/// <param name="input"></param>
void EditorCamera::UpdateTargetPosition(std::weak_ptr<MouseInput>& input)
{
    auto mouseInput = input.lock();
    if (mouseInput == nullptr) return;
    //�}�E�X�̃z�C�[��
    int wheelValue = mouseInput->GetWheelIncreaseValue(cameraSpeed);
    if (wheelValue != 0)
    {
        //�J�����̌����Ƌ������X�V
        targetBetweenSize += wheelValue;
        position = VAdd(targetPos, VScale(direction, -targetBetweenSize));
    }
}