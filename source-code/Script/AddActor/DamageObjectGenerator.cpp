#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "RotatingLaserController.h"
#include "ObjectObserver.h"
#include "DamageObjectController.h"
#include "ActorControllerManager.h"
/// <summary>
/// ���[�U�[�Ɣ��e�̊Ǘ��N���X��ǉ�
/// </summary>
/// <param name="laserController">���[�U�[�Ǘ��N���X</param>
/// <param name="bombController">���e�Ǘ��N���X</param>
DamageObjectGenerator::DamageObjectGenerator(std::shared_ptr<RotatingLaserController>& laserController, std::shared_ptr<BomberController> bombController)
{
    rotaLaserController = laserController;
    bomberController = bombController;
}
/// <summary>
/// ���[�U�[�Ɣ��e�̊Ǘ��N���X�����
/// </summary>
DamageObjectGenerator::~DamageObjectGenerator()
{
    rotaLaserController.reset();
    bomberController.reset();
}
/// <summary>
/// �_���[�W��^����I�u�W�F�N�g�𐶐�
/// </summary>
/// <param name="itemTag">�쐬�������I�u�W�F�N�g�̎��</param>
/// <param name="sub">���˂����l�̏���n��</param>
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