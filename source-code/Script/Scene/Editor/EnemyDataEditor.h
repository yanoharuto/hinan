#pragma once
#include "StageDataEditor.h"
#include <unordered_map>
#include <vector> 
/// <summary>
/// �G�̕ҏW�N���X
/// </summary>
class EnemyDataEditor final: public StageDataEditor
{
public:
    /// <summary>
/// �G�̕ҏW�N���X
/// </summary>
    EnemyDataEditor(InitObjKind enemyKind);
private:
    //�z�u���̏����Ă���t�@�C���̃p�X
    static const std::string loadFileName;
};