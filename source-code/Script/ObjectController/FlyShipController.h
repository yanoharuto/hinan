#pragma once
#include<memory>
#include<iostream>
#include <list>
#include "DxLib.h"
#include "InitObjKind.h"
#include "InitActor.h"
#include "AddableObjectController.h"
#include "AddFlyShipDataLoader.h"

class FlyShip;
class DamageObjectGenerator;
/// <summary>
/// ����ԑD�̂܂Ƃߖ�
/// </summary>
class FlyShipController abstract : public AddableObjectController
{
public:
    /// <summary>
    /// �Z�߂��s�D�̏��������邽�߂ɕK�v�ȃf�[�^������ 
    /// ��s�D�����˂��镨�𐶐��ł���damageObjGenerator������
    /// </summary>
    /// <param name="kind">������������FlyShip�̎��</param>
    /// <param name="damageObjGenerator">���[�U�[�┚�e�𔭎˂���̂Ɏg��</param>
    FlyShipController(ObjectInit::InitObjKind kind, std::shared_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// actorList��DrawModel��damageObjectGenerator�̉��
    /// </summary>
    ~FlyShipController()override;
    /// <summary>
    /// ����ԑD�̏��������
    /// </summary>
    struct InitFlyShipParamator
    {
        //�傫���Ƃ�model�̃p�X�Ƃ������蔻��̑傫���Ƃ�
        ActorParameter actorParam;
        //��������
        float setAliveTime;
        //�ړ����x
        float moveSpeed;
        //���˂̃N�[���^�C��
        float setCoolTime;
        //���j�b�g���m�̋���
        float unitBetween;
        //�c�̍s������ꍇ�̍\����
        int unitNum;
    };
    /// <summary>
    /// ����ԑD�̃p�����[�^���
    /// </summary>
    enum class FlyShipParamator
    {
        //��������
        aliveTime,

        //�ړ����x
        moveSpeed,

        //�������甭�˂��鎞��
        coolTime,

        //�\����
        unitNum,

        //�U�����j�b�g���m�̋���
        unitBetween
    };
protected:
  
    /// <summary>
    /// ��s�D�̒ǉ���񏊓�
    /// </summary>
    /// <param name="kind">��s�D�̎��</param>
    void GetAddData(AddFlyShipDataLoader::AddData kind);
    //���������
    InitFlyShipParamator param = {};
    //���[�U�[�┚�e�𔭎˂���̂Ɏg��
    std::shared_ptr<DamageObjectGenerator> damageObjectGenerator;
};