#pragma once
#include <memory>
#include <iostream>
class ObjectObserver;
class BomberController;
class RotatingLaserController;
/// <summary>
/// �����A�C�e���Ȃǂ̃_���[�W������I�u�W�F�N�g�𐶐�����
/// </summary>
class DamageObjectGenerator final
{
public:
    /// <summary>
    /// �_���[�W����̂��镨�̎��
    /// </summary>
    enum DamageObjectKind
    {
        bomber,//���e
        laser//���[�U�[
    };
    /// <summary>
    /// ���[�U�[�Ɣ��e�̊Ǘ��N���X��ǉ�
    /// </summary>
    /// <param name="laserController">���[�U�[�Ǘ��N���X</param>
    /// <param name="bombController">���e�Ǘ��N���X</param>
    DamageObjectGenerator(std::shared_ptr<RotatingLaserController>& laserController,std::shared_ptr<BomberController> bombController);
    /// <summary>
    /// ���[�U�[�Ɣ��e�̊Ǘ��N���X�����
    /// </summary>
    ~DamageObjectGenerator();
    /// <summary>
    /// �_���[�W��^����I�u�W�F�N�g�𐶐�
    /// </summary>
    /// <param name="itemTag">�쐬�������I�u�W�F�N�g�̎��</param>
    /// <param name="sub">���˂����l�̏���n��</param>
    void GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub);
private:
    //��]���[�U�[�Ǘ��N���X
    std::shared_ptr<RotatingLaserController> rotaLaserController;
    //���e�Ǘ��N���X
    std::shared_ptr<BomberController> bomberController;
};