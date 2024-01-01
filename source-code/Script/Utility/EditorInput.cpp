#include "EditorInput.h"
#include "UserInput.h"
#include "MouseInput.h"
#include "Utility.h"

/// <summary>
/// �ҏW�̓��͓��e��ύX
/// </summary>
EditorInput::EditorInput()
{
    leftMode = EditMode::Free;
    holdMouseX = 0;
    holdMouseY = 0;
    playEditStageUI = UIManager::CreateUIData(UIKind::playEditStage);
}
/// <summary>
/// ���N���b�N�������Ă���Ƃ��͕ҏW������ύX�E���肷��
/// </summary>
void EditorInput::Update(std::weak_ptr<MouseInput> input)
{
    auto state = UserInput::GetInputState(UserInput::KeyInputKind::MouseLeft);
    int x = input.lock()->GetMouseX();
    int y = input.lock()->GetMouseY();
    switch (state)
    {
        //�z�u���폜�����Ȃ�Delete
    case UserInput::InputState::Free:
        if (!isEditObject)
        {
            leftMode = EditMode::Free;
        }
        else//�ҏW���Ȃ�ړ����[�h����]���[�h��
        {
            leftMode = isRotateMode ? EditMode::Rotate : EditMode::Move;
        }
        break;
        //�}�E�X�̈ʒu���X�V �I�u�W�F�N�g��I���������͔z�u
    case UserInput::InputState::Push:
        holdMouseX = x;
        holdMouseY = y;
        leftMode = isEditObject ? leftMode : EditMode::SelectObject;
        //�ҏW�����X�e�[�W��V�ԃ{�^�����N���b�N������I��
        x = playEditStageUI.width / 2;
        y = playEditStageUI.width / 2;
        if (holdMouseX > playEditStageUI.x - x && holdMouseX < playEditStageUI.x +  x&&
            holdMouseY > playEditStageUI.y - y && holdMouseY < playEditStageUI.y + y)
        {
            leftMode = EditMode::PlayEditStage;
        }
        break;
        //�I�������o��
    case UserInput::InputState::Hold:
        HoldChangeLeftMode(x, y);
        isLeftHold = true;
        break;
        //�ҏW���[�h�ɓ�������isEditObject��True�ɂȂ�
    case UserInput::InputState::Detach:
        isLeftHold = false;
        isRotateMode = leftMode == EditMode::Rotate;
        isEditObject = leftMode != EditMode::Put && leftMode != EditMode::Delete;
        break;
    default:
        break;
    }

    state = UserInput::GetInputState(UserInput::KeyInputKind::MouseRight);
    switch (state)
    {
    case UserInput::InputState::Push:
        holdMouseX = x;
        holdMouseY = y;
        break;
    case UserInput::InputState::Hold:
        isRightHold = true;
        HoldChangeRightMode(x,y);
        break;
    default:
        isRightHold = false;
        break;
    }
}
/// <summary>
/// ����������ׂ����Ԃ��@
/// </summary>
/// <returns>����������ׂ����Ԃ�.���{�^���𒷉����Ȃ�HoldLeftButton���Ԃ�</returns>
EditorInput::EditMode EditorInput::GetEditMode() const
{
    if (isRightHold)
    {
        return rightMode;
    }
    else
    {
        return isLeftHold ? EditMode::HoldButton : leftMode;
    }
}
/// <summary>
/// ��������̕`��
/// </summary>
void EditorInput::Draw() const
{
    if(isLeftHold)
    {
        switch (leftMode)//�����������ɍ��E�㉺�ɓ������Ƃ��̐�����
        {
        case EditMode::Move:
        case EditMode::Rotate:
            if (isRotateMode)//��]���[�h���͈ړ����[�h�ɐ؂�ւ��
            {
                DrawFormat(manual[CAST_I(EditMode::Move)]);
            }
            else
            {
                DrawFormat(manual[CAST_I(EditMode::Rotate)]);
            }
            break;
        case EditMode::BackPrevState:
            DrawFormat(manual[CAST_I(EditMode::BackPrevState)]);
            break;
        case EditMode::Put:
            DrawFormat(manual[CAST_I(EditMode::Put)]);
            break;
        case EditMode::Delete:
            DrawFormat(manual[CAST_I(EditMode::Delete)]);
            break;
        case EditMode::HoldButton:
            if (isRotateMode)//��]���[�h���͈ړ����[�h�ɐ؂�ւ��
            {
                DrawFormat(manual[CAST_I(EditMode::Move)]);
            }
            else
            {
                DrawFormat(manual[CAST_I(EditMode::Rotate)]);
            }
            DrawFormat(manual[CAST_I(EditMode::ChangeFase)]);
            DrawFormat(manual[CAST_I(EditMode::Put)]);
            DrawFormat(manual[CAST_I(EditMode::Delete)]);
            break;
        default:
            break;
        }
    }
    if(isRightHold)
    {
        switch (rightMode)//�E���������ɍ��E�㉺�ɓ������Ƃ��̐�����
        {
        case EditMode::ChangeTimeLimit:
            DrawFormat(manual[CAST_I(EditMode::ChangeTimeLimit)]);
            break;
        case EditMode::ChangeFase:
            DrawFormat(manual[CAST_I(EditMode::ChangeFase)]);
            break;
        case EditMode::ScalingCamera:
            DrawFormat(manual[CAST_I(EditMode::ScalingCamera)]);
            break;
        case EditMode::HoldButton:
            DrawFormat(manual[CAST_I(EditMode::ChangeTimeLimit)]);
            DrawFormat(manual[CAST_I(EditMode::ChangeFase)]);
            DrawFormat(manual[CAST_I(EditMode::ScalingCamera)]);
            break;
        default:
            break;
        }
    }
    //�ҏW�����X�e�[�W��V��UI
    UIDrawer::DrawRotaUI(playEditStageUI);
}
/// <summary>
/// �}�E�X����ŕҏW������e��ς���
/// </summary>
void EditorInput::HoldChangeLeftMode(int mouseX, int mouseY)
{
    mouseX -= holdMouseX;
    mouseY -= holdMouseY;
    leftMode = EditMode::HoldButton;
    //���͖���
    //�}�E�X�̏㉺���E�ŕҏW���e��ς���
    if (abs(mouseX) > abs(mouseY) && abs(mouseX) > INPUT_RANGE)
    {
        if (mouseX < -INPUT_RANGE)//���Ƀ}�E�X�����炷�Ɖ�]�ƈړ���؂�ւ���
        {
            //��]���[�h�ƈړ����[�h��؂�ւ���
            leftMode = isRotateMode ? EditMode::Move : EditMode::Rotate;
        }
        if (mouseX > INPUT_RANGE)//�E�ɂ��炷�ƂЂƂO�̏�Ԃɖ߂�
        {
            leftMode = EditMode::BackPrevState;
        }
    }
    else if (abs(mouseY) > INPUT_RANGE)
    {
        //�z�u.�Ĕz�u
        if (mouseY > -INPUT_RANGE)
        {
            leftMode = EditMode::Delete;
        }
        //�ĕҏW.�ĕҏW���̂��̂�j��
        else if (mouseY < INPUT_RANGE)
        {
            leftMode = EditMode::Put;
        }
    }
}
/// <summary>
/// �E�{�^���������ŕҏW������e��ς���
/// </summary>
void EditorInput::HoldChangeRightMode(int mouseX, int mouseY)
{
    mouseX -= holdMouseX;
    mouseY -= holdMouseY;
    rightMode = EditMode::HoldButton;
    //���͖���
    //�}�E�X�̏㉺���E�ŕҏW���e��ς���
    if (abs(mouseX) > abs(mouseY) && abs(mouseX) > INPUT_RANGE)
    {
        if (mouseX < -INPUT_RANGE)//���Ƀ}�E�X�����炷�Ɖ�]�ƈړ���؂�ւ���
        {
            //��]���[�h�ƈړ����[�h��؂�ւ���
            rightMode = EditMode::ChangeTimeLimit;
        }
        if (mouseX > INPUT_RANGE)//�E�ɂ��炷�Əo�Ă���i�K��ύX�ł���悤�ɂȂ�
        {
            rightMode = EditMode::ChangeFase;
        }
    }
    else if (abs(mouseY) > INPUT_RANGE)
    {
        //�z�u.�Ĕz�u
        if (mouseY > -INPUT_RANGE)
        {
            rightMode = EditMode::ScalingCamera;
        }
    }
}
/// <summary>
/// �}�E�X���{�^�����������Ȃ瑀�����
/// </summary>
void EditorInput::DrawFormat(UIDrawer::Format format)const
{
    DrawFormatString(format.addX + holdMouseX, format.addY + holdMouseY, formatColor, format.string.c_str());
}