#include "EnemyGenerator.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "AddableObjectController.h"
/// <summary>
/// �G�@�ʒu�ɂ��Ă̏���������
/// </summary>
EnemyGenerator::EnemyGenerator()
{
    editDataVec = FirstPositionGetter::GetPlaceData();
}
/// <summary>
/// �G�R���g���[���[�Ɉʒu���������Ēǉ�����
/// </summary>
/// <param name="collectNum">�v���C���[�����W�����A�C�e����</param>
/// <param name="addObjController">�G�R���g���[���[</param>
void EnemyGenerator::GenerateEnemys(int collectNum, std::weak_ptr<AddableObjectController>& addObjController)
{
    auto controller = addObjController.lock();
    if (controller != nullptr)
    {
        controller->OnAddObject(GetNowEnemyEditData(collectNum));
    }
}
/// <summary>
/// �G�l�~�[�̔z�u����n��
/// </summary>
/// <param name="collectNum">���̎��W�A�C�e���̏�����</param>
/// <returns>�G�l�~�[�̔z�u���</returns>
std::vector<PlacementData> EnemyGenerator::GetNowEnemyEditData(int collectNum)
{
    //�z�u���
    std::vector<PlacementData> editData;

    for (unsigned int i = 0; i < editDataVec.size(); i++)
    {
        ObjectInit::InitObjKind dataKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
        //�v���C���[�����W�A�C�e��������Ă����炻�̃^�C�~���O�œG�𑝂₷
        if (editDataVec[i].collectNum == collectNum)
        {
            editData.push_back(editDataVec[i]);
        }
    }
    return editData;
}