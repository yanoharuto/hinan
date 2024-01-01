#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include "InitObjKind.h"
#include "EditObjectData.h"

class EditorDrawModel;
class EditorCircleFlyShipDrawModel;
/// <summary>
/// �ҏW�����̗���
/// </summary>
class EditorDrawModelManager final
{
public:
    /// <summary>
    /// �ҏW���̕`��ɕK�v�Ȃ��̂��m��
    /// </summary>
    EditorDrawModelManager();
    /// <summary>
    /// �`��Ɏg���N���X�̊J��
    /// </summary>
    ~EditorDrawModelManager();
    /// <summary>
    /// �����̈ʒu�ɕ`��
    /// </summary>
    /// <param name="placeData">�`�悵�Ăق����ʒu</param>
    void Draw(PlacementData placeData) const;
    /// <summary>
    /// �����̈ʒu�ɕ`��
    /// </summary>
    /// <param name="placeData">�`�悵�Ăق����ʒu���܂Ƃ߂�����</param>
    void Draw(std::vector<PlacementData> placeData) const;
private:
    //�`��N���X
    std::unordered_map<ObjectInit::InitObjKind,EditorDrawModel*> drawModelMap;
    //�~�`�w��g�ޓG�̕`��N���X
    EditorCircleFlyShipDrawModel* drawCircleFlyShip;
};