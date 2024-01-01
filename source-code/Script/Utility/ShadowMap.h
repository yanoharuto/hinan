#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"

class ObjectObserver;

/// <summary>
/// �e��`�悷��N���X
/// </summary>
class ShadowMap final
{
public:
    /// <summary>
    /// �v���C���[�𒆐S�ɉe��`��ł���悤�ɂ���
    /// </summary>
    /// <param name="player">�v���C���[�̈ʒu��`����N���X</param>
    ShadowMap(std::weak_ptr<ObjectObserver> player);
    /// <summary>
    /// �v���C���[�̃I�u�U�[�o�[�̃��Z�b�g�ƃV���h�E�}�b�v�̍폜
    /// </summary>
    ~ShadowMap();
    /// <summary>
    /// �e�̕`��͈͂̕ύX
    /// </summary>
    void SetShadowMapArea();
    /// <summary>
    /// ���ꂩ��`�悷��e�̏���
    /// </summary>
    void SetUpDrawShadow();
    /// <summary>
    /// �e��`�悷��̏I��
    /// </summary>
    void EndDrawShadow();
    /// <summary>
    /// �������񂾃V���h�E�}�b�v���g��
    /// </summary>
    void Use();
private:
    //�V���h�E�}�b�v�̍ŏ��͈͂�ݒ�
    VECTOR DrawAreaMinPos = VGet(-300.0f, -1.0f, -300.0f);
    //�V���h�E�}�b�v�̍ő�͈͂�ݒ�
    VECTOR DrawAreaMaxPos = VGet(300.0f, 700.0f, 300.0f);
    //�V���h�E�}�b�v�쐻
    int shadowMap = MakeShadowMap(2048, 2048);
    //���������ɉe�����͈͂����߂�
     std::weak_ptr<ObjectObserver> playerObserber;
};

