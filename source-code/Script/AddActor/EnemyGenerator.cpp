#include "EnemyGenerator.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "AddableObjectController.h"
/// <summary>
/// 敵機位置についての初期化する
/// </summary>
EnemyGenerator::EnemyGenerator()
{
    editDataVec = FirstPositionGetter::GetPlaceData();
}
/// <summary>
/// 敵コントローラーに位置情報を教えて追加する
/// </summary>
/// <param name="collectNum">プレイヤーが収集したアイテム数</param>
/// <param name="addObjController">敵コントローラー</param>
void EnemyGenerator::GenerateEnemys(int collectNum, std::weak_ptr<AddableObjectController>& addObjController)
{
    auto controller = addObjController.lock();
    if (controller != nullptr)
    {
        controller->OnAddObject(GetNowEnemyEditData(collectNum));
    }
}
/// <summary>
/// エネミーの配置情報を渡す
/// </summary>
/// <param name="collectNum">今の収集アイテムの所得数</param>
/// <returns>エネミーの配置情報</returns>
std::vector<PlacementData> EnemyGenerator::GetNowEnemyEditData(int collectNum)
{
    //配置情報
    std::vector<PlacementData> editData;

    for (unsigned int i = 0; i < editDataVec.size(); i++)
    {
        ObjectInit::InitObjKind dataKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
        //プレイヤーが収集アイテムを取ってきたらそのタイミングで敵を増やす
        if (editDataVec[i].collectNum == collectNum)
        {
            editData.push_back(editDataVec[i]);
        }
    }
    return editData;
}