#pragma once
#include "AddableObjectController.h"
/// <summary>
/// �v���C���[���͂�����΂��ۋ�
/// </summary>
class SawController : public AddableObjectController
{
public:
    /// <summary>
    /// �v���C���[���͂�����΂��ۋ�
    /// </summary>
    SawController();
    /// <summary>
    /// �ۋ���ǉ�
    /// </summary>
    /// <param name="editData">�ǉ�����ʒu�Ȃǂ̏��</param>
    void AddObject(PlacementData editData)override;
    /// <summary>
    /// ��]������@�j�󂳂ꂽ��j��
    /// </summary>
    void Update()override;
};

