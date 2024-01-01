#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "AddMoveSawDataLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "ReusableTimer.h"
/// <summary>
/// �ړ���]�̂�����
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(PlacementData editData)
    :Saw(InitObjKind::moveSaw,editData)
{   
    //�ǉ���񂩂�ړ����x�Ȃǂ�����
    auto addDataLoader = std::make_unique<AddMoveSawDataLoader>();
    auto addStrDataVec = addDataLoader->GetLoadData();
    //�^�C�}�[�������Ă���Ԃ�������
    moveLarpTimer = std::make_unique<ReusableTimer>(STR_TO_D(addStrDataVec[CAST_I(MoveParametor::moveTime)]));
    //�O�������ɓ���
    velocity = VScale(direction, STR_TO_F(addStrDataVec[CAST_I(MoveParametor::moveSpeed)]));
    //�j�󎞂̃G�t�F�N�g
    EffectManager::LoadEffect(EffectKind::bombExplosion);
}
/// <summary>
/// �ړ����Ȃ����]����
/// </summary>
void MoveSaw::Update()
{
    if (moveLarpTimer->IsOverLimitTime())//���Ԃ����ς��������甽�Ε����ɓ���
    {
        moveLarpTimer->Reuse();//�ړ����Ԃ����Z�b�g
        
        velocity = VSub(VGet(0,0,0),velocity);//�ړ��������]
    }
    position = VAdd(position, velocity);
    //��]
    Saw::Update();
}