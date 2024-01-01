#include "PlayerDrawModel.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "PlayerCar.h"
/// <summary>
	/// �v���C���[�̋@�̂̌X���ȂǂɑΉ�����
	/// </summary>
PlayerDrawModel::PlayerDrawModel()
	:DrawModel(ObjectInit::InitObjKind::player)
{
}
/// <summary>
/// �v���C���[�̊p�x�ɍ��킹�ĉ�]����
/// </summary>
/// <param name="drawObj"></param>
void PlayerDrawModel::Draw(VECTOR position, VECTOR direction, VECTOR rotate) const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //�ύX�O�̍s���ۑ�
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    //������ς���
    ModelSetMatrix(position, direction, rotate);
    MV1DrawModel(modelHandle);
}

/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
void PlayerDrawModel::ModelSetMatrix(VECTOR position, VECTOR direction, VECTOR rotate) const
{	
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), rotate.z);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f + rotate.y) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, position);
}