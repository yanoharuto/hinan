#pragma once
#include "DrawModel.h"
#include "EditObjectData.h"

class EditorObject;
/// <summary>
/// �e�ҏW�I�u�W�F�N�g�̕`��S����
/// </summary>
class EditorDrawModel:public DrawModel
{
public:
    /// <summary>
    /// �e�ҏW�I�u�W�F�N�g�̕`��S����
    /// </summary>
    /// <param name="kind">�`�悷�镨</param>
    EditorDrawModel(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �����̏ꏊ�ɕ`��
    /// </summary>
    /// <param name="data"></param>
    virtual void Draw(PlacementData data)const;
protected:
    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    /// <param name="pos">�ʒu</param>
    /// <param name="dir">����</param>
    void ModelSetMatrix(VECTOR pos,VECTOR dir) const;
    //�I������Ă���Ȃ炿����ƈʒu�������Ȃ�
    const float selectPosY = 75.0f;
};