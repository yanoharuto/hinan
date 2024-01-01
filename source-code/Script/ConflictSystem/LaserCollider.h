#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// Y���W�𖳎����Ă��邯�ǐ����̓����蔻��
/// </summary>
class LaserCollider : public SphereHitChecker
{
public:
    /// <summary>
    /// Y����]���郌�[�U�[�̓����蔻��
    /// </summary>
    /// <param name="obj"></param>
    /// <param name="setLineRange">������1�ɑ΂����ӂ̒���</param>
    LaserCollider(std::shared_ptr<Actor>& obj, float setLineRange);

    /// <summary>
    /// Y���W�𖳎����Ă��邯�ǐ����̓����蔻��
    /// </summary>
    /// <param name="hitCheckInfo">�������Ă���z�̏��</param>
    /// <returns></returns>
    CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo)override;
private:
    //�����̒����͍����ƌW���ɂ���Č��߂�
    float lineRange;
};

