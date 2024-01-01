#pragma once
#include <unordered_map>
#include "UIManager.h"
#define MENU_STATE_KIND_NUM 4
using namespace UIInit;
/// <summary>
/// �Q�[�����f�@�\
/// </summary>
class Menu
{
public:
    /// <summary>
    /// �eUI������
    /// </summary>
    Menu();
    /// <summary>
    /// ���j���[���J�������Ԃ�0��
    /// </summary>
    ~Menu();
    /// <summary>
    /// ���j���[�̏��
    /// </summary>
    enum class MenuOptions
    {
        //�Q�[���𑱍s�������ꍇ
        continueGame = 0,
        //��蒼�����������
        retry = 1,
        //�^�C�g���ɖ߂�
        returnTitle = 2,
        //�Q�[���I��
        exitGame = 3,
    };
    /// <summary>
    /// ���ڂ̕ύX�Ȃ�
    /// </summary>
    void Update();
    /// <summary>
    /// ���݂̃��j���[�̏��
    /// </summary>
    /// <returns>�v���C���[����蒼���������Q�[���𑱍s���������Ԃ�</returns>
    Menu::MenuOptions GetMenuState()const;
    /// <summary>
    /// ���j���[��ʂ��J���Ă��邩�ǂ���
    /// </summary>
    /// <returns>�J���Ă�����True</returns>
    bool IsMenuOpen();
    /// <summary>
    /// ���j���[��ʂ��J���Ă��鎞�Ԃ�����
    /// </summary>
    /// <returns></returns>
    static double GetOpenMenuTime();
    /// <summary>
    /// UI��`��
    /// </summary>
    void Draw()const;
private:
    /// <summary>
    /// ���j���[UI��\��
    /// </summary>
    /// <param name="option">�\������������ </param>
    void DrawUI(Menu::MenuOptions option) const;
    //���j���[��ʂ��J���Ă��鎞�Ԃ̌v��
    double startTime;
    //���j���[�̔w�i
    int backScreen;
    //�w�i�̖��邳
    int backScreenBright = 80;
    //���j���[�̏��
    static MenuOptions menuOption;
    //���j���[��ʂ��J���Ă��邩
    static bool isOpenMenu;
    //���j���[��ʂ��J���Ă���Ԃɗ����Ă��鎞��
    static double openMenuTime;
    //Menu�̊O�g
    UIData cursorUIData;
    //���j���[�̍���
    UIData uiDatas[MENU_STATE_KIND_NUM];
    //�I��
    int selectUI = 0;
};