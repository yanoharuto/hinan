#include "DrawModel.h"
#include "DxLib.h"
#include "Object.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// model�̕`��������
/// </summary>
DrawModel::DrawModel(ObjectInit::InitObjKind kind)
{
    modelHandle = InitActor::GetModelHandle(kind);
}
/// <summary>
/// �`��
/// </summary>
/// <param name="position">�ʒu</param>
/// <param name="rotate">��]</param>
void DrawModel::Draw(VECTOR position, VECTOR rotate)const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle != -1)
    {
        //������ς���
        ModelSetMatrix(position,rotate);
        //�`��
        MV1DrawModel(modelHandle);
    }
}

/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
void DrawModel::ModelSetMatrix(VECTOR position, VECTOR rotate) const
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle, rotate, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, position);
}