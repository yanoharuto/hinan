#pragma once
#include "InitObjKind.h"
#include "DxLib.h"
class Object;
/// <summary>
/// model�̕`��������
/// </summary>
class DrawModel
{
public:
    /// <summary>
    /// model�̕`��������
    /// </summary>
    /// <param name="kind">���̎�ނ̃��f���̕`����s��</param>
    DrawModel(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="position">�ʒu</param>
    /// <param name="rotate">��]</param>
    virtual void Draw(VECTOR position,VECTOR rotate) const;
protected:
    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    virtual void ModelSetMatrix(VECTOR position, VECTOR rotate) const;
    //�`�惂�f��
    int modelHandle;
};