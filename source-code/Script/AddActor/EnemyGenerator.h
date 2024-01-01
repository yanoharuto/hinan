#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "InitActor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class AddableObjectController;
using namespace ObjectInit;
/// <summary>
/// �G�@�̐������s��
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
    /// �G�@�ʒu�ɂ��Ă̏���������
    /// </summary>
    EnemyGenerator();
    /// <summary>
    /// �G�R���g���[���[�Ɉʒu���������Ēǉ�����
    /// </summary>
    /// <param name="collectNum">�v���C���[�����W�����A�C�e����</param>
    /// <param name="addObjController">�G�R���g���[���[</param>
    void GenerateEnemys(int collectNum, std::weak_ptr<AddableObjectController>& addObjController);
private:
    /// <summary>
    /// �G�l�~�[�̔z�u����n��
    /// </summary>
    /// <param name="collectNum">���̎��W�A�C�e���̏�����</param>
    /// <returns>�G�l�~�[�̔z�u���</returns>
    std::vector<PlacementData> GetNowEnemyEditData(int getCollectNum);
    
    //�G�̈ʒu�܂Ƃ�
    std::vector<PlacementData> editDataVec;
};