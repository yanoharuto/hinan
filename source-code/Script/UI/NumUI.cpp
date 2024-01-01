#include "NumUI.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "UIDrawer.h"
/// <summary>
/// ������`�悷��
/// </summary>
NumUI::NumUI(UIKind kind)
{
    numUIData = UIManager::CreateUIData(kind);
    pointUIData = UIManager::CreateUIData(UIKind::point);
    pointUIData.y = numUIData.y;
    pointUIData.size = numUIData.size;
}
/// <summary>
/// UI�폜
/// </summary>
NumUI::~NumUI()
{
    UIManager::DeleteUIGraph(&numUIData);
    UIManager::DeleteUIGraph(&pointUIData);
}
/// <summary>
/// �����̕`��
/// </summary>
/// <param name="num">����</param>
void NumUI::Draw(int num) const
{
    Draw(numUIData, num);
}

/// <summary>
/// ������`�悵�������p
/// </summary>
/// <param name="x">��ԉE�[</param>
/// <param name="y">Y���W</param>
/// <param name="num">����</param>
/// <param name="scale">�����̑傫��</param>
/// <returns>���[�̍��W</returns>
int NumUI::Draw(UIData data, int num) const
{
    //����
    int digits = static_cast<int>(OriginalMath::GetDigits(num));
    //�\���ʒu���E�[�ɂ�������ړ�
    data.x -= static_cast<int> (data.size * data.width * digits);
    //�������[���ɂȂ�܂ŕ`�悷��@������`�悷��
    for (int i = digits; i > 0; i--)
    {
        //10�̂����Ŋ��������̂��܂�
        int drawNum = (static_cast<int>(num / pow(TIMER_FONT_NUM, i - 1))) % numUIData.dataHandle.size();
        //�`��
        UIDrawer::DrawRotaUI(data,drawNum);
        //�ʒu�����炷
        data.x += static_cast<int> (data.size * data.width);
        //���ɕ`�悵���������̏���
        num -= static_cast<int>(drawNum * pow(TIMER_FONT_NUM, i - 1));
    }
    return data.x;
}
/// <summary>
/// �����_���`�悵�������p
/// </summary>
/// <param name="x">��ԉE�[</param>
/// <param name="y">Y���W</param>
/// <param name="num">����</param>
/// <param name="scale">�����̑傫��</param>
/// <returns>���[�̍��W</returns>
void NumUI::Draw(float num) const
{
    //��������
    int iNum = static_cast<int>(num);
    //�������ʂ̕���
    int decimalNum1 = static_cast<int>((num - iNum) * 10);
    //������������
    int decimalNum2 = static_cast<int>(((num - iNum) * 100 - decimalNum1 * 10));
    UIData data = numUIData;
    //�`��I�������ꏊ��edge�ɓn��
    data.x = Draw(data, decimalNum2);
    data.x -= static_cast<int> (numUIData.size * numUIData.width);
    data.x = Draw(data, decimalNum1);
    data.x -= static_cast<int> (numUIData.size * numUIData.width);
    //����������`��
    Draw(data, iNum);
    data.x -= static_cast<int> (numUIData.size * numUIData.width);
    //�����_
    UIData pData = pointUIData;
    pData.x = data.x;
    UIDrawer::DrawRotaUI(pData);
}
/// <summary>
/// �ꕶ���̑傫��
/// </summary>
/// <returns></returns>
int NumUI::GetNumWidthSize()
{
    return numUIData.width;
}
