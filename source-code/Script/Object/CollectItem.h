#pragma once
#include <string>
#include "Actor.h"
#include "EditorObject.h"
class ConflictProcessor;
class SphereHitChecker;
/// <summary>
/// ���W�A�C�e��
/// </summary>
class CollectItem : public Actor
{
public:
    /// <summary>
    /// �����ʒu��������
    /// </summary>
    /// <param name="firstPos"></param>
    CollectItem(PlacementData arrangementData);
    /// <summary>
    /// �G�t�F�N�g�̏I��
    /// </summary>
    ~CollectItem();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �Ԃ��������̏���
    /// </summary>
    /// <param name="conflictInfo"></param>
    void OnConflict(const CollisionResultInfo conflictInfo) override;
private:
    /// <summary>
    /// �㉺�ɉ�]���Ȃ���ړ�
    /// </summary>
    void MoveAndRotate();
    //���b���������̒l���ω�����
    static const float rotateY;
    //�c�����Ɉړ������
    static const float moveYValue;
    //�c�����Ɉړ����鑬�x
    static const float moveYSpeed;
    //�ŏ��̍���
    float firstY;
    //��]��
    float totalMoveYValue = 0;
    //�ԂɂԂ�����
    bool isCarConflict = false;
    //�v���C���[���R�C�����Q�b�g�����Ƃ��̃G�t�F�N�g
    int coinGetEffect = -1;
    //�R�C���̏o���I�[��
    int coinAuraEffect = -1;
};