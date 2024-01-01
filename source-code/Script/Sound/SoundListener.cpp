#include "SoundListener.h"
#include "PlayerObserver.h"
#include "Utility.h"
/// <summary>
/// ���𕷂���̃|�C���^�[��Ⴄ
/// </summary>
/// <param name="listener"></param>
SoundListener::SoundListener(std::weak_ptr<PlayerObserver> setListener)
{
    listener = setListener;
}
/// <summary>
/// ���L�|�C���^�����Z�b�g
/// </summary>
SoundListener::~SoundListener()
{
    listener.reset();
}
/// <summary>
/// ���X�i�[�̈ʒu�𔽉f
/// </summary>
void SoundListener::Update()
{
    if (listener.expired())//���X�i�[�������Ă���
    {
        VECTOR position = listener.lock()->GetSubjectPos();
        Set3DSoundListenerPosAndFrontPos_UpVecY(position, VAdd(position, listener.lock()->GetSubjectDir()));
    }
}
