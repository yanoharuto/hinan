#pragma once
#include "AddableObjectController.h"
/// <summary>
/// �ړ������]�̂�����̊Ǘ���
/// </summary>
class MoveSawController : public AddableObjectController
{
public:
    /// <summary>
    /// �ړ������]�̂�����̊Ǘ���
    /// </summary>
    MoveSawController();
    /// <summary>
    /// ��]�̂�������ړ�������@�j�󂳂ꂽ��j��
    /// </summary>
    void Update()override;
protected:
    /// <summary>
    /// �ړ������]�̂�����̒ǉ�
    /// </summary>
    /// <param name="editData">�ʒu�����</param>
    void AddObject(PlacementData editData)override;
};

