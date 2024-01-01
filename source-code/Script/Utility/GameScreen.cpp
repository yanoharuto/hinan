#include "GameScreen.h"
#include "Utility.h"
int GameScreen::screen = -1;
/// <summary>
/// �摜��ۑ�����Ă�����폜
/// </summary>
GameScreen::GameScreen()
{
    if (screen != -1)
    {
        DeleteGraph(screen);
        screen = -1;
    }
}
/// <summary>
/// �摜��ۑ�����Ă�����폜
/// </summary>
GameScreen::~GameScreen()
{
    if (screen != -1)
    {
        DeleteGraph(screen);
        screen = -1;
    }
}
/// <summary>
/// �`�悵�Ă���摜���X�V
/// </summary>
void GameScreen::ScreenUpdate()
{
    //���ۑ����Ă����ʂ��폜
    DeleteGraph(screen);
    //���̉�ʂ�ۑ�
    screen = MakeGraph(Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, screen);
}
