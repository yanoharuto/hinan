#include "EditorInput.h"
#include "UserInput.h"
#include "MouseInput.h"
#include "Utility.h"
#include "EditorUI.h"
/// <summary>
/// �ҏW�̓��͓��e��ύX
/// </summary>
EditorInput::EditorInput()
{
    inputMode = EditMode::Free;
    holdMouseX = 0;
    holdMouseY = 0;
    
}
/// <summary>
/// ���N���b�N�������Ă���Ƃ��͕ҏW������ύX�E���肷��
/// </summary>
void EditorInput::Update(std::weak_ptr<MouseInput>& input,std::weak_ptr<EditorUI>& ui)
{
    auto lockUI = ui.lock();
    auto lockInput = input.lock();
    if (lockUI == nullptr || lockInput == nullptr)return;
    //���N���b�N�����Ȃ�
    bool isPushLeft = UserInput::GetInputState(UserInput::KeyInputKind::MouseLeft) == UserInput::InputState::Push;
    inputMode = EditMode::Free;
    int x = lockInput->GetMouseX();
    int y = lockInput->GetMouseY();
    
    switch (lockUI->GetUIOnMouse(x, y))
    {
    case EditorUI::EditUIKind::time://�^�C�����~�b�g��ύX
        inputMode = EditMode::ChangeTimeLimit;
        break;
    case EditorUI::EditUIKind::faseChange://�t�F�[�Y�̕ύX
        inputMode = EditMode::ChangeFase;
        break;
    case EditorUI::EditUIKind::stagePlay://�X�e�[�W��V��
        if (isPushLeft)
        {
            inputMode = EditMode::PlayEditStage;
        }
        break;
    }
    if (inputMode != EditMode::Free) return;//�������łɉ�����UI���N���b�N���Ă�����
    //�J�����̋�����ύX
    if (UserInput::GetInputState(UserInput::KeyInputKind::MouseRight)==UserInput::InputState::Hold)
    {
        inputMode = EditMode::ScalingCameraBetween;
    }
    else if (isPushLeft)//�z�u����
    {
        inputMode = EditMode::SelectObject;
    }
    //��]������
    else if (UserInput::GetInputState(UserInput::KeyInputKind::WKey) == UserInput::InputState::Push)
    {
        inputMode = EditMode::Rotate;
    }
    //�ړ�������
    else if (UserInput::GetInputState(UserInput::KeyInputKind::SKey) == UserInput::InputState::Push)
    {
        inputMode = EditMode::Move;
    }
    //�폜����
    else if (UserInput::GetInputState(UserInput::KeyInputKind::DKey) == UserInput::InputState::Push)
    {
        inputMode = EditMode::Delete;
    }
    if (UserInput::GetInputState(UserInput::KeyInputKind::CtrKey) == UserInput::InputState::Hold)
    {
        if (UserInput::GetInputState(UserInput::KeyInputKind::ZKey) == UserInput::InputState::Push)
        {
            inputMode = EditMode::BackEditState;//�ЂƂO�ɖ߂�
        }
        if (UserInput::GetInputState(UserInput::KeyInputKind::YKey) == UserInput::InputState::Push)
        {
            inputMode = EditMode::StepEditState;//���ɖ߂�
        }
    }
}
/// <summary>
/// ����������ׂ����Ԃ��@
/// </summary>
/// <returns>����������ׂ����Ԃ�.���{�^���𒷉����Ȃ�HoldLeftButton���Ԃ�</returns>
EditorInput::EditMode EditorInput::GetEditMode() const
{
    return inputMode;
}