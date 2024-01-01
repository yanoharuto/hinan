#include "EditorUI.h"
#include "NumUI.h"
#include "TimerUI.h"
#include "Utility.h"
#include "StageDataEditor.h"

/// <summary>
/// UI�̏���
/// </summary>
EditorUI::EditorUI()
{
    //�ҏW���̃t�F�[�Y�̐���
    editFaseUI = std::make_unique<NumUI>(UIKind::getCollectItemNum);
    totalCollectNumUI = std::make_unique<NumUI>(UIKind::allCollectItemNum);
    
    //���W�A�C�e���Ɋւ���UI�̘g
    collectFrameUIData = UIManager::CreateUIData(UIKind::collectItemFrameUI);

    playEditStageUI = UIManager::CreateUIData(UIKind::playEditStage);
}
/// <summary>
/// UI�̊J��
/// </summary>
EditorUI::~EditorUI()
{
    editFaseUI.reset();
    totalCollectNumUI.reset();
    UIManager::DeleteUIGraph(&collectFrameUIData);
    UIManager::DeleteUIGraph(&playEditStageUI);
}
/// <summary>
/// ���͏����Ƀ}�E�X�����ǂ�UI�̏�ɂ��邩�n��
/// </summary>
/// <param name="mouseX">�}�E�X�̈ʒu</param>
/// <param name="mouseY">�}�E�X�̈ʒu</param>
/// <returns>�������ĂȂ�������free</returns>
EditorUI::EditUIKind EditorUI::GetUIOnMouse(int mouseX, int mouseY)const
{
    if (IsUICollider(collectFrameUIData, mouseX, mouseY)) return EditUIKind::faseChange;
    if (IsUICollider(playEditStageUI, mouseX, mouseY)) return EditUIKind::stagePlay;
    return EditUIKind::free;
}
/// <summary>
/// UI�\��
/// </summary>
/// <param name="editor">���W�A�C�e���̐���^�C�����~�b�g������</param>
/// <param name="input">����</param>
void EditorUI::Draw(std::weak_ptr<StageDataEditor> const editor)const
{
    //���W�A�C�e���̐�����\��
    UIDrawer::DrawRotaUI(collectFrameUIData);
    //���W�A�C�e���̐�
    totalCollectNumUI->Draw(editor.lock()->GetCollectNum());
    editFaseUI->Draw(editor.lock()->GetApperFaseNum());   //�ҏW�����X�e�[�W��V��UI
    UIDrawer::DrawRotaUI(playEditStageUI);
}
/// <summary>
/// UI�Ƀ}�E�X���������Ă邩���ׂ�
/// </summary>
/// <param name="data">���ׂ�UI</param>
/// <param name="mouseX">�}�E�X�̈ʒu</param>
/// <param name="mouseY">�}�E�X�̈ʒu</param>
/// <returns>�������Ă���True</returns>
bool EditorUI::IsUICollider(UIData data, int mouseX, int mouseY)const
{
    int width = data.width / 2;
    int height = data.height / 2;
    //�͈͓��Ȃ�True
    return mouseX > data.x - width && mouseX < data.x + width &&
        mouseY > data.y - height && mouseY < data.y + height;
}
