#pragma once
#include "DxLib.h"
#include "InitObjKind.h"
class DrawModel;
class Object
{
public:
    /// <summary>
    /// �I�u�W�F�N�g�̎��
    /// </summary>
    
    enum class ObjectTag
    {
        //�v���C���[
        player,
        //���W�A�C�e��
        collect,
        //�_���[�W����
        damageObject,
        //��Q��
        obstacle,
        //�X�e�[�W�̒�
        stage,
        //�������u
        acelerationObject,
    };
    /// <summary>
    /// �I�u�W�F�N�g�̏��
    /// </summary>
    enum class ObjectState
    {
        //�����O�@���������������Ƃ�
        sleep,
        //�����Ă���Ƃ�
        active,
        //�����I����ăG�t�F�N�g�Ƃ������o�����
        activeEnd,
        //�����Ȃ��Ȃ���
        dead
    };
    /// <summary>
    /// �I�u�W�F�N�g�̎�ނ�n����
    /// </summary>
    /// <param name="kind"></param>
    Object(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    Object() {};
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <returns></returns>
    virtual ~Object() {};
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() {};
    /// <summary>
    ///�@�Q�[���J�n���������B�I�[�o�[���C�h���Ȃ���Ε��ʂ̍X�V
    /// </summary>
    virtual void PrepareGame() {};
    /// <summary>
    /// ���x����
    // </summary>
    /// <returns></returns>
    VECTOR GetVelocity() { return velocity; };

    /// <summary>
    /// ���ݓ����邩�ǂ���
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetObjectState() const
    {
        return objState;
    };
    /// <summary>
    /// �|�W�V��������
    /// </summary>
    /// <returns></returns>
    VECTOR GetPos()const
    {
        return position;
    };
    /// <summary>
    /// object�̔��a
    /// </summary>
    /// <returns></returns>
    float GetRadius() const
    {
        return radius;
    }
    //���˕Ԃ��͂�Ԃ�
    float GetBouncePower()
    {
        return bouncePower;
    }
    /// <summary>
    /// ��������
    /// </summary>
    /// <returns></returns>
    VECTOR GetDir() const
    {
        return direction;
    };
    /// <summary>
    /// �����̃^�O��Ԃ�
    /// </summary>
    /// <returns></returns>
    ObjectTag GetTag() const
    {
        return tag;
    };

protected:
    /// <summary>
    /// �R���X�g���N�^�ŌĂ΂�鏈��
    /// </summary>
    virtual void InitParamater(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �ʒu�������Velocity�ɍ��킹�čX�V����
    /// </summary>
    virtual void ReflectsVelocity();
    //���a
    float radius = 0;
    //���˕Ԃ���
    float bouncePower = 0;
    //�����t���O
    ObjectState objState = ObjectState::sleep;
    //���������Ȃ̂�
    ObjectTag tag = ObjectTag::stage;
    //����
    VECTOR direction = {1,0,0};
    //�ꏊ
    VECTOR position = {};
    //���x
    VECTOR velocity = {};
};