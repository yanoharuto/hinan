#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// ����������
/// </summary>
enum class HitSituation
{
    //�������ĂȂ�
    NotHit,
    //��������
    Enter,
    //�����葱���Ă���
    Stay,
    //���ꂽ
    Exist
};
/// <summary>
/// �����蔻��̌��� �n�����
/// </summary>
struct CollisionResultInfo
{
    //�����蔻��̓������
    HitSituation hit = HitSituation::NotHit;
    //���������I�u�W�F�N�g�̃^�O
    Object::Object::ObjectTag tag = Object::ObjectTag::obstacle;
    //������ԃx�N�g��
    VECTOR bounceVec = {};
    //����������̈ʒu
    VECTOR pos = {};
    //������ї�
    float bouncePower = 0;
    /// <summary>
    /// tag�┼�a�@������ї͂�ݒ�
    /// </summary>
    void SetObjInfo(Object* const obj)
    {
        tag = obj->GetTag();
        bouncePower = obj->GetBouncePower();
    }
};
