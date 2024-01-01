#include "EditorMenu.h"
#include "Utility.h"
#include "NumUI.h"
#include "UIDrawer.h"
#include "DxLib.h"
#include "UserInput.h"
#include "MouseInput.h"
#include "StageTimeLimitEditor.h"
/// <summary>
/// UI�̊m��
/// </summary>
EditorMenu::EditorMenu()
{
    //�^�C�}�[
    timerFrameUIData = UIManager::CreateUIData(UIKind::timerFrame);
    pointUIData = UIManager::CreateUIData(UIKind::point);
    timeUI = std::make_unique<NumUI>(UIKind::timeNum);
    //�^�C�}�[�̘g�̉��ʒu
    timerFrameX = timerFrameUIData.x + timeUI->GetNumWidthSize() * 2;
    menuData = UIManager::CreateUIData(UIKind::editMenu);
    manualUIData = UIManager::CreateUIData(UIKind::editManual);
    optionsBetween += static_cast<int>(menuData.height / CONTAINER_GET_SIZE(menuData.dataHandle) * menuData.size);
}
/// <summary>
/// UI�̉��
/// </summary>
EditorMenu::~EditorMenu()
{
    timeUI.reset();
    UIManager::DeleteUIGraph(&timerFrameUIData);
    UIManager::DeleteUIGraph(&pointUIData);
    UIManager::DeleteUIGraph(&manualUIData);
    UIManager::DeleteUIGraph(&menuData);
}
/// <summary>
/// �ҏW��ʂł̃��j���[�̍X�V
/// </summary>
/// <param name="input">�}�E�X</param>
void EditorMenu::Update(std::weak_ptr<MouseInput> input)
{
    //�J���Ă���Ƃ��ɏ㉺�ɉ����ƍ��ڂ�ύX
    if (isOpenMenu)
    {
        UpdateSelectUI(input.lock()->GetMouseX(), input.lock()->GetMouseY());
        //���N���b�N���������炻��UI���J��
        if (UserInput::GetInputState(UserInput::KeyInputKind::MouseLeft)==UserInput::InputState::Push)
        {
            optionKind = static_cast<EditMenuOptions>(selectUI);
            isOpenMenu = !(optionKind == EditMenuOptions::edit);
        }
        //������xEscapeKey�ŕ���
        if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
        {
            optionKind = EditMenuOptions::edit;
            isOpenMenu = false;
        }
    }
    //Escape����������
    else if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
    {
        //���j���[��ʂ��J�����������
        isOpenMenu = !isOpenMenu;
        selectUI = 0;
    }
    
}
/// <summary>
/// ���j���[��ʂ̕`��
/// </summary>
/// <param name="time">����</param>
void EditorMenu::Draw(std::weak_ptr<StageTimeLimitEditor> time) const
{
    if (isOpenMenu)
    {
        //���j���[�̍��ڂ�`��
        auto drawData = menuData;
        for (int i = 0; i < CONTAINER_GET_SIZE(menuData.dataHandle); i++)
        {
            if (i == selectUI)
            {
                //���邳��߂�
                auto defaultColor = Utility::MAX_ONE_BYTE_RANGE;
                SetDrawBright(defaultColor, defaultColor, defaultColor);
            }
            else
            {
                //�w�i���Â�����
                SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
            }
            UIDrawer::DrawRotaUI(drawData,i);
            drawData.y += optionsBetween;
        }
        //���邳��߂�
        auto defaultColor = Utility::MAX_ONE_BYTE_RANGE;
        SetDrawBright(defaultColor,defaultColor,defaultColor);

        float timeLimit = static_cast<float>(time.lock()->GetTimeLimit());
        switch (optionKind)
        {
        case EditMenuOptions::timeLimitChange:
            //�^�C�}�[�̘g��`��@�����ɂ��邽�߂�
            DrawRotaGraph(timerFrameX, timerFrameUIData.y, timerFrameUIData.size, 0, timerFrameUIData.dataHandle[0], true);
            timeUI->Draw(timeLimit);
            break;
        case EditMenuOptions::manual:
            UIDrawer::DrawRotaUI(manualUIData);
            break;
        }
    }
}
/// <summary>
/// �}�E�X�łǂ�UI���w���Ă��邩���ׂ�
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void EditorMenu::UpdateSelectUI(int x, int y)
{
    int halfWidth = menuData.width / 2;
    if (x > menuData.x - halfWidth && x < menuData.x + halfWidth)
    {
        int halfHeight = menuData.height / 2;
        for (int i = 0; i < CONTAINER_GET_SIZE(menuData.dataHandle); i++)
        {
            if (y > menuData.y - halfHeight + optionsBetween * i &&
                y < menuData.y + halfHeight + optionsBetween * i)
            {
                selectUI = i;
            }
        }
    }
}