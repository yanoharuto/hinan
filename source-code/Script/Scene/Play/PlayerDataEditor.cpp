#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "Utility.h"
/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor(InitObjKind::player)
{
    if (!editedPlacementDataVec.empty())//�t�@�C�����󂶂�Ȃ�������ҏW�I�u�W�F�N�g�Ɉʒu��n��
    {
        for (int i = 0; i < editedPlacementDataVec.size(); i++)
        {
            if (editedPlacementDataVec[i].objKind == CAST_I(InitObjKind::player))
            {
                editObject->SetArrangementData(editedPlacementDataVec[i]);
            }
        }
    }
}
