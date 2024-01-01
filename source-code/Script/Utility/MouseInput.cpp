#include "MouseInput.h"
#include <iostream>
/// <summary>
/// ��ʂ̑傫���ƃ}�E�X�̈ʒu���X�V
/// </summary>
MouseInput::MouseInput()
{
    int color;
    //��ʃT�C�Y
    GetScreenState(&width, &height, &color);
    GetMousePoint(&mouseX, &mouseY);
}
MouseInput::~MouseInput()
{
}
/// <summary>
/// �}�E�X�̈ʒu���X�V
/// </summary>
void MouseInput::UpdateMousePosition()
{
    GetMousePoint(&mouseX, &mouseY);
}
/// <summary>
/// �}�E�X�̈ʒu�ɂ���ăx�N�g���̌�����ύX����
/// </summary>
/// <param name="forwardVec">�O���x�N�g��</param>
/// <returns>�}�E�X�̈ʒu�ɂ���ĕς������x�N�g��</returns>
VECTOR MouseInput::GetNormDirection(VECTOR forwardVec) const
{
    //�����̉��x�N�g��
    VECTOR cross = VCross(forwardVec, VGet(0, 1, 0));
    //��ʂ̕��ɑ΂���}�E�X��X��Y�̊���
    float yP = static_cast<float>(mouseY) / static_cast<float>(height);
    float xP = static_cast<float>(mouseX) / static_cast<float>(width);
    //��]��X��Z�����߂�
    float rotaX = std::lerp(-forwardVec.x, forwardVec.x, yP);
    rotaX += std::lerp(-cross.x, cross.x, xP);
    float rotaZ = std::lerp(-forwardVec.z, forwardVec.z, yP);
    rotaZ += std::lerp(-cross.z, cross.z, xP);
    return VNorm(VGet(rotaX, 0, rotaZ ));
}
/// <summary>
/// �}�E�X�̃z�C�[���̉�]�ň������}�C�i�X���v���X�ɂ���
/// </summary>
/// <returns>�}�C�i�X���v���X�ɂȂ�������</returns>
int MouseInput::GetWheelIncreaseValue(int increaseValue)const
{
    int wheelValue = GetMouseWheelRotVol();
    if (wheelValue > 0)
    {
        return increaseValue;
    }
    else if (wheelValue < 0)
    {
        return -increaseValue;
    }
    return 0;
}
