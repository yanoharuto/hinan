#include "ConflictManager.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ConflictProcessor.h"
#include "SphereHitChecker.h"
#include "Utility.h"
//�����������ʂ𔽉f������N���X�̃}�b�v
std::vector<std::pair<std::unique_ptr<ConflictProcessor>, std::shared_ptr<SphereHitChecker>>> ConflictManager::processorKeyMap;
//�������Ă��邩���ׂ�N���X�̃��X�g
std::vector <std::shared_ptr<SphereHitChecker>> ConflictManager::hitCheckList;
/// <summary>
/// �����蔻���Z�߂čs�����߂̓z
/// </summary>
ConflictManager::ConflictManager()
{
    processorKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// �����蔻��o�^Map�S����
/// </summary>
ConflictManager::~ConflictManager()
{
    processorKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// �����蔻��ǉ�
/// </summary>
/// <param name="hitChecker"></param>
void ConflictManager::AddHitChecker(std::shared_ptr<SphereHitChecker>& hitChecker)
{
    hitCheckList.push_back(std::move(hitChecker));
}
/// <summary>
/// �Փˏ������s����ǉ�
/// </summary>
/// <param name="conflictProcessor">�ǉ��������Փˏ������s��</param>
/// <param name="hitChecker">�Ăт�����̓����蔻��</param>
void ConflictManager::AddConflictProcessor(std::unique_ptr<ConflictProcessor>& conflictProcessor, std::shared_ptr<SphereHitChecker>& hitChecker)
{
    auto pair = std::make_pair(std::move(conflictProcessor), hitChecker);
    processorKeyMap.push_back(std::move(pair));
    AddHitChecker(hitChecker);
}

/// <summary>
/// �f�o�b�O�p�̋������蔻���������
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
/// �����蔻�������
/// </summary>
void ConflictManager::Update()
{
    std::list<int> breakCheckerList;
    std::list<int> breakMapList;
    
    for (int i = 0; i < CONTAINER_GET_SIZE(processorKeyMap); i++)
    {       
        //�Փˏ������s��������ł�����폜���X�g�s��
        if (processorKeyMap[i].first->IsDead())
        {
            breakMapList.push_back(i);
        }
        for (int j = 0; j < CONTAINER_GET_SIZE(hitCheckList); j++)
        {
            //�폜���X�g�ɒǉ�����Ă��玟�̓����蔻��𒲂ׂ�
            if (std::find(breakCheckerList.begin(), breakCheckerList.end(), j) != breakCheckerList.end())continue;
            //�����蔻�蒲����
            auto hitChecker = hitCheckList.begin() + j;
            //�����蔻�肪����ł���폜���X�g�s��
            if ((*hitChecker)->IsDead())
            {
                breakCheckerList.push_back(j);
            }
            //�����蔻�肪�Փˏ������s���̂��̂ł͂Ȃ��Ȃ�
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
    //�Փˏ������s
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
