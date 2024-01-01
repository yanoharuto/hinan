#include "EditorManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "UserInput.h"
#include "EffekseerForDXLib.h"
#include "EditManual.h"
#include "EditorEffect.h"
#include "CameraObserver.h"
#include "EditorCircleFlyShipDrawModel.h"
#include "EditorDrawModel.h"
#include "InitObjKind.h"
/// <summary>
/// �ҏW�ɕK�v�Ȃ��̂��m��
/// </summary>
EditorDrawModelManager::EditorDrawModelManager()
{
    drawModelMap.insert(std::make_pair(ObjectInit::InitObjKind::player,new EditorDrawModel(ObjectInit::InitObjKind::player)));
    drawModelMap.insert(std::make_pair(ObjectInit::InitObjKind::saw,new EditorDrawModel(ObjectInit::InitObjKind::saw)));
    drawModelMap.insert(std::make_pair(ObjectInit::InitObjKind::moveSaw,new EditorDrawModel(ObjectInit::InitObjKind::moveSaw)));
    drawModelMap.insert(std::make_pair(ObjectInit::InitObjKind::bomberShip,new EditorDrawModel(ObjectInit::InitObjKind::bomberShip)));
    drawModelMap.insert(std::make_pair(ObjectInit::InitObjKind::upDownLaserShip,new EditorDrawModel(ObjectInit::InitObjKind::upDownLaserShip)));
    drawModelMap.insert(std::make_pair(ObjectInit::InitObjKind::collect,new EditorDrawModel(ObjectInit::InitObjKind::collect)));
    drawCircleFlyShip = new EditorCircleFlyShipDrawModel();
}
/// <summary>
/// �ҏW����X�e�[�W�̔w�i�Ȃǂ����
/// </summary>
EditorDrawModelManager::~EditorDrawModelManager()
{
    SAFE_DELETE(drawCircleFlyShip);
}
/// <summary>
/// �����̈ʒu�ɕ`��
/// </summary>
/// <param name="placeData">�`�悵�Ăق����ʒu</param>
void EditorDrawModelManager::Draw(PlacementData placeData) const
{
    switch (placeData.objKind)
    {
        //�w��g�ޓG�Ȃǂ͕`����@��ς���
    case CAST_I(ObjectInit::InitObjKind::circleLaserShip):
        drawCircleFlyShip->Draw(placeData);
        break;
    default:
        //���ʂ̕`��
        drawModelMap.find(static_cast<ObjectInit::InitObjKind>(placeData.objKind))->second->Draw(placeData);
        break;
    } 
}
/// <summary>
/// �����̈ʒu�ɕ`��
/// </summary>
/// <param name="placeData">�`�悵�Ăق����ʒu���܂Ƃ߂�����</param>
void EditorDrawModelManager::Draw(std::vector<PlacementData> placeData) const
{
    for (int i = 0;i < CONTAINER_GET_SIZE(placeData); i++)
    {
        Draw(placeData[i]);
    }
}
