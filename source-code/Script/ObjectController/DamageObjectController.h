#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "ActorController.h"

class ObjectObserver;
class SphereHitChecker;
class ConflictProcessor;
class DamageObject;
/// <summary>
/// �_���[�W����̂���I�u�W�F�N�g�̊Ǘ��N���X
/// </summary>
class DamageObjectController abstract : public ActorController
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="kind">�������������I�u�W�F�N�g�̎��</param>
    DamageObjectController(ObjectInit::InitObjKind kind);

    /// <summary>
    /// �����̃I�u�W�F�N�g���琶�����ꂽ�Ƃ�
    /// </summary>
    /// <param name="sub">���˂����I�u�W�F�N�g�̈ʒu������Ȃǂ�n���N���X</param>
    virtual void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub) = 0;
protected:
};