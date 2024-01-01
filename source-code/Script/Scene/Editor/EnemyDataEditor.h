#pragma once
#include "StageDataEditor.h"
#include <unordered_map>
#include <vector> 
/// <summary>
/// 敵の編集クラス
/// </summary>
class EnemyDataEditor final: public StageDataEditor
{
public:
    /// <summary>
/// 敵の編集クラス
/// </summary>
    EnemyDataEditor(InitObjKind enemyKind);
private:
    //配置情報の書いてあるファイルのパス
    static const std::string loadFileName;
};