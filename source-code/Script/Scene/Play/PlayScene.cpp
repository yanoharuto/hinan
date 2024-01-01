#include "PlayScene.h"
#include "Utility.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "PlayGameProcess.h"
#include "PostGameEndStagingProcess.h"
#include "PrePlayGameProcess.h"
#include "EffekseerForDXLib.h"
#include "GameCamera.h"
#include "GameScreen.h"
#include "ShadowMap.h"
#include "PlayerObserver.h"
#include "CollectItemObserver.h"
#include "CameraObserver.h"
/// <summary>
/// ���j���[��ʂƃQ�[���̗���̊m�ۂƉ������[�h
/// </summary>
PlayScene::PlayScene()
    :SceneBase(SceneType::play)
{   
    //���݂̏���
    nowProgress = PlaySceneProgress::start;
    //�Փ˔���Ǘ�
    conflictManager = std::make_unique<ConflictManager>();
    //�l�X�ȃI�u�W�F�N�g�̍X�V�Ȃǂ�����
    controllerManager = std::make_shared<ActorControllerManager>();
    //�S�[���O����
    gamePrevProcess = std::make_unique<PrePlayGameProcess>(controllerManager->GetSharedCollectObserver());
    //�J����
    auto player = controllerManager->GetSharedPlayerObserver();
    camera = std::make_shared<GameCamera>(player);
    cameraObserver = std::make_shared<CameraObserver>(camera);
    //�e
    shadowMap = std::make_unique<ShadowMap>(controllerManager->GetSharedPlayerObserver());
    //�`�悷�邽�ѕۑ��o����N���X
    screen = std::make_unique<GameScreen>();
    //�J�����̏���
    camera->Update();
    //���j���[��ʂ̊J��
    menu = std::make_unique<Menu>();
    //�S�[����̏����͂܂��Ă΂Ȃ�
    postGameEndProcess = nullptr;
    playGameProcess = std::make_unique<PlayGameProcess>(controllerManager->GetSharedPlayerObserver(), controllerManager->GetSharedCollectObserver());
}
/// <summary>
/// ���j���[�ƃQ�[���̊J��
/// </summary>
PlayScene::~PlayScene()
{
    SAFE_RESET(menu);
    SAFE_RESET(conflictManager);
    SAFE_RESET(shadowMap);
    SAFE_RESET(screen);
    SAFE_RESET(postGameEndProcess);
    SAFE_RESET(playGameProcess);
    SAFE_RESET(gamePrevProcess);
    controllerManager.reset();
    camera.reset();
}
/// <summary>
/// �Q�[����V��
/// </summary>
/// <returns></returns>
SceneType PlayScene::Update()
{
    //���j���[�Ńv���C���[������I�񂾂�
    menu->Update();
    //���j���[�̏�Ԃɂ���Ď��̃V�[����ύX    
    switch (menu->GetMenuState())
    {
        //�Q�[������蒼��
    case Menu::MenuOptions::retry:
        nowSceneType = SceneType::reload;
        break;
        //�^�C�g���ɖ߂�
    case Menu::MenuOptions::returnTitle:
        nowSceneType = SceneType::title;
        break;
        //�Q�[���I��
    case Menu::MenuOptions::exitGame:
        nowSceneType = SceneType::escape;
        break;
    }

    //menu��ʂ��J���ĂȂ��Ȃ畁�ʂ̏���
    if (!menu->IsMenuOpen())
    {
        (this->*UpdateFunc[CAST_I(nowProgress)])();
    }
   
    return nowSceneType;
}
/// <summary>
/// ���j���[���J���Ă��鎞�ƗV��ł���Ƃ��ŏ������Ⴄ
/// </summary>
void PlayScene::Draw()const
{   
   (this->*DrawFunc[CAST_I(nowProgress)])();
}

/// <summary>
/// �G�t�F�N�g�̍X�V����
/// </summary>
void PlayScene::UpdateEffect()
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();
    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
    UpdateEffekseer3D();
    UpdateEffekseer2D();
}
/// <summary>
/// �J�E���g�_�E���I���܂ł̏���
/// </summary>
void PlayScene::UpdatePreStartCountdownEnd()
{
    gamePrevProcess->Update();
    controllerManager->PrepareGame();
    camera->Update();
    shadowMap->SetShadowMapArea();
    //�G�t�F�N�g�̍X�V
    UpdateEffect();
    //�������I�������
    if (gamePrevProcess->IsEndProcess())
    {
        nowProgress = PlaySceneProgress::game;
        SAFE_RESET(gamePrevProcess);
    }
}
/// <summary>
/// �V��ł���Ƃ��̏���
/// </summary>
void PlayScene::UpdatePlayGame()
{
    //�Q�[����V��ł���Ƃ��̏���
    playGameProcess->Update(controllerManager->GetSharedCollectObserver());
    controllerManager->Update();
    conflictManager->Update();
    camera->Update();
    shadowMap->SetShadowMapArea();
    //�G�t�F�N�g�̍X�V
    UpdateEffect();
    //�V��ł���Ƃ��̏������I��������
    if (playGameProcess->IsEndProcess())
    {
        postGameEndProcess = std::make_unique<PostGameEndStagingProcess>(controllerManager->GetSharedPlayerObserver(), playGameProcess->GetGameTimer());
        SAFE_RESET(playGameProcess);
        controllerManager.reset();
        nowProgress = PlaySceneProgress::postGameEnd;
    }
}
/// <summary>
/// �S�������̏���
/// </summary>
void PlayScene::UpdatePostGameEndProcess()
{
    postGameEndProcess->Update();
    //�G�t�F�N�g�̍X�V
    UpdateEffect();
    if (postGameEndProcess->IsEndProcess())
    {
        nowSceneType = SceneType::title;
    }
}
/// <summary>
/// �J�E���g�_�E���I���܂ł̕`��
/// </summary>
void PlayScene::DrawPreStartCountdownEnd()const
{
    if (menu->IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
        menu->Draw();
    }
    else//�V��ł���Ƃ��̏�Ԃ�`��
    {
        //�V���h�E�}�b�v��model�̕`��
        shadowMap->SetUpDrawShadow();
        controllerManager->Draw(cameraObserver);
        shadowMap->EndDrawShadow();
        controllerManager->Draw(cameraObserver);
        shadowMap->Use();
        //�G�t�F�N�g
        DrawEffekseer3D();
        DrawEffekseer2D();
        gamePrevProcess->Draw();
        //�`���ۑ�
        screen->ScreenUpdate();
    }
}
/// <summary>
/// �V��ł���Ƃ��̕`��
/// </summary>
void PlayScene::DrawPlayGame()const
{
    if (menu->IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
        menu->Draw();
    }
    else//�V��ł���Ƃ��̏�Ԃ�`��
    {
        shadowMap->SetUpDrawShadow();
        controllerManager->Draw(cameraObserver);
        shadowMap->EndDrawShadow();
        controllerManager->Draw(cameraObserver);
        shadowMap->Use();
        //�G�t�F�N�g
        DrawEffekseer3D();
        DrawEffekseer2D();
        playGameProcess->Draw();
        //�`���ۑ�
        screen->ScreenUpdate();
    }
}
/// <summary>
/// �S���A�C�e�������������̏���
/// </summary>
void PlayScene::DrawPostGameEndProcess()const
{
    if (menu->IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
        menu->Draw();
    }
    else
    {
        //�G�t�F�N�g
        DrawEffekseer3D();
        DrawEffekseer2D();
        postGameEndProcess->Draw();
    }
}