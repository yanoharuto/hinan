#pragma once
#include <iostream>
#include <memory>
#include "Object.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class CameraObserver;
class MouseInput;
constexpr int EDIT_OBJECT_KIND = 7;
/// <summary>
/// �G�f�B�^��ŕ\������I�u�W�F�N�g
/// </summary>
class EditorObject : public Object
{
public:
    /// <summary>
    /// �ҏW���������̂������ɉ�����
    /// </summary>
    EditorObject();
    /// <summary>
    /// �ҏW�I�u�W�F�N�g�̎�ނ�ύX
    /// </summary>
    void UpdateKind(std::weak_ptr<MouseInput> input);
    /// <summary>
    /// �}�E�X�̈ʒu�ɂȂ�ׂ��ړ�
    /// </summary>
    /// <param name="cameraObserever">�J�����̓`�B��</param>
    /// <param name="input">�}�E�X����</param>
    void Move(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input);
    /// <summary>
    /// �}�E�X�ɉ����ĉ�]
    /// </summary>
    /// <param name="cameraObserever">�J�����̓`�B��</param>
    /// <param name="input">�}�E�X����</param>
    void Rotate(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input);
    /// <summary>
    /// �`��ɕK�v�ȍ\���̂�n��
    /// </summary>
    /// <returns>�ʒu�ƌ����ƕ`�悵�����I�u�W�F�N�g�̎��</returns>
    PlacementData GetPlacementData()const;
    /// <summary>
    /// �����̔z�u�������p���ʒu��ς���
    /// </summary>
    /// <param name="setData">�z�u</param>
    void SetArrangementData(PlacementData setData);
protected:
    //��]���x
    static const float rotaSpeed;
    //�ړ����x
    static const float moveSpeed;
    //�}�E�X�̈ʒu�ۑ��p
    int mouseX;
    //�}�E�X�̈ʒu�ۑ��p
    int mouseY;
    //�}�E�X�̒[����Ŏg��
    static const int mouseEdge;
    //�ҏW���̃I�u�W�F�N�g�̎�ޔԍ�
    int kind;
    //kinds�̓Y�����Ƃ��Ďg��
    int changeKindCount = 0;
    //�ҏW���̃I�u�W�F�N�g�̎�ޔԍ��̎Q�Ɛ�
    ObjectInit::InitObjKind kinds[EDIT_OBJECT_KIND] = 
    {
        ObjectInit::InitObjKind::saw,
        ObjectInit::InitObjKind::moveSaw,
        ObjectInit::InitObjKind::bomberShip,
        ObjectInit::InitObjKind::circleLaserShip,
        ObjectInit::InitObjKind::upDownLaserShip,
        ObjectInit::InitObjKind::collect,
        ObjectInit::InitObjKind::player
    };
};