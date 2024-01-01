#include "ConflictManager.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ConflictProcessor.h"
#include "SphereHitChecker.h"
#include "Utility.h"
//当たった結果を反映させるクラスのマップ
std::vector<std::pair<std::unique_ptr<ConflictProcessor>, std::shared_ptr<SphereHitChecker>>> ConflictManager::processorKeyMap;
//当たっているか調べるクラスのリスト
std::vector <std::shared_ptr<SphereHitChecker>> ConflictManager::hitCheckList;
/// <summary>
/// 当たり判定を纏めて行うための奴
/// </summary>
ConflictManager::ConflictManager()
{
    processorKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// 当たり判定登録Map全消し
/// </summary>
ConflictManager::~ConflictManager()
{
    processorKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// 当たり判定追加
/// </summary>
/// <param name="hitChecker"></param>
void ConflictManager::AddHitChecker(std::shared_ptr<SphereHitChecker>& hitChecker)
{
    hitCheckList.push_back(std::move(hitChecker));
}
/// <summary>
/// 衝突処理実行役を追加
/// </summary>
/// <param name="conflictProcessor">追加したい衝突処理実行役</param>
/// <param name="hitChecker">呼びたいやつの当たり判定</param>
void ConflictManager::AddConflictProcessor(std::unique_ptr<ConflictProcessor>& conflictProcessor, std::shared_ptr<SphereHitChecker>& hitChecker)
{
    auto pair = std::make_pair(std::move(conflictProcessor), hitChecker);
    processorKeyMap.push_back(std::move(pair));
    AddHitChecker(hitChecker);
}

/// <summary>
/// デバッグ用の球当たり判定を見せる
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = hitCheckList.begin(); objIte != hitCheckList.end(); objIte++)
    {
       HitCheckInfo info = (*objIte)->GetHitExamineCheckInfo();
       DrawSphere3D(info.pos, info.radius, 4, GetColor(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE), GetColor(Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE, Utility::MAX_ONE_BYTE_RANGE), false);
    }
}
/// <summary>
/// 当たり判定をする
/// </summary>
void ConflictManager::Update()
{
    std::list<int> breakCheckerList;
    std::list<int> breakMapList;
    
    for (int i = 0; i < CONTAINER_GET_SIZE(processorKeyMap); i++)
    {       
        //衝突処理実行役が死んでいたら削除リスト行き
        if (processorKeyMap[i].first->IsDead())
        {
            breakMapList.push_back(i);
        }
        for (int j = 0; j < CONTAINER_GET_SIZE(hitCheckList); j++)
        {
            //削除リストに追加されてたら次の当たり判定を調べる
            if (std::find(breakCheckerList.begin(), breakCheckerList.end(), j) != breakCheckerList.end())continue;
            //当たり判定調査役
            auto hitChecker = hitCheckList.begin() + j;
            //当たり判定が死んでたら削除リスト行き
            if ((*hitChecker)->IsDead())
            {
                breakCheckerList.push_back(j);
            }
            //当たり判定が衝突処理実行役のものではないなら
            else if (*hitChecker != processorKeyMap[i].second)
            {

                Conflict(i,*hitChecker);
            }
        }
    }
    for (auto suffix = breakCheckerList.begin(); suffix != breakCheckerList.end(); suffix++)
    {
        auto brokenItr = (hitCheckList.begin() + (*suffix));
        auto shared = *brokenItr;
        hitCheckList.erase(brokenItr);
        SAFE_RESET(shared);
    } 
    for (auto suffix = breakMapList.begin(); suffix != breakMapList.end(); suffix++)
    {
        SAFE_RESET((processorKeyMap.begin() + *suffix)->first);
        SAFE_RESET((processorKeyMap.begin() + *suffix)->second);
        processorKeyMap.erase(processorKeyMap.begin() + *suffix);
    }
}

void ConflictManager::Conflict(int i,std::shared_ptr<SphereHitChecker>& hitChecker)
{
    auto checkInfo = processorKeyMap[i].first->GetHitExamineCheckInfo();
    //衝突処理実行
    processorKeyMap[i].first->OnConflict((hitChecker)->HitCheck(checkInfo));

    for (auto itr = processorKeyMap.begin(); itr != processorKeyMap.end(); itr++)
    {
        if ((*itr).second == hitChecker)
        {
            (*itr).first->OnConflict(processorKeyMap[i].second->HitCheck((*itr).first->GetHitExamineCheckInfo()));
            break;
        }
    }
}
