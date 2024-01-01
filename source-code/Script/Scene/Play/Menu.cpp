#include "Menu.h"
#include "UserInput.h"
#include "DxLib.h"
#include "Utility.h"
#include "GameScreen.h"
#include "UIDrawer.h"
#include "Clock.h"
//メニューの状態
Menu::MenuOptions Menu::menuOption = Menu::MenuOptions::continueGame;
//メニューを開いているか
bool Menu::isOpenMenu = false;
//メニューを開いている時間
double Menu::openMenuTime=0;
/// <summary>
/// 各UI初期化
/// </summary>
Menu::Menu()
{
    //ゲーム続行状態
    menuOption = MenuOptions::continueGame;
    //項目を移動するカーソルのUI
    cursorUIData = UIManager::CreateUIData(UIKind::menuCursor);
    //各項目のUI準備
    uiDatas[static_cast<int>(MenuOptions::continueGame)] = UIManager::CreateUIData(UIKind::playUI);
    uiDatas[static_cast<int>(MenuOptions::exitGame)] = UIManager::CreateUIData(UIKind::exitUI);
    uiDatas[static_cast<int>(MenuOptions::retry)] = UIManager::CreateUIData(UIKind::retryUI);
    uiDatas[static_cast<int>(MenuOptions::returnTitle)] = UIManager::CreateUIData(UIKind::returnTitleBottonUI);
    isOpenMenu = false;
    openMenuTime = 0;
}
/// <summary>
/// メニューを開いた時間を0に
/// </summary>
Menu::~Menu()
{
    openMenuTime = 0;
    UIManager::DeleteUIGraph(&cursorUIData);
    for (int i = 0; i < MENU_STATE_KIND_NUM; i++)
    {
        UIManager::DeleteUIGraph(&uiDatas[i]);
    }
}
/// <summary>
/// 項目の変更など
/// </summary>
void Menu::Update()
{    
    //開いているときに上下に押すと項目を変更
    if (isOpenMenu)
    {
        if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Push)
        {
            selectUI--;
            //一番上の項目からさらに上に行く場合そのまま
            if (selectUI < 0)
            {
                selectUI = 0;
            }
        }
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Push)
        {
            selectUI++;
            //一番下の項目からさらに下に行く場合そのまま
            if (selectUI >= MENU_STATE_KIND_NUM)
            {
                selectUI = MENU_STATE_KIND_NUM - 1;
            }
        }
        //移動後のカーソル
        cursorUIData.y = uiDatas[selectUI % MENU_STATE_KIND_NUM].y;

        //メニューを開いた状態でスペースキーを押したら押した項目を保存
        if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            menuOption = static_cast<MenuOptions>(selectUI);
            isOpenMenu = !(menuOption == MenuOptions::continueGame);
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
        //もう一度EscapeKeyで閉じる
        if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
        {
            menuOption = MenuOptions::continueGame;
            isOpenMenu = false;
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
    }
    //Escapeを押したら
    else if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
    {
        //メニュー画面を開いたり閉じたり
        isOpenMenu = !isOpenMenu;
        selectUI = 0;

        if (isOpenMenu)
        {
            backScreen = GameScreen::GetScreen();
            //メニュー画面を開いた時間を所得
            startTime = Clock::GetNowGameTime();
        }
        else
        {
            //メニュー画面を開いている時間を計測
            openMenuTime += Clock::GetNowGameTime() - startTime;
        }
    }
}
/// <summary>
/// 現在のメニューの状態
/// </summary>
/// <returns>プレイヤーがやり直したいかゲームを続行したいか返す</returns>
Menu::MenuOptions Menu::GetMenuState()const
{
    return menuOption;
}
/// <summary>
/// メニュー画面を開いているかどうか
/// </summary>
/// <returns>開いていたらTrue</returns>
bool Menu::IsMenuOpen()
{
    return isOpenMenu;
}
/// <summary>
/// メニュー画面を開いている時間を所得
/// </summary>
/// <returns></returns>
double Menu::GetOpenMenuTime()
{
    return openMenuTime;
}
/// <summary>
/// UIを描画
/// </summary>
void Menu::Draw() const
{
    if (isOpenMenu)
    {
        SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
        DrawGraph(0, 0, backScreen, false);
        SetDrawBright(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE);
        //各UIを描画  選択中なら二枚目の状態にする
        UIDrawer::DrawRotaUI(cursorUIData);
        DrawUI(MenuOptions::continueGame);
        DrawUI(MenuOptions::retry);
        DrawUI(MenuOptions::returnTitle);
        DrawUI(MenuOptions::exitGame);
    }
}
/// <summary>
/// メニューUIを表示
/// </summary>
/// <param name="option">表示したい項目 </param>
void Menu::DrawUI(Menu::MenuOptions state) const
{
    int menuKind = static_cast<int>(state);
    UIDrawer::DrawRotaUI(uiDatas[menuKind], selectUI == menuKind ? 0 : 1);
}