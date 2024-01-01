#pragma once
#include <list>
#include "ActorController.h"
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// ���W�A�C�e���̑���
/// </summary>
class CollectItemController final : public ActorController
{
public:
    /// <summary>
    /// �R�C����\��New���čő喇����ۑ�
    /// </summary>
    CollectItemController();
    /// <summary>
    /// actorList�̐擪�̎��W�A�C�e�������X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// ���W�A�C�e���̕`��
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const override;
    /// <summary>
    /// �Q�[�����n�܂�O�̏���
    /// </summary>
    void PrepareGame()override;
    /// <summary>
    /// �����Ǝ��W�A�C�e���̋���
    /// </summary>
    /// <param name="pos">���W�A�C�e���Ƃ̋����𒲂ׂ����ʒu</param>
    /// <returns>�����Ǝ��W�A�C�e���̋����x�N�g��</returns>
    VECTOR GetItemBetween(VECTOR pos)const;
    /// <summary>
    /// �ŏ��ɃX�e�[�W�ɔz�u����閇��
    /// </summary>
    /// <returns>�X�e�[�W�ɔz�u���ꂽ�ő吔</returns>
    int GetTotalNum()const;
    /// <summary>
    /// �A�C�e���̎c�薇��
    /// </summary>
    /// <returns>�v���C���[�Ɏ����ƌ���</returns>
    int GetRemainingNum()const;
    /// <summary>
    /// ���̎��W�A�C�e�������Ԗڂ̃A�C�e����
    /// </summary>
    /// <returns>���ꂽ�瑝����</returns>
    int GetCollectCount()const;
    /// <summary>
    /// �Ō�̈�̃A�C�e����������ꂽ��
    /// </summary>
    /// <returns>������ꂽ��True</returns>
    bool IsCollectLastOne()const;

private:
    //���W�A�C�e���̍ő吔
    int totalCollectNum;
    //���̎��W�A�C�e�������Ԗڂ�
    int collectCount;
    //�������ꂽ�A�C�e���̐�
    int remainingCollectNum;
    //������I�u�W�F�N�g�����ꂽ��
    bool isCollectLastOne;
    /// ���ݓ����Ă�����W�A�C�e���̈ʒu
    VECTOR nowActiveCollectItemPos;
};
