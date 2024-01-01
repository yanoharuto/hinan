#include "EditorMenu.h"
#include "Utility.h"
#include "NumUI.h"
#include "UIDrawer.h"
#include "DxLib.h"
#include "UserInput.h"
#include "MouseInput.h"
#include "StageTimeLimitEditor.h"
/// <summary>
/// UIの確保
/// </summary>
EditorMenu::EditorMenu()
{
    //タイマー
    timerFrameUIData = UIManager::CreateUIData(UIKind::timerFrame);
    pointUIData = UIManager::CreateUIData(UIKind::point);
    timeUI = std::make_unique<NumUI>(UIKind::timeNum);
    //タイマーの枠の横位置
    timerFrameX = timerFrameUIData.x + timeUI->GetNumWidthSize() * 2;
    menuData = UIManager::CreateUIData(UIKind::editMenu);
    manualUIData = UIManager::CreateUIData(UIKind::editManual);
    optionsBetween += static_cast<int>(menuData.height / CONTAINER_GET_SIZE(menuData.dataHandle) * menuData.size);
}
/// <summary>
/// UIの解放
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
/// 編集画面でのメニューの更新
/// </summary>
/// <param name="input">マウス</param>
void EditorMenu::Update(std::weak_ptr<MouseInput> input)
{
    //開いているときに上下に押すと項目を変更
    if (isOpenMenu)
    {
        UpdateSelectUI(input.lock()->GetMouseX(), input.lock()->GetMouseY());
        //左クリックを押したらそのUIを開く
        if (UserInput::GetInputState(UserInput::KeyInputKind::MouseLeft)==UserInput::InputState::Push)
        {
            optionKind = static_cast<EditMenuOptions>(selectUI);
            isOpenMenu = !(optionKind == EditMenuOptions::edit);
        }
        //もう一度EscapeKeyで閉じる
        if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
        {
            optionKind = EditMenuOptions::edit;
            isOpenMenu = false;
        }
    }
    //Escapeを押したら
    else if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
    {
        //メニュー画面を開いたり閉じたり
        isOpenMenu = !isOpenMenu;
        selectUI = 0;
    }
    
}
/// <summary>
/// メニュー画面の描画
/// </summary>
/// <param name="time">時間</param>
void EditorMenu::Draw(std::weak_ptr<StageTimeLimitEditor> time) const
{
    if (isOpenMenu)
    {
        //メニューの項目を描画
        auto drawData = menuData;
        for (int i = 0; i < CONTAINER_GET_SIZE(menuData.dataHandle); i++)
        {
            if (i == selectUI)
            {
                //明るさを戻す
                auto defaultColor = Utility::MAX_ONE_BYTE_RANGE;
                SetDrawBright(defaultColor, defaultColor, defaultColor);
            }
            else
            {
                //背景を暗くする
                SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
            }
            UIDrawer::DrawRotaUI(drawData,i);
            drawData.y += optionsBetween;
        }
        //明るさを戻す
        auto defaultColor = Utility::MAX_ONE_BYTE_RANGE;
        SetDrawBright(defaultColor,defaultColor,defaultColor);

        float timeLimit = static_cast<float>(time.lock()->GetTimeLimit());
        switch (optionKind)
        {
        case EditMenuOptions::timeLimitChange:
            //タイマーの枠を描画　中央にするために
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
/// マウスでどのUIを指しているか調べる
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