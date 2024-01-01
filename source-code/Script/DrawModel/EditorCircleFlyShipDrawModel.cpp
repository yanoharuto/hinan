#include "EditorCircleFlyShipDrawModel.h"
#include "CSVFileLoader.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "InitObjKind.h"
#include "FlyShipController.h"
#include "EditorDrawModel.h"
#include "AddFlyShipDataLoader.h"
#include "Utility.h"
#include "InitActor.h"
#include "Object.h"
/// <summary>
/// �~�`��s���͕ҏW���͐w�`�̔�s�@�Z�߂ĕ`�悷��
/// ���̂��߂ɕK�v�ȏ���������
/// </summary>
EditorCircleFlyShipDrawModel::EditorCircleFlyShipDrawModel()
    :EditorDrawModel(InitObjKind::circleLaserShip)
{
    Init();
}
/// <summary>
/// ���ʂɉ~������Ă���@�̂�`��
/// </summary>
/// <param name="data">�z�u�ʒu</param>
void EditorCircleFlyShipDrawModel::Draw(PlacementData data) const
{
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
    VECTOR dataPos = VGet(data.posX, 0, data.posZ);
    for (int i = 0; i < uniNum; i++)
    {
        dataDir = VNorm(OriginalMath::GetYRotateVector(dataDir, uniDirRota)); 
        //�`�悷�郂�f�����Ȃ��Ȃ�I��
        if (modelHandle == -1)return;
        //������ς���
        ModelSetMatrix(VAdd(dataPos, VScale(dataDir, uniBetween)),VGet(data.dirX, 0, data.dirZ));
        // �RD���f���̃|�W�V�����ݒ�
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// ������model�̈ʒu���]�ɍ��킹�ĕ`�悷��
/// </summary>
/// <param name="drawObj">�ʒu�Ƃ������Ă����炤</param>
void EditorCircleFlyShipDrawModel::Draw(VECTOR position, VECTOR rotate) const
{
    for (int i = 0; i < uniNum; i++)
    {
        rotate = VNorm(OriginalMath::GetYRotateVector(rotate, uniDirRota));
        //�`�悷�郂�f�����Ȃ��Ȃ�I��
        if (modelHandle == -1)return;
        //������ς���
        ModelSetMatrix(VAdd(position, VScale(rotate, uniBetween)), rotate);
        MV1DrawModel(modelHandle);
    }

}
/// <summary>
/// �~����邽�߂ɕK�v�ȏ�������
/// </summary>
void EditorCircleFlyShipDrawModel::Init()
{
    //FlyShip�p�̃f�[�^�����[�h
    auto addDataLoader = std::make_unique<AddFlyShipDataLoader>(AddObjectDataLoader::AddData::circleFlyShip);
    auto addData = addDataLoader->GetLoadData();
    uniNum = STR_TO_I(addData[CAST_I(FlyShipController::FlyShipParamator::unitNum)]);
    uniBetween = STR_TO_F(addData[CAST_I(FlyShipController::FlyShipParamator::unitBetween)]);
    //�@�̂̐���������
    uniDirRota = 360.0f / uniNum;
    //�ǉ����ǂݎ��I��
    SAFE_RESET(addDataLoader);
}
