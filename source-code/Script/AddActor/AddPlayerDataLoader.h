#pragma once
#include "AddObjectDataLoader.h"
/// <summary>
/// プレイヤーの追加情報読み取りクラス
/// </summary>
class AddPlayerDataLoader final: public AddObjectDataLoader
{
public:
    /// <summary>
    /// プレイヤーの追加情報を所得
    /// </summary>
    AddPlayerDataLoader();
private:
    //プレイヤーの追加情報スキーマ
    const std::string addDataSchema = "playerSpeedSchema.json";
};

