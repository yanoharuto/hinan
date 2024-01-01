#include "DamageObject.h"
#include "ObjectObserver.h"
/// <summary>
/// ���˂����z�̈ʒu�Ƃ���������|�C���^�[����������
/// </summary>
/// <param name="kind"></param>
/// <param name="setObserver"></param>
DamageObject::DamageObject(ObjectInit::InitObjKind kind, std::unique_ptr<ObjectObserver> setObserver)
    :Actor(kind)
{
    observer = std::move(setObserver);
    tag = ObjectTag::damageObject;
}
/// <summary>
/// ���˂����I�u�W�F�N�g�̃��j�[�N�|�C���^�̊J��
/// </summary>
DamageObject::~DamageObject()
{
    observer.reset();
}