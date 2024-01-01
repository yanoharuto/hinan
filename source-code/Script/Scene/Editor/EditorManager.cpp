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
/// 編集に必要なものを確保
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
/// 編集物やステージの背景などを解放
/// </summary>
EditorDrawModelManager::~EditorDrawModelManager()
{
    SAFE_DELETE(drawCircleFlyShip);
}
/// <summary>
/// 引数の位置に描画
/// </summary>
/// <param name="placeData">描画してほしい位置</param>
void EditorDrawModelManager::Draw(PlacementData placeData) const
{
    switch (placeData.objKind)
    {
        //陣を組む敵などは描画方法を変える
    case CAST_I(ObjectInit::InitObjKind::circleLaserShip):
        drawCircleFlyShip->Draw(placeData);
        break;
    default:
        //普通の描画
        drawModelMap.find(static_cast<ObjectInit::InitObjKind>(placeData.objKind))->second->Draw(placeData);
        break;
    } 
}
/// <summary>
/// 引数の位置に描画
/// </summary>
/// <param name="placeData">描画してほしい位置をまとめたもの</param>
void EditorDrawModelManager::Draw(std::vector<PlacementData> placeData) const
{
    for (int i = 0;i < CONTAINER_GET_SIZE(placeData); i++)
    {
        Draw(placeData[i]);
    }
}
