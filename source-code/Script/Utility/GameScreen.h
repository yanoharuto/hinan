#pragma once
#include "DxLib.h"

/// <summary>
/// �`�悵���摜��ۑ�����
/// </summary>
class GameScreen
{
public:
    /// <summary>
    /// �ۑ��ς݉摜���폜
    /// </summary>
    GameScreen();
    /// <summary>
    /// �ۑ��ς݉摜���폜
    /// </summary>
    ~GameScreen();
    /// <summary>
    /// �`�悵����ʂ�ۑ�
    /// </summary>
    void ScreenUpdate();
    /// <summary>
    /// �Ō�ɕۑ�������ʂ�n��
    /// </summary>
    /// <returns>�Ō�ɕۑ��������</returns>
    static int GetScreen()
    {
        return screen;
    }
private:
    //�Ō�ɕۑ��������
   static int screen;
};

