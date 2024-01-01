#include "SpaceKeyUI.h"
#include "Utility.h"
#include "DxLib.h"
#include "UIDrawer.h"
/// <summary>
/// �_�ŕ\��������UI�������ɓn��
/// </summary>
/// <param name="uiKind"></param>
FlashUI::FlashUI(UIKind uiKind)
{
    pressKeyUIData = UIManager::CreateUIData(uiKind);
    aValue = lowtestAvalue;//�Œ�l���Z�b�g
    isAValueIncrement = true;
}
/// <summary>
/// pressKeyData�̍폜
/// </summary>
FlashUI::~FlashUI()
{
    UIManager::DeleteUIGraph(&pressKeyUIData);
}
/// <summary>
/// �A���t�@�l�̍X�V
/// </summary>
void FlashUI::Update()
{
    aValue += isAValueIncrement ? aSpeed : -aSpeed;
    if (aValue > Utility::MAX_ONE_BYTE_RANGE)//a�l���ō��l�ȏ�ɂȂ����牺����悤�ɂ���
    {
        isAValueIncrement = false;
    }
    else if (aValue < lowtestAvalue)//a�l���Œ�ɂȂ�����オ��悤�ɂ���
    {
        isAValueIncrement = true;
    }
}
/// <summary>
/// ���X�ɔ����Ȃ�����Z���Ȃ����肵�Ȃ���`��
/// </summary>
void FlashUI::Draw() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//���l��������
    UIDrawer::DrawRotaUI(pressKeyUIData,0,0,true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
}
