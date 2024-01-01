#include "EditManual.h"
#include "Utility.h"
#include "DxLib.h"
#include "UIDrawer.h"
#include "StageDataEditor.h"

/// <summary>
/// �t�H���g�T�C�Y�ƕ\���ʒu�̒���
/// </summary>
EditManual::EditManual()
{
    screenHeight = static_cast<int>(Utility::SCREEN_HEIGHT * UIDrawer::GetScreenRaito() - fontSize);
    SetFontSize(fontSize);
}
/// <summary>
/// �ҏW��������\��
/// </summary>
void EditManual::DrawEditManualString() const
{
    //�`�敶��Y���W
    int charY = screenHeight - strBetweenY;
    //�`�敶��X���W
    int charX = strBetweenX;
    //�\���ҏW��������
    DrawManualString(editCrossAction, charX, charY);
    charX = GetNextDrawX(editCrossAction, charX);
    //SpaceKey�ҏW��������
    DrawManualString(editSpaceKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //WKey�̖�������
    DrawManualString(wKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //���s
    charY -= strBetweenY;
    charX = strBetweenX;
    //���ʕ`�揈��
    DrawCommonString(charX, charY);
}
/// <summary>
/// ����ҏW���邩�I�𒆂̑�������\��
/// </summary>
void EditManual::DrawSelectManualString() const
{
    //�`�敶��Y���W
    int charY = screenHeight - strBetweenY;
    //�`�敶��X���W
    int charX = strBetweenX;
    //�\���I�𒆐�����
    DrawManualString(selectCrossKeyAction, charX, charY);
    charX = GetNextDrawX(selectCrossKeyAction, charX);
    //SpaceKey�I�𒆐�����
    DrawManualString(selectSpaceKeyAction, charX, charY);
    charX = GetNextDrawX(selectSpaceKeyAction, charX);
    //���s
    charY -= strBetweenY;
    charX = strBetweenX;
    //���ʕ`�揈��
    DrawCommonString(charX, charY);
}
/// <summary>
/// �ҏW�����I�𒆂ł��`�悷�鑀�����
/// </summary>
/// <param name="x">�`��J�nX</param>
/// <param name="y">�`��J�nY</param>
void EditManual::DrawCommonString(int x, int y) const
{
    //�J���������폜���@
    //AKey�̖�������
    DrawManualString(aKeyAction, x, y);
    x = GetNextDrawX(editSpaceKeyAction, x);
    //DKey�̖�������
    DrawManualString(dKeyAction, x, y);
    x = GetNextDrawX(editSpaceKeyAction, x);
    //ESCKey�̖�������
    DrawManualString(escKeyAction, x, y);
    x = GetNextDrawX(editSpaceKeyAction, x);
    //SKey�̖�������
    DrawManualString(sKeyAction, x, y);
}
/// <summary>
/// �����������X�̏ꏊ�����߂�
/// </summary>
/// <param name="prevStr">���O�ɏ���������</param>
/// <param name="nowX">����X���W</param>
/// <returns>���ɏ����ׂ�X���W</returns>
int EditManual::GetNextDrawX(std::string prevStr, int nowX)const
{
    return static_cast<int>(prevStr.size()) * fontSize + strBetweenX + nowX;
}
/// <summary>
/// �������̕`��
/// </summary>
/// <param name="drawStr">������</param>
/// <param name="x">�`��ʒuX</param>
/// <param name="y">�`��ʒuY</param>
void EditManual::DrawManualString(std::string drawStr, int x, int y)const
{
    DrawString(x, y, drawStr.c_str(), GetColor(0, 0, 0));
}