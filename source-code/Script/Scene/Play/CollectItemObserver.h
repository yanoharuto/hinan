#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
class CollectItemController;
class PlayerObserver;
/// <summary>
/// ���W�A�C�e���̐�����`����N���X
/// </summary>
class CollectItemObserver final
{
public:
    /// <summary>
    /// �Ǘ��N���X������
    /// </summary>
    /// <param name="collectItemController">���W�A�C�e���̊Ǘ��N���X</param>
    CollectItemObserver(std::shared_ptr<CollectItemController>& collectItemController);
    /// <summary>
    /// �Ǘ��N���X���J��
    /// </summary>
    ~CollectItemObserver();
    /// <summary>
    /// �ŏ��ɃX�e�[�W�ɔz�u����閇��
    /// </summary>
    /// <returns>�X�e�[�W�ɔz�u���ꂽ�ő吔</returns>
    int GetTotalItemNum ()const;
    /// <summary>
    /// �����Ǝ��W�A�C�e���̋���
    /// </summary>
    /// <param name="pos">���W�A�C�e���Ƃ̋����𒲂ׂ����ʒu</param>
    /// <returns>�����Ǝ��W�A�C�e���̋����x�N�g��</returns>
    VECTOR GetItemBetween(VECTOR pos)const;
    /// <summary>
    /// �A�C�e���̎c�薇��
    /// </summary>
    /// <returns>�v���C���[�Ɏ����ƌ���</returns>
    int GetRemainingItemNum ()const;
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
    //���W�A�C�e���̐���ʒu�������Ă��炤
    std::shared_ptr<CollectItemController> collectController;
};