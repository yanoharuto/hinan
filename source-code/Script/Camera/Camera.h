#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "Camera.h"
#include "CameraDataLoader.h"
class ObjectObserver;
class Actor;

/// <summary>
/// �J����
/// </summary>
class Camera abstract
{
public:
    /// <summary>
    /// �J�����̑��x�⍂���̏�����
    /// </summary>
    /// <param name="type">�ǂ̃^�C�~���O�Ŏg����������</param>
    Camera(CameraDataLoader::UseCameraSceneKind type);
    /// <summary>
    /// �Ď��Ώۂ̉��
    /// </summary>
    virtual ~Camera();
    /// <summary>
    /// �J�����̌���������
    /// </summary>
    /// <returns>�J�����̌����x�N�g��</returns>
    VECTOR GetNormDirection()const;
    /// <summary>
    /// �J�����̃^�[�Q�b�g�̈ʒu��n��
    /// </summary>
    /// <returns>�^�[�Q�b�g�̈ʒu</returns>
    VECTOR GetTargetPosition()const;
    /// <summary>
    /// �J�����̈ʒu������
    /// </summary>
    /// <returns>�J�����̍��W</returns>
    VECTOR GetPosition()const;
    /// <summary>
    /// ������p�x������
    /// </summary>
    /// <returns></returns>
    float GetLookingAngle()const;
    /// <summary>
    /// �J�����ƃ^�[�Q�b�g�Ƃ̋���
    /// </summary>
    /// <returns></returns>
    float GetTargetBetweenSize() const { return targetBetweenSize; }
protected:
    /// <summary>
    /// �J�����̃p�����[�^����ǂݎ��
    /// </summary>
    /// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
    void LoadData(CameraDataLoader::UseCameraSceneKind type);
    //���������̂̈ʒu���������Ă������
    std::shared_ptr<ObjectObserver> targetObserver;
    //�J�����̈ʒu
    VECTOR position;
    //�J�����̕���
    VECTOR direction;
    //�_���ׂ��ꏊ
    VECTOR targetPos = { 0,0,0 };
    //�`�悵�悤�Ƃ���͈�
    float nearValue;
    //�`�悵�悤�Ƃ���͈�
    float farValue;
    //�^�[�Q�b�g�Ƃ̋���
    float targetBetweenSize;
    //����
    float posY;
    //�J�����̒ǂ������x
    float cameraSpeed;
    //�J�����̌�����͈͊p
    static float lookingAngle;
};