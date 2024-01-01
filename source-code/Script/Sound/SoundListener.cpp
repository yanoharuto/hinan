#include "SoundListener.h"
#include "PlayerObserver.h"
#include "Utility.h"
/// <summary>
/// 音を聞くやつのポインターを貰う
/// </summary>
/// <param name="listener"></param>
SoundListener::SoundListener(std::weak_ptr<PlayerObserver> setListener)
{
    listener = setListener;
}
/// <summary>
/// 共有ポインタをリセット
/// </summary>
SoundListener::~SoundListener()
{
    listener.reset();
}
/// <summary>
/// リスナーの位置を反映
/// </summary>
void SoundListener::Update()
{
    if (listener.expired())//リスナーが活きてたら
    {
        VECTOR position = listener.lock()->GetSubjectPos();
        Set3DSoundListenerPosAndFrontPos_UpVecY(position, VAdd(position, listener.lock()->GetSubjectDir()));
    }
}
