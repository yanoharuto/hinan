#pragma once
//fps
#define FLAME 60
/// <summary>
/// �Q�[�����̎��Ԃ��X�V
/// </summary>
class Clock
{
public:
    /// <summary>
    /// �Q�[���J�n�̏u�Ԃ�ۑ�
    /// </summary>
    Clock();
    /// <summary>
    /// �^�C�}�[���X�V����
    /// </summary>
    void Update();
    /// <summary>
    /// �Q�[���̌o�ߎ��Ԃ�1000m�b�ɂ��ēn��
    /// </summary>
    /// <returns></returns>
    static double GetNowGameTime();
private:
    //1000m�b
    double timeD;
    //���ʂ̌o�ߕb��
    static double gameTime;
};