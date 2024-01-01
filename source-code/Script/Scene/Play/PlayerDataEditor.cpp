#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "Utility.h"
/// <summary>
/// プレイヤーの初期位置の編集
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor(InitObjKind::player)
{
    if (!editedPlacementDataVec.empty())//ファイルが空じゃなかったら編集オブジェクトに位置を渡す
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
