#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// �X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
/// </summary>
class WallCollider : public SphereHitChecker
{
public:
    /// <summary>
    /// �X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
    /// </summary>
    /// <param name="owner"></param>
    /// <param name="setFirstPos">����ȏ�̒l�ɂȂ����璵�˕Ԃ�</param>
    /// <param name="setEndPos">����ȉ��̒l�ɂȂ����璵�˕Ԃ�</param>
    WallCollider(std::shared_ptr<Actor>& owner,VECTOR setFirstPos,VECTOR setEndPos);
    /// <summary>
    /// �������������ׂ�
    /// </summary>
    /// <param name="hitCheckInfo">���ׂ��������蔻��</param>
    /// <returns>�Փˌ���</returns>
    CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo) override;
private:
    //����ȏ�̒l�ɂȂ����璵�˕Ԃ�
    VECTOR firstPos;
    //����ȉ��̒l�ɂȂ����璵�˕Ԃ�
    VECTOR endPos;
};
