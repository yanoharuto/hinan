#include "AddableObjectController.h"
#include "Utility.h"
/// <summary>
/// ������
/// </summary>
/// <param name="kind">�������������I�u�W�F�N�g�̎��</param>
AddableObjectController::AddableObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
{
}
/// <summary>
/// ���X�g�ɑΏۂ̃I�u�W�F�N�g��Z�߂Ēǉ�
/// </summary>
/// <param name="placeDataVec">�z�u�ʒu���X�g</param>
void AddableObjectController::OnAddObject(std::vector<PlacementData> placeDataVec)
{
    if (!placeDataVec.empty())
    {
        //�z�u�ʒu���X�g�̃T�C�Y�����ǉ�
        for (int i = 0; i < CONTAINER_GET_SIZE(placeDataVec); i++)
        {
            //������ނȂ�ǉ�
            if (placeDataVec[i].objKind == CAST_I(controllObjKind))
            {
                AddObject(placeDataVec[i]);
            }
        }
    }
}