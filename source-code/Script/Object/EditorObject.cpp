#include "EditorObject.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "CameraObserver.h"
#include "Utility.h"
#include "MouseInput.h"
//移動速度
const float EditorObject::moveSpeed = 17.0f;
//回転速度
const float EditorObject::rotaSpeed = 0.02f;
//マウスの端判定で使う
const int EditorObject::mouseEdge = 10;
/// <summary>
/// エディタ上で使用するオブジェクト
/// </summary>
EditorObject::EditorObject()
    :Object()
{
    position = {};
    direction = VGet(1, 0, 0);
    GetMousePoint(&mouseX, &mouseY);
    kind = CAST_I(ObjectInit::InitObjKind::saw);
}
/// <summary>
/// 編集オブジェクトの種類を変更
/// </summary>
void EditorObject::UpdateKind(std::weak_ptr<MouseInput> input)
{
    changeKindCount += input.lock()->GetWheelIncreaseValue();
    if (changeKindCount >= EDIT_OBJECT_KIND)
    {
        changeKindCount = 0;
    }
    if (changeKindCount < 0)
    {
        changeKindCount = EDIT_OBJECT_KIND - 1;
    }
    kind = CAST_I(kinds[changeKindCount]);
}
/// <summary>
/// マウスの位置になるべく移動
/// </summary>
/// <param name="cameraObserever">カメラの伝達役</param>
/// <param name="input">マウス入力</param>
void EditorObject::Move(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input)
{
    // マウスポインタがある画面上の座標に該当する３Ｄ空間上の Near 面の座標を取得
    const VECTOR startPosition = ConvScreenPosToWorldPos(VGet(input.lock()->GetMouseX(), input.lock()->GetMouseY(), 0.0f));

    // マウスポインタがある画面上の座標に該当する３Ｄ空間上の Far 面の座標を取得
    const VECTOR endPos = ConvScreenPosToWorldPos(VGet(input.lock()->GetMouseX(), input.lock()->GetMouseY(), 1.0f));

    position = VAdd(cameraObserever.lock()->GetCameraPos(), VScale(VNorm(VSub(endPos, startPosition)), cameraObserever.lock()->GetTargetBetweenSize()));
}
/// <summary>
/// マウスに沿って回転
/// </summary>
/// <param name="cameraObserever">カメラの伝達役</param>
/// <param name="input">マウス入力</param>
void EditorObject::Rotate(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input)
{
    direction = input.lock()->GetNormDirection(cameraObserever.lock()->GetCameraDir());
}
/// <summary>
/// 描画に必要な構造体を渡す
/// </summary>
/// <returns>位置と向きと描画したいオブジェクトの種類</returns>
PlacementData EditorObject::GetPlacementData() const
{
    PlacementData data;
    //向き
    data.dirX = direction.x;
    data.dirZ = direction.z;
    //ポジション
    data.posX = position.x;
    data.posZ = position.z;
    data.objKind = kind;
    return data;
}
/// <summary>
/// 引数の配置を引き継ぎ位置を変える
/// </summary>
/// <param name="setData">配置</param>
void EditorObject::SetArrangementData(PlacementData setData)
{
    position = VGet(setData.posX, 0, setData.posZ);
    direction = VGet(setData.dirX, 0, setData.dirZ);
    kind = setData.objKind;
}