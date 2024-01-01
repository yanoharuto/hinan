#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UIDrawer.h"
#include "Timer.h"
/// <summary>
/// �J�E���g�_�E����UI
/// </summary>
/// <param name="setTimer">���̃^�C�}�[�̎c�莞�Ԃ�3�b�O����J�E���g�_�E������</param>
CountDown::CountDown(std::weak_ptr<Timer> setTimer)
{
	isCountDownEnd = false;
	isPlayedCountSE = false;
	countDownUIData = UIManager::CreateUIData(UIKind::countDownUI);
	endUIData = UIManager::CreateUIData(UIKind::onGameStartCountDownEnd);
	timer = setTimer;
	SoundPlayer::LoadAndInitSound(SoundKind::countDown);
}
/// <summary>
/// �^�C�}�[�̉���@UI�폜
/// </summary>
CountDown::~CountDown()
{
	timer.reset();
	UIManager::DeleteUIGraph(&countDownUIData);
	UIManager::DeleteUIGraph(&endUIData);
}

/// <summary>
/// �^�C�}�[��i�܂���UI�̐�����ύX����
/// </summary>
void CountDown::Update()
{
	switch (static_cast<int>(timer.lock()->GetRemainingTime()))//�c�肠�Ɖ��b
	{
	case 0:
		isCountDownEnd = true;
		break;
	case 1:
		uiHIndex = 0;
		break;
	case 2:
		uiHIndex = 1;
		break;
	case 3:
		if (!isPlayedCountSE)//����̓J�E���g�_�E���̉���炷
		{
			uiHIndex = 2;
			isPlayedCountSE = true;
			SoundPlayer::Play2DSE(SoundKind::countDown);
		}
		break;
	} 
}
/// <summary>
/// �J�E���g�_�E���ƏI�����UI��`��
/// </summary>
void CountDown::DrawUI()const
{
	if (isCountDownEnd)//�I����start�Ƃ�end�Ƃ��o��
	{
		UIDrawer::DrawRotaUI(endUIData);
	}
	else if (isPlayedCountSE)//3.2.1�Ɛ������o���Ă���
	{
		UIDrawer::DrawRotaUI(countDownUIData, uiHIndex);
	}
}
/// <summary>
/// �J�E���g�_�E���̉����I�������
/// </summary>
/// <returns></returns>
bool CountDown::IsPlayCountDownSound() const
{
	return SoundPlayer::IsPlaySound(SoundKind::countDown);
}
/// <summary>
/// �J�E���g�_�E���������I�������
/// </summary>
/// <returns></returns>
bool CountDown::IsCountDownEnd() const
{
	return isCountDownEnd;
}