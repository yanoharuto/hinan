#pragma once
#include "StageDataEditor.h"
/// <summary>
/// ���W�A�C�e���̕ҏW�N���X
/// </summary>
class CollectItemDataEditor final : public StageDataEditor
{
public:
    /// <summary>
    /// ���W�A�C�e���̕ҏW�N���X
    /// </summary>
    CollectItemDataEditor();
    /// <summary>
    ///  �e�N���X�Ɠ����X�V�Ǝ��W�A�C�e���̐����X�V����
    /// </summary>
    void Update(std::weak_ptr<CameraObserver> cameraObserever)override;
    /// <summary>
    /// �ҏW����ҏW���I�����I�u�W�F�N�g�̕`��
    /// </summary>
    void Draw()const override;
private:
    //�����ڂ̎��W�A�C�e���Ȃ̂��̈ʒu
    const int drawCollectNumY = 200;
    //���@���Ԗڂ̃~�b�V�������̈ʒu
    const int drawEditedCollectNumY = 0;
    //�ǂݍ��ޔz�u���̏����Ă���t�@�C���̃p�X
    static const std::string loadFileName;
};

