#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "InitActor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class AddableObjectController;
using namespace ObjectInit;
/// <summary>
/// 敵機の生成を行う
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
    /// 敵機位置についての初期化する
    /// </summary>
    EnemyGenerator();
    /// <summary>
    /// 敵コントローラーに位置情報を教えて追加する
    /// </summary>
    /// <param name="collectNum">プレイヤーが収集したアイテム数</param>
    /// <param name="addObjController">敵コントローラー</param>
    void GenerateEnemys(int collectNum, std::weak_ptr<AddableObjectController>& addObjController);
private:
    /// <summary>
    /// エネミーの配置情報を渡す
    /// </summary>
    /// <param name="collectNum">今の収集アイテムの所得数</param>
    /// <returns>エネミーの配置情報</returns>
    std::vector<PlacementData> GetNowEnemyEditData(int getCollectNum);
    
    //敵の位置まとめ
    std::vector<PlacementData> editDataVec;
};