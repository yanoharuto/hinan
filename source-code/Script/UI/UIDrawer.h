#pragma once
#include "UIManager.h"
/// <summary>
/// �X�N���[���̑傫���ɂ���ĕ`��ʒu�Ƃ���ς���
/// </summary>
class UIDrawer
{
public:
    /// <summary>
    /// drawRotaGraph����ʂ̃T�C�Y�ɍ��킹�ďo����悤�ɂ���
    /// </summary>
    /// <param name="data">�`�悵����UI</param>
    /// <param name="gHIndex">�`�悵����UI�̓Y����</param>
    /// <param name="angle">UI���X����</param>
    /// <param name="trans">�����x�L���t���O</param>
    /// <returns>���s�����false</returns>
    static bool DrawRotaUI(UIData data, int gHIndex = 0, float angle = 0, bool trans = true);
    /// <summary>
    /// �X�N���[���̑z��̑傫���Ƃ̍���{���œn��
    /// </summary>
    /// <returns></returns>
    static float GetScreenRaito();
    /// <summary>
    /// ��ʃT�C�Y�������ăT�C�Y�ɂ����UI�̑傫����ύX�ł���悤�ɂ���
    /// </summary>
    UIDrawer();
    //�ʒu�ƕ�����̍\����
    struct Format
    {
        int addX;//�J�n�ʒuX
        int addY;//�J�n�ʒuY
        std::string string;//����
    };
private:
    //�X�N���[������
    static int screenWidth;
    //�X�N���[���c��
    static int screenHeight;
    //�����䗦
    static float widthRaito;
    //�c���䗦
    static float heightRaito;
    //��ʂ̑傫���䗦
    static float screenSizeRaito;
};