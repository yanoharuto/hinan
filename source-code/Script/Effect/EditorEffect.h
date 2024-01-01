#pragma once
#include "EditObjectData.h"
class StageDataEditor;
/// <summary>
/// Editor�Ŏg���G�t�F�N�g
/// </summary>
class EditorEffect
{
public:
    /// <summary>
    /// �G�t�F�N�g�ǂݍ���
    /// </summary>
    EditorEffect();
    /// <summary>
    /// �G�t�F�N�g�I��
    /// </summary>
    ~EditorEffect();
    /// <summary>
    /// �G�t�F�N�g�̌����ƈʒu�̕ύX
    /// </summary>
    /// <param name="editObjPlaceData">���ҏW���Ă���I�u�W�F�N�g�̈ʒu</param>
    void UpdatePositionAndDirection(PlacementData const editObjPlaceData);
    /// <summary>
    /// �G�f�B�^�[��ʂŎg���G�t�F�N�g�̃X�^�[�g
    /// </summary>
    void Start();
    /// <summary>
    /// �G�f�B�^�[��ʂŎg���G�t�F�N�g�̃X�g�b�v
    /// </summary>
    void Stop();
private:
    //�ҏW���̈ʒu�̕�����₷���Ȃ�G�t�F�N�g
    int posEffect = -1;
    //������������₷���Ȃ�G�t�F�N�g
    int dirEffect = -1;
};