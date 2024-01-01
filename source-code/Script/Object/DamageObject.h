#pragma once
#include <iostream>
#include <memory>
#include "Actor.h"
#include "InitObjKind.h"

class ObjectObserver;
/// <summary>
/// �_���[�W����̂���I�u�W�F�N�g
/// </summary>
class DamageObject abstract:
    public Actor
{
public:
    /// <summary>
    /// ���˂����z�̈ʒu�Ƃ���������|�C���^�[����������
    /// </summary>
    /// <param name="kind"></param>
    /// <param name="setObserver"></param>
    DamageObject(ObjectInit::InitObjKind kind, std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// ���˂����I�u�W�F�N�g�̃��j�[�N�|�C���^�̊J��
    /// </summary>
    virtual ~DamageObject();
protected:
    /// <summary>
    /// ���˂����I�u�W�F�N�g�̊Ď���
    /// </summary>
    std::unique_ptr<ObjectObserver> observer;
};

