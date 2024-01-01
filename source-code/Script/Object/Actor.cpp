#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// �`����@��ύX����Ȃ�������ɓn���Ă�������
/// </summary>
/// <param name="kind"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = ObjectState::sleep;
}

/// <summary>
/// �����蔻��œ������Ă���n�����
/// </summary>
/// <returns></returns>
HitCheckInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}
