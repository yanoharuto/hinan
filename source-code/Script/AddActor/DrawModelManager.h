#pragma once
#include "AssetManager.h"
/// <summary>
/// 描画モデルの保存
/// </summary>
class DrawModelManager final:AssetManager
{
public:
    //複製準備
    DrawModelManager();
    /// <summary>
    /// 各モデルの情報をデリート
    /// </summary>
    ~DrawModelManager()override;
    /// <summary>
    /// modelをロードして渡す
    /// </summary>
    /// <param name="assetPath"></param>
    /// <returns>すでにロードしてたら複製</returns>
    int Get3DModelAssetHandle(std::string assetPath);
private:
    
    /// 描画モデルハンドル
    static std::unordered_map <std::string, int> modelMap;
};