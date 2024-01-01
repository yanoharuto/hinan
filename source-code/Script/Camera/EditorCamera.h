#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
#include "EditObjectData.h"
class MouseInput;
/// <summary>
/// �ҏW���[�h���̃J����
/// </summary>
class EditorCamera : public Camera
{
public:
    /// <summary>
    /// �J�����̃X�s�[�h�Ȃǂ̏�����
    /// </summary>
    EditorCamera();
    /// <summary>
    /// �ʒu�ƃ^�[�Q�b�g�̈ʒu���X�V
    /// </summary>
    /// <param name="input"></param>
    void UpdatePosition(std::weak_ptr<MouseInput>& input);
    /// <summary>
    /// �J�����̌����ƃ^�[�Q�b�g�̈ʒu���X�V�@
    /// </summary>
    /// <param name="input"></param>
    void UpdateTargetPosition(std::weak_ptr<MouseInput>& input);
private:
    //��]���x
    const float rotaSpeed = 0.01f;
    //�}�E�X�̒[
    const int mouseEdge = 10;
};

