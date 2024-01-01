#pragma once
#include <string>
class StageDataEditor;
/// <summary>
/// �ҏW���̑������
/// </summary>
class EditManual final
{
public:
    /// <summary>
    /// �t�H���g�T�C�Y�ƕ\���ʒu�̒���
    /// </summary>
    EditManual();
    /// <summary>
    /// �ҏW��������\��
    /// </summary>
    void DrawEditManualString()const;
    /// <summary>
    /// ����ҏW���邩�I�𒆂̑�������\��
    /// </summary>
    void DrawSelectManualString()const;
private:
    /// <summary>
    /// �ҏW�����I�𒆂ł��`�悷�鑀�����
    /// </summary>
    /// <param name="x">�`��J�nX</param>
    /// <param name="y">�`��J�nY</param>
    void DrawCommonString(int x, int y)const;
    /// <summary>
    /// �����������X�̏ꏊ�����߂�
    /// </summary>
    /// <param name="prevStr">���O�ɏ���������</param>
    /// <param name="nowX">����X���W</param>
    /// <returns>���ɏ����ׂ�X���W</returns>
    int GetNextDrawX(std::string prevStr, int nowX)const;
    /// <summary>
    /// �������̕`��
    /// </summary>
    /// <param name="drawStr">������</param>
    /// <param name="x">�`��ʒuX</param>
    /// <param name="y">�`��ʒuY</param>
    void DrawManualString(std::string drawStr,int x,int y)const;
    //�\���ҏW��
    const std::string selectCrossKeyAction="�\���L�[�ҏW���ύX";
    //�\���I��
    const std::string editCrossAction="�\���L�[�ҏW���ړ�";
    //SpaceKey�I��
    const std::string selectSpaceKeyAction="space�ŕҏW�J�n";
    //SpaceKey�ҏW��
    const std::string editSpaceKeyAction="space�Ŕz�u";
    //DKey�̖�������
    const std::string dKeyAction="D�ō폜";
    //WKey�̖�������
    const std::string wKeyAction="�����ύX";
    //AKey�̖�������
    const std::string aKeyAction="A�Ə\���ŃJ��������";
    //SKey�̖�������
    const std::string sKeyAction="S�Ə\���ŏo�Ă��鎞����ύX";
    //ESCKey�̖�������
    const std::string escKeyAction="ESC�Ń��j���[";
    //�\���ʒu�̍���
    int screenHeight;
    //�`�悷�镶���̃T�C�Y
    const int fontSize = 24;
    //������̋���Y
    const int strBetweenY = 50;
    //������̋���X
    const int strBetweenX = 50;

};

