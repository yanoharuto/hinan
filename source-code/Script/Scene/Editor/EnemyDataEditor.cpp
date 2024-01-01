#include "EnemyDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "EditorCircleFlyShipDrawModel.h"
//�ǂݍ��ޔz�u���̃t�@�C���̃p�X
const std::string EnemyDataEditor::loadFileName = "enemyData";
/// <summary>
/// �G�̕ҏW�N���X
/// </summary>
EnemyDataEditor::EnemyDataEditor(InitObjKind enemyKind)
    :StageDataEditor(loadFileName,enemyKind)
{
    //�~�`��s���N���X�͕`����@��ύX
    if (enemyKind == InitObjKind::circleLaserShip)
    {
        SAFE_DELETE(drawer);
        drawer = new EditorCircleFlyShipDrawModel();
    }
}
