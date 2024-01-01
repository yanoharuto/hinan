#include "PlayGameProcess.h"
#include "ConflictManager.h"
#include "ActorControllerManager.h"
#include "GamePlayUI.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "SoundPlayer.h"
#include "PostGameEndStagingProcess.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "StopTimer.h"

/// <summary>
/// BGM�ƃQ�[���I���^�C�}�[���N��
/// </summary>
/// <param name="player">UI�Ƀv���C���[����n��</param>
/// <param name="collectItemObserver">UI�Ɏ��W�A�C�e������n��</param>
PlayGameProcess::PlayGameProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<CollectItemObserver> const collectItemObserver)
{
	timer = StageDataManager::CreateGameTimer();
	playUI = new GamePlayUI(player, timer, collectItemObserver);
	SoundPlayer::LoadAndInitSound(SoundKind::playBGM);
}
/// <summary>
/// UI�ƃ^�C�}�[�̉��
/// </summary>
PlayGameProcess::~PlayGameProcess()
{
	SAFE_DELETE(playUI);
	timer.reset();
}
/// <summary>
/// �V��ł���Ƃ��̍X�V
/// </summary>
/// <param name="collectObserver">���W�A�C�e���̎c�萔�������Ă��炤</param>
void PlayGameProcess::Update(std::weak_ptr<CollectItemObserver> const collectObserver)
{
	if (isFirstUpdate)//����Ȃ�^�C�}�[�ċN��
	{
		timer->Reset();
		isFirstUpdate = false;
	}
	//���W�A�C�e�����S�������I�����,�������Ԃ��I�[�o�[�����Ȃ�I��
	if (collectObserver.lock()->GetRemainingItemNum() == 0 || timer->IsOverLimitTime())
	{
		isEndProcess = true;
	}
	//�Ō�̈����������Ȃ�^�C�}�[���~�߂�
	if (collectObserver.lock()->IsCollectLastOne())
	{
		//�^�C�}�[�X�g�b�v
		timer->Stop();
	}
	//BGM�����ĂȂ�������Đ�
	if (!SoundPlayer::IsPlaySound(SoundKind::playBGM))
	{
		SoundPlayer::Play2DSE(SoundKind::playBGM);
	}
	playUI->Update();
}
/// <summary>
/// �`��
/// </summary>
void PlayGameProcess::Draw() const
{
	playUI->Draw();
}
/// <summary>
/// �Q�[���̎c�莞�ԃ^�C�}�[��n��
/// </summary>
/// <returns> �Q�[���̎c�莞�ԃ^�C�}�[��n��</returns>
std::shared_ptr<Timer> PlayGameProcess::GetGameTimer()
{
	return timer;
};
