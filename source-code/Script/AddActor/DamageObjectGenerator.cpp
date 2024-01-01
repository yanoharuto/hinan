#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "RotatingLaserController.h"
#include "ObjectObserver.h"
#include "DamageObjectController.h"
#include "ActorControllerManager.h"
/// <summary>
/// レーザーと爆弾の管理クラスを追加
/// </summary>
/// <param name="laserController">レーザー管理クラス</param>
/// <param name="bombController">爆弾管理クラス</param>
DamageObjectGenerator::DamageObjectGenerator(std::shared_ptr<RotatingLaserController>& laserController, std::shared_ptr<BomberController> bombController)
{
    rotaLaserController = laserController;
    bomberController = bombController;
}
/// <summary>
/// レーザーと爆弾の管理クラスを解放
/// </summary>
DamageObjectGenerator::~DamageObjectGenerator()
{
    rotaLaserController.reset();
    bomberController.reset();
}
/// <summary>
/// ダメージを与えるオブジェクトを生成
/// </summary>
/// <param name="itemTag">作成したいオブジェクトの種類</param>
/// <param name="sub">発射した人の情報を渡す</param>
void DamageObjectGenerator::GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub)
{
    switch (itemTag)
    {
    case DamageObjectGenerator::bomber:
        bomberController->OnGenerateDamageObject(std::move(sub));
        break;
    case DamageObjectGenerator::laser:
        rotaLaserController->OnGenerateDamageObject(std::move(sub));
        break;
    }
}