#include "EditorObject.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "CameraObserver.h"
#include "Utility.h"
#include "MouseInput.h"
//�ړ����x
const float EditorObject::moveSpeed = 17.0f;
//��]���x
const float EditorObject::rotaSpeed = 0.02f;
//�}�E�X�̒[����Ŏg��
const int EditorObject::mouseEdge = 10;
/// <summary>
/// �G�f�B�^��Ŏg�p����I�u�W�F�N�g
/// </summary>
EditorObject::EditorObject()
    :Object()
{
    position = {};
    direction = VGet(1, 0, 0);
    GetMousePoint(&mouseX, &mouseY);
    kind = CAST_I(ObjectInit::InitObjKind::saw);
}
/// <summary>
/// �ҏW�I�u�W�F�N�g�̎�ނ�ύX
/// </summary>
void EditorObject::UpdateKind(std::weak_ptr<MouseInput> input)
{
    changeKindCount += input.lock()->GetWheelIncreaseValue();
    if (changeKindCount >= EDIT_OBJECT_KIND)
    {
        changeKindCount = 0;
    }
    if (changeKindCount < 0)
    {
        changeKindCount = EDIT_OBJECT_KIND - 1;
    }
    kind = CAST_I(kinds[changeKindCount]);
}
/// <summary>
/// �}�E�X�̈ʒu�ɂȂ�ׂ��ړ�
/// </summary>
/// <param name="cameraObserever">�J�����̓`�B��</param>
/// <param name="input">�}�E�X����</param>
void EditorObject::Move(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input)
{
    // �}�E�X�|�C���^�������ʏ�̍��W�ɊY������R�c��ԏ�� Near �ʂ̍��W���擾
    const VECTOR startPosition = ConvScreenPosToWorldPos(VGet(input.lock()->GetMouseX(), input.lock()->GetMouseY(), 0.0f));

    // �}�E�X�|�C���^�������ʏ�̍��W�ɊY������R�c��ԏ�� Far �ʂ̍��W���擾
    const VECTOR endPos = ConvScreenPosToWorldPos(VGet(input.lock()->GetMouseX(), input.lock()->GetMouseY(), 1.0f));

    position = VAdd(cameraObserever.lock()->GetCameraPos(), VScale(VNorm(VSub(endPos, startPosition)), cameraObserever.lock()->GetTargetBetweenSize()));
}
/// <summary>
/// �}�E�X�ɉ����ĉ�]
/// </summary>
/// <param name="cameraObserever">�J�����̓`�B��</param>
/// <param name="input">�}�E�X����</param>
void EditorObject::Rotate(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input)
{
    direction = input.lock()->GetNormDirection(cameraObserever.lock()->GetCameraDir());
}
/// <summary>
/// �`��ɕK�v�ȍ\���̂�n��
/// </summary>
/// <returns>�ʒu�ƌ����ƕ`�悵�����I�u�W�F�N�g�̎��</returns>
PlacementData EditorObject::GetPlacementData() const
{
    PlacementData data;
    //����
    data.dirX = direction.x;
    data.dirZ = direction.z;
    //�|�W�V����
    data.posX = position.x;
    data.posZ = position.z;
    data.objKind = kind;
    return data;
}
/// <summary>
/// �����̔z�u�������p���ʒu��ς���
/// </summary>
/// <param name="setData">�z�u</param>
void EditorObject::SetArrangementData(PlacementData setData)
{
    position = VGet(setData.posX, 0, setData.posZ);
    direction = VGet(setData.dirX, 0, setData.dirZ);
    kind = setData.objKind;
}