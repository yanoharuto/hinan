#pragma once
#include "Timer.h"
/// <summary>
/// ������x���Ԃ��v���ł���^�C�}�[
/// </summary>
class ReusableTimer final: public Timer
{
public:
    /// <summary>
    /// �v���J�n
    /// </summary>
    /// <param name="setLimitTime">�v�����鎞��</param>
    ReusableTimer(double setLimitTime);
    ///<summary>
    /// ������x�ŏ��ɐݒ肵���v�����ԕ��v���J�n
    ///</summary>
    void Reuse();
};