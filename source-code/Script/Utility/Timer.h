#pragma once
/// <summary>
/// ���߂�ꂽ���Ԑi�񂾂肷��
/// </summary>
class Timer
{
public:
    /// <summary>
    /// �������ԓ����v������
    /// </summary>
    /// <param name="setLimitTime">�v������������</param>
    Timer(double setLimitTime);
    /// <summary>
    /// �ݒ莞�Ԃ��߂�����
    /// </summary>
    /// <returns>�߂�����True</returns>
    bool IsOverLimitTime()const;
    /// <summary>
    /// �o�ߎ���
    /// </summary>
    /// <returns>���b�o������</returns>
    virtual double GetElaspedTime()const;
    /// <summary>
    /// �^�C�}�[�ɐݒ肳�ꂽ����
    /// </summary>
    /// <returns>�^�C�}�[�ɐݒ肳�ꂽ���Ԃ�Ԃ�</returns>
    double GetLimitTime()const;
    /// <summary>
    /// �c�莞�Ԃ�����
    /// </summary>
    /// <returns>���Ɖ��b���Ԃ��c���Ă��邩</returns>
    double GetRemainingTime()const;
protected:
    //��������
    double limitTime = 0;
    //�v���J�n����
    double startTime = 0;
};