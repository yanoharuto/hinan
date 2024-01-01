#pragma once
#include<iostream>
#include<memory>
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// �I�u�W�F�N�g�̊Ď���
/// </summary>
class ObjectObserver
{
public:
    /// <summary>
    /// �I�u�W�F�N�g�̊Ď���
    /// </summary>
    /// <param name="setSubject">�Ď��������I�u�W�F�N�g</param>
    ObjectObserver(std::shared_ptr<Object>  setSubject);
    /// <summary>
    /// �Ď��Ώۂ̊J��
    /// </summary>
    ~ObjectObserver();
    /// <summary>
    /// �Ď��Ώۂ̈ʒu��n��
    /// </summary>
    /// <returns></returns>
    virtual VECTOR GetSubjectPos() const;
    /// <summary>
    /// �Ď��Ώۂ̌���
    /// </summary>
    /// <returns></returns>
    virtual VECTOR GetSubjectDir() const;
    /// <summary>
    /// �Ď��Ώۂ̏��
    /// </summary>
    /// <returns></returns>
    virtual Object::ObjectState GetSubjectState()const;
protected:
    /// <summary>
    /// �q�N���X�p�̃R���X�g���N�^
    /// </summary>
    ObjectObserver() {};
    //�Ď����Ă��镨
    std::shared_ptr<Object> subject;
};