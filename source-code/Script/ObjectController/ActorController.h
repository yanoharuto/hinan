#pragma once
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "DrawModel.h"
class Actor;
class DrawModel;
class CameraObserver;
/// <summary>
/// 1�̎�ނ�actor�̎q�N���X�𓮂������߂Ɏg��
/// </summary>
class ActorController abstract
{
public:
    /// <summary>
    /// ���삷��I�u�W�F�N�g�̖��O��������
    /// </summary>
    ActorController(ObjectInit::InitObjKind kind) { controllObjKind = kind; };
    /// <summary>
    /// �`����ƃI�u�W�F�N�g�̃f���[�g
    /// </summary>
    virtual ~ActorController();
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update();
    /// <summary>
    /// �Q�[���J�n��������
    /// </summary>
    virtual void PrepareGame();
    /// <summary>
    /// �`�揈��
    /// </summary>
    virtual void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const;
protected:
    /// <summary>
    /// �`�����ActorList�̉��
    /// </summary>
    void DeleteActorListAndDrawModel();
    /// <summary>
    /// �����蔻��������ɒǉ�
    /// </summary>
    /// <param name="hitCheckOwner">�����蔻��̎�����</param>
    void AddConflictManagement(std::shared_ptr<Actor>& hitCheckOwner);
    //���̃��X�g����
    std::list <std::shared_ptr<Actor>> actorList;
    //�`��S��
    std::unique_ptr<DrawModel> drawModel;
    //���삷��I�u�W�F�N�g�̎��
    ObjectInit::InitObjKind controllObjKind;
};