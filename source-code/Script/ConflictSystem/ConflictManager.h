#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include <iostream>
class ConflictProcessor;
class SphereHitChecker;
struct CollisionResultInfo;
/// <summary>
///  当たり判定を纏めて行うための奴
/// </summary>
class ConflictManager
{
public:
    /// <summary>
    /// 当たり判定を纏めて行うための奴
    /// </summary>
    ConflictManager();
    /// <summary>
    /// 当たり判定登録Map全消し
    /// </summary>
    ~ConflictManager();
    /// <summary>
    /// 当たり判定追加
    /// </summary>
    /// <param name="hitChecker">当たり判定</param>
    static void AddHitChecker(std::shared_ptr<SphereHitChecker>& hitChecker);
    static void AddConflictProcessor(std::unique_ptr<ConflictProcessor>& conflictProcessor,std::shared_ptr<SphereHitChecker>& hitChecker);
    /// <summary>
    /// デバッグ用球を出す
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// 何か衝突している物がないか調べる
    /// </summary>
    void Update();
private:
    void Conflict(int i, std::shared_ptr<SphereHitChecker>& hitChecker);
    //当たった結果を反映させるクラスのマップ
    static std::vector<std::pair<std::unique_ptr<ConflictProcessor>, std::shared_ptr<SphereHitChecker>>> processorKeyMap;
    //当たっているか調べるクラスのリスト
    static std::vector<std::shared_ptr<SphereHitChecker>> hitCheckList;
};