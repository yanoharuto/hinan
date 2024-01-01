#pragma once

#include "SceneType.h"

class FadeInFadeOut;
class SceneFlowBase;
class Clock;
class SoundPlayer;
class InitActor;
class EffectManager;
class UIManager;
/// <summary>
/// �e�V�[���̕����n��
/// </summary>
class SceneBase abstract
{
public:
    /// <summary>
    /// ���݂̃V�[���̕ۑ�
    /// </summary>
    /// <param name="_SceneType">���݂̃V�[���̕ۑ�</param>
    SceneBase(SceneType _SceneType);    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBase() {};
    /// <summary>
    /// �V�[���̍X�V
    /// </summary>
    /// <returns>���̃V�[��</returns>
    virtual SceneType Update() = 0;
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() const = 0;
protected:
    //���̃V�[���̎��
    SceneType nowSceneType;
};