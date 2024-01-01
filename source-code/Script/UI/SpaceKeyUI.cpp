#include "SpaceKeyUI.h"
#include "Utility.h"
#include "DxLib.h"
#include "UIDrawer.h"
/// <summary>
/// 点滅表示したいUIを引数に渡す
/// </summary>
/// <param name="uiKind"></param>
FlashUI::FlashUI(UIKind uiKind)
{
    pressKeyUIData = UIManager::CreateUIData(uiKind);
    aValue = lowtestAvalue;//最低値をセット
    isAValueIncrement = true;
}
/// <summary>
/// pressKeyDataの削除
/// </summary>
FlashUI::~FlashUI()
{
    UIManager::DeleteUIGraph(&pressKeyUIData);
}
/// <summary>
/// アルファ値の更新
/// </summary>
void FlashUI::Update()
{
    aValue += isAValueIncrement ? aSpeed : -aSpeed;
    if (aValue > Utility::MAX_ONE_BYTE_RANGE)//a値が最高値以上になったら下げるようにする
    {
        isAValueIncrement = false;
    }
    else if (aValue < lowtestAvalue)//a値が最低になったら上がるようにする
    {
        isAValueIncrement = true;
    }
}
/// <summary>
/// 徐々に薄くなったり濃くなったりしながら描画
/// </summary>
void FlashUI::Draw() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//α値をいじる
    UIDrawer::DrawRotaUI(pressKeyUIData,0,0,true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
}
