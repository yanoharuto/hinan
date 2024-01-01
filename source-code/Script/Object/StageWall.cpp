#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
/// <summary>
/// s“®”ÍˆÍ‚ğ‹·‚ß‚é•Ç
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::InitObjKind::wall)
{
    tag = ObjectTag::obstacle;
    position = {0,0,0};
}