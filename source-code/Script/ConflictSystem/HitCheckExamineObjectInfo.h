#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// �����蔻��Ŏg�������ɂ��ēn���������
/// </summary>
struct HitCheckInfo
{
    //�|�W�V����
    VECTOR pos = {};
    //�ړ���
    VECTOR velocity = {};
    //���a
    float radius = 0;
    //�I�u�W�F�N�g�̎��
    Object::ObjectTag tag;
    /// <summary>
    /// �����蔻��ɕK�v�ȏ����Z�b�g
    /// </summary>
    /// <param name="obj">�Z�b�g�������I�u�W�F�N�g</param>
    void SetExamineInfo(Object* const obj)
    {
        tag = obj->GetTag();
        pos = obj->GetPos();
        radius = obj->GetRadius();
    }
};