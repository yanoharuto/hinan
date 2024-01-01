#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorMenu.h"
#include "StageTimeLimitEditor.h"
#include "EditorManager.h"
#include "UserInput.h"
#include "EditorCamera.h"
#include "EditorEffect.h"
#include "EditManual.h"
#include "CameraObserver.h"
#include "StageObjectController.h"
#include "StageDataEditor.h"
#include "MouseInput.h"
#include "EditorInput.h"
#include "EffekseerForDXLib.h"
#include "EditorObject.h"
#include "EditorUI.h"
/// <summary>
/// ���j���[��ʂ�J�����A�ҏW�N���X�Ȃǂ��m��
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::editor)
{
    SetMouseDispFlag(true);
    //�J����
    camera = std::make_shared<EditorCamera>();
    cameraObserver = std::make_unique<CameraObserver>(camera);
    //�ҏW�I�u�W�F�N�g�̎�ނ�ύX����N���X
    drawManager = std::make_unique<EditorDrawModelManager>();
    //���j���[���
    menu = std::make_unique< EditorMenu>();
    //�����������
    manual = std::make_unique< EditManual>();
    //�G�t�F�N�g
    editorEffect = std::make_unique< EditorEffect>();
    //�w�i
    stage = std::make_unique< StageObjectController>();
    //���݂̕ҏW�N���X
    editor = std::make_shared<StageDataEditor>();
    //�ҏW�I�u�W�F�N�g
    editObject = std::make_unique< EditorObject>();
    //�ҏW���̓��͂𒲂ׂ�
    input = std::make_shared<EditorInput>();
    //�}�E�X
    mouse = std::make_shared<MouseInput>();
    //�������Ԃ̕ύX
    timeEditor = std::make_shared<StageTimeLimitEditor>();
    //UI
    ui = std::make_shared< EditorUI>();
    //�ړ��t���O
    isMove = true;
}
/// <summary>
/// �R���X�g���N�^�Ŋm�ۂ��������J��
/// </summary>
EditorScene::~EditorScene()
{
    SAFE_RESET(menu);
    SAFE_RESET(ui);
    SAFE_RESET(drawManager);
    camera.reset();
    SAFE_RESET(manual);
    SAFE_RESET(editorEffect);
    SetMouseDispFlag(false);
    SAFE_RESET(stage);
    mouse.reset();
}
/// <summary>
/// ���j���[��Editor�̍X�V
/// </summary>
/// <returns>�^�C�g���ɖ߂�����Q�[�����I��������Editor���ēǂݍ��݂����肷��</returns>
SceneType EditorScene::Update()
{
    mouse->UpdateMousePosition();
    menu->Update(mouse);//���j���[��ʂ̍X�V
    auto returnType = menu->GetMenuState();
    //�^�C�g���V�[����I�������Ȃ�߂�
    switch (returnType)
    {
    case EditorMenu::EditMenuOptions::timeLimitChange:
        ChangeTimeLimit();
        break;
    case EditorMenu::EditMenuOptions::returnTitle:
        return SceneType::title;
        break;
    default:
        break;
    }
    //���j���[��ʊJ���ĂȂ�������
    if (!menu->IsMenuOpen())
    {
        std::weak_ptr<EditorUI> weakUI = ui;
        std::weak_ptr<MouseInput> weakMouse = mouse;
        //���͏󋵂��X�V
        input->Update(weakMouse,weakUI);
        //���͂ɂ���ċ�����ς���
        auto inputMode = input->GetEditMode();
        if (inputMode == EditorInput::EditMode::PlayEditStage)
        {
            return SceneType::play;
        }
        (this->*EditFunc[CAST_I(inputMode)])();
        //�J�����̈ʒu��ς���
        camera->UpdatePosition(weakMouse);
    }
    return nowSceneType;
}
/// <summary>
/// ���j���[��ʂ�Editor�̕`��
/// </summary>
void EditorScene::Draw() const
{
    //���j���[��ʂ��J���Ă�����
    if (menu->IsMenuOpen())
    {
        menu->Draw(timeEditor);
    }
    else
    {
        std::weak_ptr<CameraObserver> weakCamera = cameraObserver;
        //�X�e�[�W�ɔz�u����Ă��镨
        stage->Draw(weakCamera);
        //�ҏW���A�ҏW�ς݃I�u�W�F�N�g��`��
        drawManager->Draw(editObject->GetPlacementData());
        drawManager->Draw(editor->GetNowFaseEditEndPlacementData());
        ui->Draw(editor);
        //�G�t�F�N�g�X�V
        Effekseer_Sync3DSetting();
        UpdateEffekseer3D();
        DrawEffekseer3D();
    }
}
/// <summary>
/// �I�u�W�F�N�g�̈ړ���������
/// </summary>
void EditorScene::MoveObject()
{
    //�ړ��o����悤�ɂ���
    isMove = true;
    isRotate = false;
}
/// <summary>
/// �I�u�W�F�N�g�̉�]��������
/// </summary>
void EditorScene::RotateObject()
{
    //��]�o����悤�ɂ���
    isRotate = true;
    isMove = false;
}
/// <summary>
/// �I�u�W�F�N�g�̍폜
/// </summary>
void EditorScene::DeleteObject()
{
    if (editor->IsReEdit())
    {
        editor->OnEraceEditData();
        isReEdit = false;
    }
}
/// <summary>
/// �I�u�W�F�N�g�̔z�u
/// </summary>
void EditorScene::PutObject()
{
    editor->OnPut(editObject->GetPlacementData());
}
/// <summary>
/// �ҏW�t�F�[�Y��ύX
/// </summary>
void EditorScene::ChangeFase()
{
    //���ҏW���Ă���I�u�W�F�N�g�̏o��^�C�~���O��ύX����
    editor->ChangeAppearFase(mouse);
}
/// <summary>
/// �^�C�����~�b�g��ύX
/// </summary>
void EditorScene::ChangeTimeLimit()
{
    timeEditor->ChangeTimeLimit(mouse);
}
/// <summary>
/// �J�����̋�����ύX
/// </summary>
void EditorScene::ScalingCameraBetween()
{
    std::weak_ptr<MouseInput> weakMouse = mouse;
    camera->UpdateTargetPosition(weakMouse);
}

