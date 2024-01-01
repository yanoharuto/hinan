#include <iostream>
#include <memory>
#include "UIManager.h"
#include "UIDrawer.h"
class NumUI;
class StageDataEditor;
/// <summary>
/// �ҏW���ɏo��UI
/// </summary>
class EditorUI
{
public:
    /// <summary>
    /// UI�̏���
    /// </summary>
    EditorUI();
    /// <summary>
    /// UI�̊J��
    /// </summary>
    ~EditorUI();
    /// <summary>
    /// �ҏW����UI�̎��
    /// </summary>
    enum class EditUIKind
    {
        faseChange,
        time,
        stagePlay,
        free
    };
    /// <summary>
    /// ���͏����Ƀ}�E�X�����ǂ�UI�̏�ɂ��邩�n��
    /// </summary>
    /// <param name="mouseX">�}�E�X�̈ʒu</param>
    /// <param name="mouseY">�}�E�X�̈ʒu</param>
    /// <returns>�������ĂȂ�������free</returns>
    EditUIKind GetUIOnMouse(int mouseX,int mouseY) const;
    /// <summary>
    /// UI�\��
    /// </summary>
    /// <param name="editor">���W�A�C�e���̐���^�C�����~�b�g������</param>
    /// <param name="input">����</param>
    void Draw(std::weak_ptr<StageDataEditor> const editor)const;
private:
    /// <summary>
    /// UI�Ƀ}�E�X���������Ă邩���ׂ�
    /// </summary>
    /// <param name="data">���ׂ�UI</param>
    /// <param name="mouseX">�}�E�X�̈ʒu</param>
    /// <param name="mouseY">�}�E�X�̈ʒu</param>
    /// <returns>�������Ă���True</returns>
    bool IsUICollider(UIData data,int mouseX,int mouseY)const;

    //���W�A�C�e���̃t���[��UI
    UIData collectFrameUIData;
    //�ҏW�����X�e�[�W��V�ԃ{�^��
    UIData playEditStageUI;
    //�ҏW���̃t�F�[�Y�̐���
    std::unique_ptr<NumUI> editFaseUI;
    //���W�A�C�e���̐���`�悷��N���X
    std::unique_ptr<NumUI> totalCollectNumUI;
};