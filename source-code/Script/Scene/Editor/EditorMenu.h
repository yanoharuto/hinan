#pragma once
#include <memory>
#include <iostream>
#include "UIManager.h"
class NumUI;
class StageTimeLimitEditor;
class MouseInput;
constexpr int MENU_STATE_KIND_NUM = 4;
class EditorMenu
{
public:
    /// <summary>
    /// UIの確保
    /// </summary>
    EditorMenu();
    /// <summary>
    /// UIの解放
    /// </summary>
    ~EditorMenu();
    /// <summary>
    /// メニューの状態
    /// </summary>
    enum class EditMenuOptions
    {
        //編集を続行させた
        edit = 0,
        //制限時間の変更
        timeLimitChange = 1,
        //操作説明
        manual = 2,
        //タイトルに戻る
        returnTitle = 3,
    };
    /// <summary>
    /// 編集画面でのメニューの更新
    /// </summary>
    /// <param name="input">マウス</param>
    void Update(std::weak_ptr<MouseInput> input);
    /// <summary>
    /// メニュー画面の使いたい機能を渡す
    /// </summary>
    /// <returns></returns>
    EditorMenu::EditMenuOptions GetMenuState()const { return optionKind; };
    /// <summary>
    /// メニュー画面を開いているかどうか
    /// </summary>
    /// <returns>開いていたらTrue</returns>
    bool IsMenuOpen()const { return isOpenMenu; };
    /// <summary>
    /// メニュー画面の描画
    /// </summary>
    /// <param name="time">時間</param>
    void Draw(std::weak_ptr<StageTimeLimitEditor> time)const;
private:
    /// <summary>
    /// マウスでどのUIを指しているか調べる
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void UpdateSelectUI(int x, int y);
    //カーソルの縦サイズ
    int optionsBetween = 100;
    //タイマー描画位置
    int timerFrameX;
    //制限時間の数字を描画する
    std::unique_ptr<NumUI> timeUI = nullptr;
    //数字のフォント画像
    UIData timerFrameUIData;
    //小数点
    UIData pointUIData;
    //操作説明
    UIData manualUIData;
    UIData menuData;
    //メニュー画面を開いているか
    bool isOpenMenu;
    //現在押されたボタンは何か
    EditMenuOptions optionKind = EditMenuOptions::edit;
    //メニューの背景
    int backScreen;
    //背景の明るさ
    int backScreenBright = 80;
    //選択しているUI
    int selectUI = 0;
};

