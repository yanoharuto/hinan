#include "Object.h"
#include "InitActor.h"
/// <summary>
/// オブジェクトの種類を渡すと初期化する
/// </summary>
/// <param name="kind">オブジェクトの種類</param>
Object::Object(ObjectInit::InitObjKind kind)
{
    InitParamater(kind);
}
/// <summary>
/// 各オブジェクトの当たり判定や跳ね返り力等の初期化
/// </summary>
void Object::InitParamater(ObjectInit::InitObjKind kind)
{
    //初期化したい情報を所得
    ActorParameter initParam = InitActor::GetActorParamator(kind);
    //ポジション
    position.y = initParam.firstPosY;
    //向き
    direction = { 1,0,0 };
    //跳ね返り力
    bouncePower = initParam.setBouncePow;
    //半径
    radius = initParam.setRadius;
}
/// <summary>
/// 位置や向きをVelocityに合わせて更新する
/// </summary>
void Object::ReflectsVelocity()
{
    // 力をかけ終わったベロシティの方向にディレクションを調整.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // ポジションを更新.
    position = VAdd(position, velocity);
}