/// <summary>
/// �ҏW�i�K��߂�
/// </summary>
void EditorScene::StepBackEditState()
{
    editor->OnBackStepPrevState();
}
/// <summary>
/// �Ȃɂ�������Ă��Ȃ���
/// </summary>
void EditorScene::FreeButtonUpdate()
{
    if (isMove)
    {
        editObject->Move(cameraObserver, mouse);
    }
    else if(isRotate)
    {
        editObject->Rotate(cameraObserver, mouse);
    }
    //�ĕҏW���͈ړ��Ɖ�]�Ə����ƍĔz�u�ȊO�ł��Ȃ�
    if(!isReEdit)
    {
        //��ނ̕ύX
        editObject->UpdateKind(mouse);
        //�d�Ȃ��Ă��镨�𒲂ׂ�
        editor->UpdateEditTarget(editObject->GetPlacementData());
        //�ҏW�ΏۂɐG��Ă�����G�t�F�N�g���o��
        if (editor->IsReEdit())
        {
            editorEffect->Start();
            editorEffect->UpdatePositionAndDirection(editor->GetEditData());
        }
        else
        {
            editorEffect->Stop();
        }
    }
}
/// <summary>
/// �I�u�W�F�N�g��I�������Ƃ�
/// </summary>
void EditorScene::SelectObject()
{
    //isReEdit��false�Ȃ�ĕҏW����Ώۂ�����
    if (editor->IsReEdit() && !isReEdit)
    {
        //�ĕҏW
        editObject->SetArrangementData(editor->GetEditData());
        isReEdit = true;
    }
    else
    {
        PutObject();
        isReEdit = false;
    }
}
/// <summary>
/// �ҏW����O������ɂ�蒼��
/// </summary>
void EditorScene::StepEditState()
{
    editor->OnStepState();
}