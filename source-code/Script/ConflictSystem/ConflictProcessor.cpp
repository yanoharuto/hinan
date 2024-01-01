#include "ConflictProcessor.h"
#include "Actor.h"
#include "SphereHitChecker.h"
#include "ConflictManager.h"
/// <summary>
/// �Փˏ������s��
/// </summary>
/// <param name="obj">���s�������Փˏ���������I�u�W�F�N�g</param>
ConflictProcessor::ConflictProcessor(std::shared_ptr<Actor> obj)
{
    object = std::move(obj);
}
/// <summary>
/// ���s��̃I�u�W�F�N�g�����Z�b�g
/// </summary>
ConflictProcessor::~ConflictProcessor()
{
    object.reset();
}

/// <summary>
/// �����蔻��̏������Ăяo��
/// </summary>
/// <param name="resultInfo">�Փˎ��̌���</param>
void ConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //�����������̏������s��
        object->OnConflict(resultInfo);
    }
}
/// <summary>
/// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
HitCheckInfo ConflictProcessor::GetHitExamineCheckInfo() const
{
    HitCheckInfo info;
    info.SetExamineInfo(object.get());
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// �Փˏ������s���I�u�W�F�N�g���������Ȃ��Ȃ�
/// </summary>
/// <returns>�������Ȃ��Ȃ�True</returns>
bool ConflictProcessor::IsDead()
{
    return object->GetObjectState()== Object::ObjectState::dead;
}
