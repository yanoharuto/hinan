#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
/// <summary>
/// �s���͈͂����߂��
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::InitObjKind::wall)
{
    tag = ObjectTag::obstacle;
    position = {0,0,0};
}