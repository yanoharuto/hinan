#include "EditorCircleFlyShipDrawModel.h"
#include "CSVFileLoader.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "InitObjKind.h"
#include "FlyShipController.h"
#include "EditorDrawModel.h"
#include "AddFlyShipDataLoader.h"
#include "Utility.h"
#include "InitActor.h"
#include "Object.h"
/// <summary>
/// 円形飛行艇は編集時は陣形の飛行機纏めて描画する
/// そのために必要な情報を初期化
/// </summary>
EditorCircleFlyShipDrawModel::EditorCircleFlyShipDrawModel()
    :EditorDrawModel(InitObjKind::circleLaserShip)
{
    Init();
}
/// <summary>
/// 普通に円を作っている機体を描画
/// </summary>
/// <param name="data">配置位置</param>
void EditorCircleFlyShipDrawModel::Draw(PlacementData data) const
{
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
    VECTOR dataPos = VGet(data.posX, 0, data.posZ);
    for (int i = 0; i < uniNum; i++)
    {
        dataDir = VNorm(OriginalMath::GetYRotateVector(dataDir, uniDirRota)); 
        //描画するモデルがないなら終了
        if (modelHandle == -1)return;
        //向きを変える
        ModelSetMatrix(VAdd(dataPos, VScale(dataDir, uniBetween)),VGet(data.dirX, 0, data.dirZ));
        // ３Dモデルのポジション設定
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// 引数のmodelの位置や回転に合わせて描画する
/// </summary>
/// <param name="drawObj">位置とか教えてももらう</param>
void EditorCircleFlyShipDrawModel::Draw(VECTOR position, VECTOR rotate) const
{
    for (int i = 0; i < uniNum; i++)
    {
        rotate = VNorm(OriginalMath::GetYRotateVector(rotate, uniDirRota));
        //描画するモデルがないなら終了
        if (modelHandle == -1)return;
        //向きを変える
        ModelSetMatrix(VAdd(position, VScale(rotate, uniBetween)), rotate);
        MV1DrawModel(modelHandle);
    }

}
/// <summary>
/// 円を作るために必要な情報を所得
/// </summary>
void EditorCircleFlyShipDrawModel::Init()
{
    //FlyShip用のデータをロード
    auto addDataLoader = std::make_unique<AddFlyShipDataLoader>(AddObjectDataLoader::AddData::circleFlyShip);
    auto addData = addDataLoader->GetLoadData();
    uniNum = STR_TO_I(addData[CAST_I(FlyShipController::FlyShipParamator::unitNum)]);
    uniBetween = STR_TO_F(addData[CAST_I(FlyShipController::FlyShipParamator::unitBetween)]);
    //機体の数だけ割る
    uniDirRota = 360.0f / uniNum;
    //追加情報読み取り終了
    SAFE_RESET(addDataLoader);
}
