#include "ActorControllerManager.h"
#include "AddableObjectController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "EnemyGenerator.h"
#include "CircleFlyShipController.h"
#include "UpDownFlyShipController.h"
#include "MoveSawController.h"
#include "BomberFlyShipController.h"
#include "SawController.h"
#include "RotatingLaserController.h"
#include "BomberController.h"
#include "StageObjectController.h"
#include "CameraObserver.h"
#include "PlayerCarController.h"
#include "CollectController.h"
/// <summary>
/// �Q�[�����Ɏg���I�u�W�F�N�g�̊Ǘ��N���X�̊m��
/// </summary>
/// <param name="collectItemObserver">���W�A�C�e�������ꂽ�肵���狳���Ă��炤</param>
ActorControllerManager::ActorControllerManager()
{
    //���W�A�C�e��
    auto collectController = std::make_shared<CollectItemController>();
    collectObserver = std::make_shared<CollectItemObserver>(collectController);
    //�v���C���[
    auto playerController = std::make_shared<PlayerCarController>();
    //�v���C���[�̏����X�V����I�u�U�[�o�[
    playerObserver = playerController->CreatePlayerObserver();
    //�X�e�[�W�̐���
    actorControllerList.push_back(std::make_shared<StageObjectController>());
    //���[�U�[�Ǘ��N���X
    auto laserController = std::make_shared<RotatingLaserController>();
    //���e�Ǘ��N���X
    auto bombController = std::make_shared<BomberController>();
    //�_���[�W���肠��I�u�W�F�N�g�����N���X
    damageObjGenerator = std::make_shared<DamageObjectGenerator>(laserController, bombController);
    actorControllerList.push_back(laserController);
    actorControllerList.push_back(bombController);
    actorControllerList.push_back(std::move(playerController));
    actorControllerList.push_back(std::move(collectController));
    //�e�G�Ǘ��N���X
    addableActorControllerList.push_back(std::make_shared<SawController>());
    addableActorControllerList.push_back(std::make_shared<MoveSawController>());
    addableActorControllerList.push_back(std::make_shared<CircleFlyShipController>(damageObjGenerator));
    addableActorControllerList.push_back(std::make_shared<BomberFlyShipController>(damageObjGenerator));
    addableActorControllerList.push_back(std::make_shared<UpDownFlyShipController>(damageObjGenerator));
    //�G�����N���X
    enemyGenerator = std::make_unique<EnemyGenerator>();
    //�I�u�W�F�N�g�𐶐�
    for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
    {
        std::weak_ptr<AddableObjectController> weakPtr = *ctrItr;
        enemyGenerator->GenerateEnemys(0, weakPtr);
    }
}
/// <summary>
/// �Ǘ��N���X��X�e�[�W�̃I�u�W�F�N�g�Ȃǂ����ׂĉ��
/// </summary>
ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        (*ite).reset();
    }
    for (auto ite = addableActorControllerList.begin(); ite != addableActorControllerList.end(); ite++)
    {
        (*ite).reset();
    }
    damageObjGenerator.reset();
    SAFE_RESET(enemyGenerator);
}
/// <summary>
/// �X�V
/// </summary>
void ActorControllerManager::Update()
{
    //�G��������
    GenerateEnemyProcess();
    Update(actorControllerList);
    Update(addableActorControllerList);
}
/// <summary>
/// �Q�[���J�n�O�X�V
/// </summary>
void ActorControllerManager::PrepareGame()
{
    //�G��������
    GenerateEnemyProcess();
    PrepareGame(actorControllerList);
    PrepareGame(addableActorControllerList);
}
/// <summary>
/// �e�A�N�^�[�̕`��
/// </summary>
void ActorControllerManager::Draw(std::weak_ptr<CameraObserver> cameraObserever)const
{
    Draw(actorControllerList,cameraObserever);
    Draw(addableActorControllerList,cameraObserever);
}
/// <summary>
/// 2��Actor�Ǘ��N���X�ǂ���ł��g����Q�[���J�n�O�X�V
/// </summary>
/// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
/// <param name="controllerList">controllerClass��Z�߂����X�g</param>
template<typename controllerClass>
void ActorControllerManager::PrepareGame(std::list<std::shared_ptr<controllerClass>> controllerList)
{
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->PrepareGame();
    }
}
/// <summary>
/// 2��Actor�Ǘ��N���X�ǂ���ł��g����X�V
/// </summary>
/// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
/// <param name="controllerList">controllerClass��Z�߂����X�g</param>
template<typename controllerClass>
void ActorControllerManager::Update(std::list<std::shared_ptr<controllerClass>> controllerList)
{
    //�X�V����
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->Update();
    }
}
/// <summary>
/// 2��Actor�Ǘ��N���X�ǂ���ł��g����`��
/// </summary>
/// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
/// <param name="controllerList">controllerClass��Z�߂����X�g</param>
template<typename controllerClass>
void ActorControllerManager::Draw(std::list<std::shared_ptr<controllerClass>> controllerList, std::weak_ptr<CameraObserver> cameraObserever)const
{
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->Draw(cameraObserever);
    }
}
/// <summary>
///�@�G��������
/// </summary>
void ActorControllerManager::GenerateEnemyProcess()
{
    //���W�A�C�e�������ꂽ��
    int nowGetCollectNum = collectObserver->GetCollectCount();
    //���ꂽ�����X�V���ꂽ��
    if (nowGetCollectNum != collectNum)
    {
        //�G�����N���X�ɒǉ�����K�v�����鎖��������
        for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
        {
            collectNum = nowGetCollectNum;
            std::weak_ptr<AddableObjectController> weakPtr = *ctrItr;
            enemyGenerator->GenerateEnemys(collectNum,weakPtr);
        }
    }
}