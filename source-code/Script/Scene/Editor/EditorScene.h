#pragma once
#include <iostream>
#include <memory>
#include "SceneBase.h"
class StageDataEditor;
class StageObjectController;
class StageTimeLimitEditor;
class EditorMenu;
class CameraObserver;
class EditorDrawModelManager;
class EditManual;
class EditorEffect;
class EditorCamera;
class EditorObject;
class EditorInput;
class MouseInput;
class EditorUI;
/// <summary>
/// �ҏW�V�[���N���X
/// </summary>
class EditorScene final : public SceneBase
{
public:
    /// <summary>
    /// ���j���[��ʂ�J�����A�ҏW�N���X�Ȃǂ��m��
    /// </summary>
    EditorScene();
    /// <summary>
    /// �R���X�g���N�^�Ŋm�ۂ��������J��
    /// </summary>
    ~EditorScene()override;
    /// <summary>
    /// ���j���[��Editor�̍X�V
    /// </summary>
    /// <returns>�^�C�g���ɖ߂�����Q�[�����I��������Editor���ēǂݍ��݂����肷��</returns>
    SceneType Update()override;
    /// <summary>
    /// ���j���[��ʂ�Editor�̕`��
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// �I�u�W�F�N�g�̈ړ���������
    /// </summary>
    void MoveObject();
    /// <summary>
    /// �I�u�W�F�N�g�̉�]��������
    /// </summary>
    void RotateObject();
    /// <summary>
    /// �I�u�W�F�N�g�̍폜
    /// </summary>
    void DeleteObject();
    /// <summary>
    /// �I�u�W�F�N�g�̔z�u
    /// </summary>
    void PutObject();
    /// <summary>
    /// �ҏW�t�F�[�Y��ύX
    /// </summary>
    void ChangeFase();
    /// <summary>
    /// �^�C�����~�b�g��ύX
    /// </summary>
    void ChangeTimeLimit();
    /// <summary>
    /// �J�����̋�����ύX
    /// </summary>
    void ScalingCameraBetween();
    /// <summary>
    /// �ҏW�i�K��߂�
    /// </summary>
    void StepBackEditState();
    /// <summary>
    /// �Ȃɂ�������Ă��Ȃ���
    /// </summary>
    void FreeButtonUpdate();
    /// <summary>
    /// �I�u�W�F�N�g��I�������Ƃ�
    /// </summary>
    void SelectObject();
    /// <summary>
    /// �ҏW����O������ɂ�蒼��
    /// </summary>
    void StepEditState();
    //�֐��|�C���^
    void (EditorScene::* EditFunc[12])() = {
        &EditorScene::MoveObject,&EditorScene::RotateObject,& EditorScene::DeleteObject,
        &EditorScene::PutObject,&EditorScene::ChangeFase,&EditorScene::ChangeTimeLimit,
        & EditorScene::ScalingCameraBetween,& EditorScene::StepBackEditState,& EditorScene::FreeButtonUpdate,& EditorScene::SelectObject,& EditorScene::StepEditState
    };
    //���j���[
    std::unique_ptr<EditorMenu> menu;
    //�ҏW���̎�ނ�ύX����
    std::unique_ptr<EditorDrawModelManager> drawManager;
    //�ҏW�������
    std::unique_ptr<EditManual> manual;
    //�ҏW���ɏo�Ă���G�t�F�N�g�̍X�V��
    std::unique_ptr <EditorEffect> editorEffect;
    //�}�E�X�ňړ����鎞�Ɏg��
    std::shared_ptr<MouseInput> mouse;
    //�J����
    std::shared_ptr<EditorCamera> camera;
    //�J�����̌�����ҏW�I�u�W�F�N�g�ɓ`����N���X
    std::shared_ptr<CameraObserver> cameraObserver;
    //�X�e�[�W�̒[
    std::unique_ptr<StageObjectController> stage;
    //���ݕҏW���Ă��镨
    std::shared_ptr<StageDataEditor> editor;
    //���ݕҏW���̃I�u�W�F�N�g
    std::unique_ptr<EditorObject> editObject;
    //UI
    std::shared_ptr<EditorUI> ui;
    //���Ԃ̕ύX
    std::shared_ptr<StageTimeLimitEditor> timeEditor;
    //�ҏW���̓��͂��Ǘ�
    std::shared_ptr<EditorInput> input;
    //�ĕҏW����
    bool isReEdit = false;
    //��]���[�h��
    bool isRotate = false;
    //�ړ�
    bool isMove = false;
};