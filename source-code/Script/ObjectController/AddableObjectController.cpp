#include "AddableObjectController.h"
#include "Utility.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="kind">初期化したいオブジェクトの種類</param>
AddableObjectController::AddableObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
}
/// <summary>
/// リストに対象のオブジェクトを纏めて追加
/// </summary>
/// <param name="placeDataVec">配置位置リスト</param>
void AddableObjectController::OnAddObject(std::vector<PlacementData> placeDataVec)
{
    if (!placeDataVec.empty())
    {
        //配置位置リストのサイズだけ追加
        for (int i = 0; i < CONTAINER_GET_SIZE(placeDataVec); i++)
        {
            //同じ種類なら追加
            if (placeDataVec[i].objKind == CAST_I(controllObjKind))
            {
                AddObject(placeDataVec[i]);
            }
        }
    }
}