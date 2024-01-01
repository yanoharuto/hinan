#pragma once
#include "DrawModel.h"
class PlayerCar;
/// <summary>
/// �v���C���[�̋@�̂̌X���ȂǂɑΉ�����
/// </summary>
class PlayerDrawModel : public DrawModel
{
public:
    /// <summary>
    /// �v���C���[�̋@�̂̌X���ȂǂɑΉ�
    /// </summary>
    PlayerDrawModel();
    /// <summary>
    /// �v���C���[�̊p�x�ɍ��킹�ĉ�]����
    /// </summary>
    /// <param name="drawObj"></param>
    void Draw(VECTOR position,VECTOR direction,VECTOR rotate) const;
protected:
    /// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
    void ModelSetMatrix(VECTOR position, VECTOR direction, VECTOR rotate) const;
};

