#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"

/// <summary>
/// �����蔻������L���邱�Ƃ��o����N���X
/// </summary>
class Actor abstract : public Object
{
public:
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    /// <param name="kind"></param>
    Actor(ObjectInit::InitObjKind kind);
    

    virtual ~Actor()
    {
    };

    /// <summary>
    /// �Փˏ���
    /// </summary>
    virtual void OnConflict(const CollisionResultInfo conflictInfo) {};

    /// <summary>
    /// �����蔻��œ������Ă���n�����
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitCheckExamineInfo();
};