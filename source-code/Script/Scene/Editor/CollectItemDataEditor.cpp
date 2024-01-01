#include "CollectItemDataEditor.h"
#include "EditorObject.h"
#include "UserInput.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "CameraObserver.h"
//�ǂݍ��ޔz�u���̏����Ă���t�@�C���̃p�X
const std::string CollectItemDataEditor::loadFileName = "collectData";
/// <summary>
/// ���W�A�C�e���̕ҏW����N���X
/// </summary>
CollectItemDataEditor::CollectItemDataEditor()
    :StageDataEditor(loadFileName,InitObjKind::collect)
{
}
/// <summary>
/// �e�N���X�Ɠ����X�V�Ǝ��W�A�C�e���̐����X�V����
/// </summary>
void CollectItemDataEditor::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    //�e�N���X�Ɠ����X�V
    StageDataEditor::Update(cameraObserever);


}
/// <summary>
/// �ҏW����ҏW���I�����I�u�W�F�N�g�̕`��
/// </summary>
void CollectItemDataEditor::Draw() const
{
    StageDataEditor::Draw();
    
    //���W�A�C�e���̐�
    DrawString(0, drawCollectNumY, std::to_string(collectNum).c_str(), GetColor(0, 0, 0));
    //�~�b�V�����̐�
    DrawString(0, drawEditedCollectNumY, std::to_string(getCollectNum).c_str(), GetColor(0, 0, 0));
}
 