#pragma once
#include <memory>
#include <iostream>
#include "DxLib.h"
class Object;
class Camera;
/// <summary>
/// �J�����̌������I�u�W�F�N�g�ɓn�����߂̃N���X
/// </summary>
class CameraObserver
{
public:
    /// <summary>
    /// �J���������L���Ă��炤
    /// </summary>
    /// <param name="setCamera">���L���Ă��炤�J����</param>
    CameraObserver(std::shared_ptr<Camera> setCamera);
    /// <summary>
    /// �J�����J��
    /// </summary>
    ~CameraObserver();
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�ҏW�J�����̌���</returns>
    VECTOR GetCameraDir()const;
    /// <summary>
    /// �J�����̃^�[�Q�b�g�̈ʒu��n��
    /// </summary>
    /// <returns>�^�[�Q�b�g�̈ʒu</returns>
    VECTOR GetTargetPosition()const;
    /// <summary>
    /// �J�����̈ʒu
    /// </summary>
    /// <returns></returns>
    VECTOR GetCameraPos()const;
    /// <summary>
    /// �����̂��̂��J�����͈͓̔������ׂ�
    /// </summary>
    /// <param name="obj">���ׂ����I�u�W�F�N�g</param>
    /// <returns>�J�����͈͓̔��Ȃ�True</returns>
    bool IsLookingCamera(std::weak_ptr<Object>& obj) const;
    /// <summary>
    /// �J�����ƃ^�[�Q�b�g�Ƃ̋���
    /// </summary>
    /// <returns></returns>
    float GetTargetBetweenSize() const;
private:
    //�Ď��ΏۃJ����
    std::shared_ptr<Camera> camera;
};
