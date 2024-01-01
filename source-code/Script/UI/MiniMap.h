#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "DxLib.h"
#include "UIManager.h"
#include "ObjectObserver.h"

/// <summary>
/// �v���C���[�𒆐S�ɋ߂��ɃA�C�e�������邩���ׂ�����
/// </summary>
class MiniMap
{
public:
    /// <summary>
    /// ���W�A�C�e���Ƃ���`�悷�邽�߂̓z
    /// </summary>
    MiniMap(std::weak_ptr<ObjectObserver> player);
    /// <summary>
    /// �`�悷��}�[�J�[������
    /// </summary>
    ~MiniMap();
    /// <summary>
    /// �~�j�}�b�v�ɕ\������}�[�J�[�̈ʒu���X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �}�b�v�ɕ\������_�ƃ��[�_�[�̘g
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �}�b�v�ɔ��f���������A�C�e���̒ǉ�
    /// </summary>
    /// <param name="obserber"></param>
    static void AddMarker(std::unique_ptr<ObjectObserver> obserber);
private:
    /// <summary>
    /// �`�悷��}�[�J�[�̃|�W�V����
    /// </summary>
    /// <param name="subjectPos">���������}�[�J�[�̃I�u�W�F�N�g�̃|�W�V����</param>
    void UpdateDrawPosList(VECTOR subjectPos);
    /// <summary>
    /// �~�j�}�b�v�̑傫���ɕϊ�����
    /// </summary>
    /// <param name="between">�����̃A�C�e������̋���</param>
    /// <returns></returns>
    VECTOR ConvertPosition(VECTOR between);
    //�v���C���[�̃}�[�J�[�̐F
    const unsigned int playerColor = GetColor(180,200,0);
    //���W���̐F
    const unsigned int coinColor = GetColor(0,115,255);
    //�k�̈�̐F
    const unsigned int northColor = GetColor(255,0,0);
    //���@��Icon�̑傫��
    static const int iconSize = 5;
    //�~�j�}�b�v�̉摜�̕�
    int mapGraphWidth;
    //���W���̈ʒu�̏k��
    float betweenSize = 0.25f;
    //�~�j�}�b�v
    static UIData miniMapUIData;
    //�}�b�v�̒��S���ɂ���
    std::weak_ptr<ObjectObserver> playerObserver;
    //�}�[�J�[�̈ʒu���X�V���邽�߂̃��X�g
    static std::list<std::unique_ptr<ObjectObserver>> markerObserverList;
    //�`��ʒu�̃��X�g
    std::list<VECTOR> drawPosList;
    //�k�̈ʒu
    VECTOR northPos;
};