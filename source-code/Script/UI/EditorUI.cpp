#include "EditorUI.h"
#include "NumUI.h"
#include "TimerUI.h"
#include "Utility.h"
#include "StageDataEditor.h"

/// <summary>
/// UIの所得
/// </summary>
EditorUI::EditorUI()
{
    //編集中のフェーズの数字
    editFaseUI = std::make_unique<NumUI>(UIKind::getCollectItemNum);
    totalCollectNumUI = std::make_unique<NumUI>(UIKind::allCollectItemNum);
    
    //収集アイテムに関するUIの枠
    collectFrameUIData = UIManager::CreateUIData(UIKind::collectItemFrameUI);

    playEditStageUI = UIManager::CreateUIData(UIKind::playEditStage);
}
/// <summary>
/// UIの開放
/// </summary>
EditorUI::~EditorUI()
{
    editFaseUI.reset();
    totalCollectNumUI.reset();
    UIManager::DeleteUIGraph(&collectFrameUIData);
    UIManager::DeleteUIGraph(&playEditStageUI);
}
/// <summary>
/// 入力処理にマウスが今どのUIの上にいるか渡す
/// </summary>
/// <param name="mouseX">マウスの位置</param>
/// <param name="mouseY">マウスの位置</param>
/// <returns>当たってなかったらfree</returns>
EditorUI::EditUIKind EditorUI::GetUIOnMouse(int mouseX, int mouseY)const
{
    if (IsUICollider(collectFrameUIData, mouseX, mouseY)) return EditUIKind::faseChange;
    if (IsUICollider(playEditStageUI, mouseX, mouseY)) return EditUIKind::stagePlay;
    return EditUIKind::free;
}
/// <summary>
/// UI表示
/// </summary>
/// <param name="editor">収集アイテムの数やタイムリミットを所得</param>
/// <param name="input">入力</param>
void EditorUI::Draw(std::weak_ptr<StageDataEditor> const editor)const
{
    //収集アイテムの数等を表示
    UIDrawer::DrawRotaUI(collectFrameUIData);
    //収集アイテムの数
    totalCollectNumUI->Draw(editor.lock()->GetCollectNum());
    editFaseUI->Draw(editor.lock()->GetApperFaseNum());   //編集したステージを遊ぶUI
    UIDrawer::DrawRotaUI(playEditStageUI);
}
/// <summary>
/// UIにマウスが当たってるか調べる
/// </summary>
/// <param name="data">調べるUI</param>
/// <param name="mouseX">マウスの位置</param>
/// <param name="mouseY">マウスの位置</param>
/// <returns>当たってたらTrue</returns>
bool EditorUI::IsUICollider(UIData data, int mouseX, int mouseY)const
{
    int width = data.width / 2;
    int height = data.height / 2;
    //範囲内ならTrue
    return mouseX > data.x - width && mouseX < data.x + width &&
        mouseY > data.y - height && mouseY < data.y + height;
}
