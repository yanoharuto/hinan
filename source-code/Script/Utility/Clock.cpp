#include "Clock.h"
#include "DxLib.h"
#include "Utility.h"
#include "Menu.h"
//�o�ߕb��
double Clock::gameTime;
/// <summary>
/// �Q�[���J�n�̏u�Ԃ�ۑ�
/// </summary>
Clock::Clock()
{
    // ���݂̃J�E���g���擾����
    timeD = static_cast<double>(GetNowHiPerformanceCount());
    gameTime = static_cast<double>(GetNowHiPerformanceCount()) / 1000000;
}
/// <summary>
/// �^�C�}�[���X�V����
/// </summary>
void Clock::Update()
{
    // �P�V�~���b(��b�ԂU�O�t���[�����������̂P�t���[��������̌o�ߎ���)
   double temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
   // �o�߂���܂ł����ő҂�
    while (temp < Utility::DELTATIME)
    {
        temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    }

    // ���݂̃J�E���g���擾����
    timeD =  static_cast<double>(GetNowHiPerformanceCount());
    
    gameTime = timeD / 1000000;
}
/// <summary>
/// �Q�[���̌o�ߎ��Ԃ�1000m�b�ɂ��ēn��
/// </summary>
/// <returns></returns>
double Clock::GetNowGameTime()
{
    return gameTime - Menu::GetOpenMenuTime();
}
