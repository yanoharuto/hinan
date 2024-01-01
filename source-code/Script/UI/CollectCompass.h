#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class CollectItemObserver;
class PlayerObserver;
/// <summary>
/// ���W�A�C�e���̕������L���G�t�F�N�g���o��
/// </summary>
class CollectCompass
{
public:
    /// <summary>
    /// playerObserver��collectController�̏���
    /// </summary>
    /// <param name="player">�v���C���[�̈ʒu���������������</param>
    /// <param name="collectItemObserver">���W�A�C�e���̋����Ȃǂ���������</param>
    CollectCompass(std::weak_ptr<PlayerObserver> player,std::shared_ptr<CollectItemObserver> collectItemObserver);
    /// <summary>
    /// �G�t�F�N�g�I��
    /// </summary>
    ~CollectCompass();
    /// <summary>
    /// �G�t�F�N�g�̈ʒu�ƌ�����ݒ�
    /// </summary>
    void Update();
private:
    //�v���C���[�̈ʒu�����������Ă���
    std::weak_ptr<PlayerObserver> playerObserver;
    //���W�A�C�e���̊Ǘ��N���X
    std::weak_ptr<CollectItemObserver> collectObserver;
    //�G�t�F�N�g�n���h��
    int compassEffect = -1;
    //�G�t�F�N�g��Y���W
    const float addYPos = 13;
};