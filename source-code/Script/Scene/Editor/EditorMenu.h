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
    /// UI�̊m��
    /// </summary>
    EditorMenu();
    /// <summary>
    /// UI�̉��
    /// </summary>
    ~EditorMenu();
    /// <summary>
    /// ���j���[�̏��
    /// </summary>
    enum class EditMenuOptions
    {
        //�ҏW�𑱍s������
        edit = 0,
        //�������Ԃ̕ύX
        timeLimitChange = 1,
        //�������
        manual = 2,
        //�^�C�g���ɖ߂�
        returnTitle = 3,
    };
    /// <summary>
    /// �ҏW��ʂł̃��j���[�̍X�V
    /// </summary>
    /// <param name="input">�}�E�X</param>
    void Update(std::weak_ptr<MouseInput> input);
    /// <summary>
    /// ���j���[��ʂ̎g�������@�\��n��
    /// </summary>
    /// <returns></returns>
    EditorMenu::EditMenuOptions GetMenuState()const { return optionKind; };
    /// <summary>
    /// ���j���[��ʂ��J���Ă��邩�ǂ���
    /// </summary>
    /// <returns>�J���Ă�����True</returns>
    bool IsMenuOpen()const { return isOpenMenu; };
    /// <summary>
    /// ���j���[��ʂ̕`��
    /// </summary>
    /// <param name="time">����</param>
    void Draw(std::weak_ptr<StageTimeLimitEditor> time)const;
private:
    /// <summary>
    /// �}�E�X�łǂ�UI���w���Ă��邩���ׂ�
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void UpdateSelectUI(int x, int y);
    //�J�[�\���̏c�T�C�Y
    int optionsBetween = 100;
    //�^�C�}�[�`��ʒu
    int timerFrameX;
    //�������Ԃ̐�����`�悷��
    std::unique_ptr<NumUI> timeUI = nullptr;
    //�����̃t�H���g�摜
    UIData timerFrameUIData;
    //�����_
    UIData pointUIData;
    //�������
    UIData manualUIData;
    UIData menuData;
    //���j���[��ʂ��J���Ă��邩
    bool isOpenMenu;
    //���݉����ꂽ�{�^���͉���
    EditMenuOptions optionKind = EditMenuOptions::edit;
    //���j���[�̔w�i
    int backScreen;
    //�w�i�̖��邳
    int backScreenBright = 80;
    //�I�����Ă���UI
    int selectUI = 0;
};

