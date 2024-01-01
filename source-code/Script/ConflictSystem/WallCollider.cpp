#include "WallCollider.h"
#include "Actor.h"
/// <summary>
/// �X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
/// </summary>
/// <param name="owner"></param>
/// <param name="setFirstPos">����ȏ�̒l�ɂȂ����璵�˕Ԃ�</param>
/// <param name="setEndPos">����ȉ��̒l�ɂȂ����璵�˕Ԃ�</param>
WallCollider::WallCollider(std::shared_ptr<Actor>& owner,VECTOR setFirstPos, VECTOR setEndPos)
    :SphereHitChecker(owner)
{
    firstPos = setFirstPos;
    endPos = setEndPos;
}

/// <summary>
/// �������������ׂ�
/// </summary>
/// <param name="hitCheckInfo"></param>
/// <returns></returns>
CollisionResultInfo WallCollider::HitCheck(HitCheckInfo hitCheckInfo)
{
    CollisionResultInfo resultInfo;//�Ԃ�l
    resultInfo.SetObjInfo(object.get());
    resultInfo.pos = hitCheckInfo.pos;
    resultInfo.hit = HitSituation::NotHit;
    //�����𑫂����ꍇ�̃|�W�V����
    VECTOR nextPos = VAdd(hitCheckInfo.pos, hitCheckInfo.velocity);
    //�����I���t���O
    bool isEndProcess = false;
    //�͈͓��ɖ߂�܂ŏ������s��
    while (!isEndProcess)
    {
        isEndProcess = true;
        //�͈͊O�ɏo�悤�Ƃ��Ă���Ȃ牟���߂�
        if (nextPos.x - hitCheckInfo.radius < firstPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.x = firstPos.x + hitCheckInfo.radius + 1;
            isEndProcess = false;
        }
        else if (nextPos.x + hitCheckInfo.radius > endPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.x = endPos.x - hitCheckInfo.radius - 1;
            isEndProcess = false;
        }
        else if (nextPos.z - hitCheckInfo.radius < firstPos.z)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.z = firstPos.z + hitCheckInfo.radius + 1;
            isEndProcess = false;
        }
        else if (nextPos.z + hitCheckInfo.radius > endPos.z)
        {
            resultInfo.hit = HitSituation::Enter;
            nextPos.z = endPos.z - hitCheckInfo.radius - 1;
            isEndProcess = false;
        }
        //������񂾈ʒu
        resultInfo.pos = nextPos;
    }
    return resultInfo;
}
