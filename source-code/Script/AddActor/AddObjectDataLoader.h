#pragma once
#include "AssetManager.h"
#include <string>
#include <vector>
/// <summary>
/// オブジェクトの追加情報を読み取るクラス
/// </summary>
class AddObjectDataLoader abstract:public AssetManager
{
public:
    enum class AddData;
    /// <summary>
    /// 追加情報を読み取る
    /// </summary>
    AddObjectDataLoader();
    /// <summary>
    /// 追加情報を文字列で渡す
    /// </summary>
    /// <returns>文字列で渡す</returns>
    virtual std::vector<std::string> GetLoadData()const { return loadData; };
    //追加情報の種類
    enum class AddData
    {
        playerSpeed,//プレイヤーの移動情報
        circleFlyShip,//円陣組んでる飛行船の追加情報
        upDownFlyShip,//上下に移動する飛行船の追加情報
        bomberShip,//爆弾落とす飛行船の追加情報
        moveSaw//移動回転のこぎりの追加情報
    };
protected:
    //追加情報文字列
    std::vector<std::string> loadData;
    //読み取った追加情報のリスト
    std::vector<std::string> addDataList;
};