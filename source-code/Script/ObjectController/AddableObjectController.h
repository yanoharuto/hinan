#pragma once
#include "ActorController.h"
/// <summary>
/// �ҏW���Ĉʒu�����܂��Ă���I�u�W�F�N�g�̊Ǘ��N���X
/// </summary>
class AddableObjectController abstract : public ActorController
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="kind">�������������I�u�W�F�N�g�̎��</param>
    AddableObjectController(ObjectInit::InitObjKind kind);
    /// <summary>
    /// ���X�g�ɑΏۂ̃I�u�W�F�N�g��Z�߂Ēǉ�
    /// </summary>
    /// <param name="placeDataVec">�z�u�ʒu���X�g</param>
    virtual void OnAddObject(std::vector<PlacementData> placeDataVec);
protected:
    /// <summary>
    /// ���X�g�ɑΏۂ̃I�u�W�F�N�g��ǉ�
    /// </summary>
    /// <param name="placeData">�z�u�ʒu</param>
    virtual void AddObject(PlacementData placeData) = 0;
};