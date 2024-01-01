#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// •`‰æ•û–@‚ğ•ÏX‚·‚é‚È‚ç‘æ“ñˆø”‚É“n‚µ‚Ä‚­‚¾‚³‚¢
/// </summary>
/// <param name="kind"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = ObjectState::sleep;
}

/// <summary>
/// “–‚½‚è”»’è‚Å“–‚½‚Á‚Ä‚½‚ç“n‚·î•ñ
/// </summary>
/// <returns></returns>
HitCheckInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}
