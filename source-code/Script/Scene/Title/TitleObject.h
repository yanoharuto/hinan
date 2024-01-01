#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
class Timer;
class ActorControllerManager;
class TitlteCarController;
class TitleCamera;
class ObjectObserver;
class ShadowMap;
class ReusableTimer;
class CollectItemObserver;
class CameraObserver;
/// <summary>
/// �^�C�g���̌��œ�����
/// </summary>
class TitleObject
{
public:
    /// <summary>
    /// �^�C�g���ŃQ�[���̕��͋C��`����
    /// </summary>
    TitleObject();
    /// <summary>
    /// �����������^�C�}�[�⑖���Ă���ԂȂǂ̉��
    /// </summary>
    ~TitleObject();
    /// <summary>
    /// �Ԃ�X�e�[�W�I���̍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �Ԃ�X�e�[�W�̕`��
    /// </summary>
    void Draw()const;
private:
    //�Z�߂ē������}�l�[�W���[
    std::unique_ptr<ActorControllerManager> manager;
    //�Ƃ肠���������Ă����
    std::shared_ptr<TitlteCarController> titleCarController;
    //���W�A�C�e���̊Ď��N���X
    std::shared_ptr<CollectItemObserver> collectItemObserver;
    //�J����
    std::shared_ptr<TitleCamera> camera;
    //���̃^�C�}�[���؂��Ə�ʕϊ�
    std::shared_ptr <ReusableTimer> initTimer;
    //�e
    std::unique_ptr<ShadowMap> shadowMap;
    //�e�ƃJ�����ɓn���Ԃ̃I�u�U�[�o
    std::shared_ptr<ObjectObserver> demoObserver; 
    //�J�����̌����Ȃǂ�m�点��
    std::shared_ptr<CameraObserver> cameraObserever;
    //��ʕϊ�����
    const float initTime = 15.0f;
    //��ʕϊ����x
    const float fadeSpeed = 3;
    //fadeValue�𑝂₷�����炷��
    bool isAValueIncrement = true;
    //��ʕϊ��n
    float fadeValue;
    //�����Ă���Ԃ̏����ʒu
    const VECTOR demoCarFirstPos = { -3200,0,0 };
    //�����Ă���Ԃ̏�������
    const VECTOR demoCarFirstDir = { 1,0,0.1f };
};