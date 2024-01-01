#include "DrawModelManager.h"
#include "DxLib.h"

//modelのアドレスを貰うとモデルハンドルを返す
std::unordered_map<std::string, int> DrawModelManager::modelMap;
//複製準備
DrawModelManager::DrawModelManager()
{
    modelMap.clear();
}
/// <summary>
/// 各モデルの情報をデリート
/// </summary>
DrawModelManager::~DrawModelManager()
{
    for (auto ite = modelMap.begin(); ite != modelMap.end(); ite++)
    {
        MV1DeleteModel((*ite).second);
    }
    modelMap.clear();
}
/// <summary>
/// modelをロードして渡す
/// </summary>
/// <param name="assetPath"></param>
/// <returns>すでにロードしてたら複製</returns>
int DrawModelManager::Get3DModelAssetHandle(std::string assetPath)
{
    if (modelMap.contains(assetPath))//すでに追加ロードされていたら複製
    {
        return MV1DuplicateModel(modelMap[assetPath]);
    }
    //まだロードしてないならロードする
    modelMap.insert(std::make_pair(assetPath, MV1LoadModel(assetPath.c_str())));
    return modelMap[assetPath];
}
