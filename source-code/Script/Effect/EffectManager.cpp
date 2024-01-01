#include <unordered_map>
#include <memory>
#include <iostream>
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "CSVFileLoader.h"
#include "JsonFileLoader.h"
#include "Utility.h"
#include "UIDrawer.h"
//エフェクトのハンドルが入るマップ
std::unordered_map <EffectKind, int> EffectManager:: effectMap;
//エフェクトのパスが入る文字列
std::vector<std::string> EffectManager::initDataVec;
//jsonスキーマのパス
std::string EffectManager::schemaPath = "effectSchema.json";
/// <summary>
/// エフェクトの保管庫
/// </summary>
EffectManager::EffectManager()
{
    effectMap.clear();
    initDataVec = GetAssetList(AssetList::effect);
}
/// <summary>
/// エフェクトを解放
/// </summary>
EffectManager::~EffectManager()
{
    for (auto ite = effectMap.begin(); ite != effectMap.end(); ite++)
    {
        DeleteEffekseerEffect((*ite).second);
    }
    effectMap.clear();
}
/// <summary>
/// エフェクトを読み込む
/// </summary>
/// <param name="kind">エフェクトの種類</param>
void EffectManager::LoadEffect(EffectKind kind)
{
    std::vector<std::string> dataVec;
    if (!effectMap.contains(kind))
    {
        if (IsExistJsonFile())//json版
        {
            auto json = std::make_unique<JsonFileLoader>(initDataVec[static_cast<int>(kind)], schemaPath);
            dataVec.push_back(json->GetLoadString("effectPass"));
            dataVec.push_back(std::to_string(json->GetLoadFloat("effectSize")));
            SAFE_RESET(json);
        }
        else
        {
            //データ読み取り
            auto initDataFile = std::make_unique<CSVFileLoader>(initDataVec[static_cast<int>(kind)]);
            dataVec = initDataFile->GetStringData();
            SAFE_RESET(initDataFile);
        }
        //エフェクトのアセットのパス
        const char* effectPathStr = dataVec[static_cast<int>(EffectInitData::effectPath)].c_str();
        //エフェクトの大きさ
        float size = STR_TO_F(dataVec[static_cast<int>(EffectInitData::effectSize)]);
        //エフェクトの読み込みと大きさをセット
        int effectHandle = LoadEffekseerEffect(effectPathStr, size);
        effectMap.insert(std::make_pair(kind, effectHandle));
    }
}
/// <summary>
/// ロード済みの3Ⅾエフェクトを渡す
/// </summary>
/// <param name="kind">エフェクトの種類</param>
/// <returns>3Ⅾエフェクトのハンドル</returns>
int EffectManager::GetPlayEffect3D(EffectKind kind)
{
    int isPlay = -1;
    //ロード済みなら渡す
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer3DEffect(effectMap[kind]);
    }
    return isPlay;
}
/// <summary>
/// ロード済みの2Dエフェクトを渡す
/// </summary>
/// <param name="kind"></param>
/// <returns>2Ⅾエフェクトのハンドル</returns>
int EffectManager::GetPlayEffect2D(EffectKind kind)
{
    int isPlay = -1;
    //ロード済みなら渡す
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer2DEffect(effectMap[kind]);
    }
    return isPlay;
}