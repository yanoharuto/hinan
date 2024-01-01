#include "EditorDrawModel.h"
#include "OriginalMath.h"
#include "EditorObject.h"
#include "InitActor.h"
/// <summary>
/// �e�ҏW�I�u�W�F�N�g�̕`��S����
/// </summary>
/// <param name="kind">�`�悷�镨</param>
EditorDrawModel::EditorDrawModel(ObjectInit::InitObjKind kind)
    :DrawModel(kind)
{
}
/// <summary>
/// �����̏ꏊ�ɕ`��
/// </summary>
/// <param name="data"></param>
void EditorDrawModel::Draw(PlacementData data) const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //������ς���
    ModelSetMatrix(VGet(data.posX, 0, data.posZ),VGet(data.dirX,0,data.dirZ));
    MV1DrawModel(modelHandle);
}
/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
/// <param name="dir"></param>
void EditorDrawModel::ModelSetMatrix(VECTOR pos, VECTOR dir) const
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, pos);
}