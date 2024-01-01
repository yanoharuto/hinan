#include "PlayManual.h"
#include "UIDrawer.h"
/// <summary>
/// �eUI��ǂݍ���
/// </summary>
PlayManual::PlayManual()
{
	//������@�ŏo���邱�Ƃ������Ă���
    playManualUIData = UIManager::CreateUIData(UIKind::manual);
	//������@�ŉ��Ɉ����Ă���g
    sheatUIData = UIManager::CreateUIData(UIKind::playManualSheat);
	//���{�^��
	leftBUI.data = UIManager::CreateUIData(UIKind::leftButton);
	//�E�{�^��
	rightBUI.data = UIManager::CreateUIData(UIKind::rightButton);
	//�W���C�p�b�h�Ȃ�UI�ύX
	downBUI.data = UIManager::CreateUIData((UserInput::IsInputPad()) ? UIKind::xDownButton : UIKind::downButton);
}
/// <summary>
/// UI�폜
/// </summary>
PlayManual::~PlayManual()
{
	UIManager::DeleteUIGraph(&playManualUIData);
	UIManager::DeleteUIGraph(&sheatUIData);
	UIManager::DeleteUIGraph(&leftBUI.data);
	UIManager::DeleteUIGraph(&rightBUI.data);
	UIManager::DeleteUIGraph(&downBUI.data);
}
/// <summary>
/// �v���C���[�̓��͂ɂ���đ��������ς���
/// </summary>
void PlayManual::Update()
{
	//�{�^�����͏�
	leftBUI.push = UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Hold;
	rightBUI.push = UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Hold;
	//�p�b�h���g���Ă���Ή��̃{�^����ύX����
	downBUI.push = UserInput::GetInputState((UserInput::IsInputPad()) ? UserInput::KeyInputKind::Space : UserInput::KeyInputKind::Down) == UserInput::InputState::Hold;

	UIKind nextUIKind = UIKind::manual;
	//�������ɓ��͂���ƃ^�[�{��������
	if (downBUI.push)
	{
		nextUIKind = UIKind::turboManual;
	}
	//�\������UI���ύX���ꂽ��f�[�^�������Ă���
	if (nextUIKind != nowUIKind)
	{
		playManualUIData= UIManager::CreateUIData(nextUIKind);
		nowUIKind = nextUIKind;
	}
}
/// <summary>
/// ��������̕`��
/// </summary>
void PlayManual::Draw() const
{
	UIDrawer::DrawRotaUI(sheatUIData);
	UIDrawer::DrawRotaUI(playManualUIData);
	//�{�^�������Ă��牟������Ԃ�UI�ɕύX
	UIDrawer::DrawRotaUI(leftBUI.data, leftBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(rightBUI.data, rightBUI.push ? 1 : 0);
	UIDrawer::DrawRotaUI(downBUI.data, downBUI.push ? 1 : 0);
}