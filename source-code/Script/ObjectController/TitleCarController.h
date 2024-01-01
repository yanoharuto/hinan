#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
#include "DxLib.h"
class TitleCar;
class Timer;
class ObjectObserver;
/// <summary>
/// �^�C�g���ő��点��
/// </summary>
class TitlteCarController : public ActorController
{
public:
    /// <summary>
    /// �^�C�g���ő��点���
    /// </summary>
    /// <param name="setPos">�����ʒu</param>
    /// <param name="setDir">��������</param>
    /// <param name="initTimer">����I�ɏ����ʒu�ɖ߂����߂̃^�C�}�[</param>
    TitlteCarController(VECTOR setPos, VECTOR setDir, std::shared_ptr<Timer> initTimer);
    /// <summary>
    /// �����Ă���Ԃƕ`����̊J��
    /// </summary>
    ~TitlteCarController()override;
    /// <summary>
    /// �Ԃ̈ړ�
    /// </summary>
    void Update()override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const override;
    /// <summary>
    /// �Ԃ̈ʒu�Ȃǂ��J�����Ȃǂɓn����悤�ɂ���
    /// </summary>
    /// <returns>�ԏ��`�B��</returns>
    std::shared_ptr<ObjectObserver> CreateCarObserver();
private:
    //�^�C�g���ő����
    std::shared_ptr<TitleCar> titleCar;
    //�Ԃ̈ʒu�Ȃǂ�`����
    std::shared_ptr<ObjectObserver> observer;
};