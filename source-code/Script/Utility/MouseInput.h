#pragma once
#include "DxLib.h"
/// <summary>
/// �}�E�X��X�N���[���̑傫���𑼂ɓ`����
/// </summary>
class MouseInput
{
public:
    MouseInput();
    ~MouseInput();
    /// <summary>
    /// �}�E�X��XY���W���X�V
    /// </summary>
    void UpdateMousePosition();
    /// <summary>
    /// �}�E�X��X���W
    /// </summary>
    /// <returns></returns>
    int GetMouseX()const { return mouseX; };
    /// <summary>
    /// �}�E�X��Y���W
    /// </summary>
    /// <returns></returns>
    int GetMouseY()const { return mouseY; };
    /// <summary>
    /// �X�N���[���̏c��
    /// </summary>
    /// <returns></returns>
    int GetHeight()const { return height; };
    /// <summary>
    /// �X�N���[���̉���
    /// </summary>
    /// <returns></returns>
    int GetWidth()const { return width; };
    /// <summary>
    /// �}�E�X�̈ʒu�ɂ���ăx�N�g���̌�����ύX����
    /// </summary>
    /// <param name="forwardVec">�O���x�N�g��</param>
    /// <returns>�}�E�X�̈ʒu�ɂ���ĕς������x�N�g��</returns>
    VECTOR GetNormDirection(VECTOR forwardVec)const;
    /// <summary>
    /// �}�E�X�̃z�C�[���̉�]�ň������}�C�i�X���v���X�ɂ���
    /// </summary>
    /// <returns>�}�C�i�X���v���X�ɂȂ�������</returns>
    int GetWheelIncreaseValue(int increaseValue = 1)const;
private:
    //�X�N���[���̏c�̑傫��
    int height;
    //�X�N���[���̉��̑傫��
    int width;
    //�}�E�X�̈ʒuX
    int mouseX;
    //�}�E�X�̈ʒuY
    int mouseY;
};

