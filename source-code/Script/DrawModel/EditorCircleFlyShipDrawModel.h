#pragma once
#include "EditorDrawModel.h"

/// <summary>
/// �~�`��ɐw�`��g�ޓG�̕`��S��
/// </summary>
class EditorCircleFlyShipDrawModel final : public EditorDrawModel
{
public:
    /// <summary>
    /// �~�`��s���͕ҏW���͐w�`�̔�s�@�Z�߂ĕ`�悷��
    /// ���̂��߂ɕK�v�ȏ���������
    /// </summary>
    EditorCircleFlyShipDrawModel();
    /// <summary>
    /// �`�悷��
    /// </summary>
    /// <param name="data">�z�u���</param>
    void Draw(PlacementData data)const override;
    /// <summary>
    /// ������model�̈ʒu���]�ɍ��킹�ĕ`�悷��
    /// </summary>
    /// <param name="drawObj">�ʒu�Ƃ������Ă����炤</param>
    void Draw(VECTOR position, VECTOR rotate)const override;
private:
    /// <summary>
    /// ������
    /// </summary>
    void Init();
    //���j�b�g�̐�
    int uniNum = 0;
    //�e���j�b�g�̕����ւ̊p�x
    float uniDirRota = 0.0f;
    //���j�b�g���m�̋���
    float uniBetween=0.0f;
};