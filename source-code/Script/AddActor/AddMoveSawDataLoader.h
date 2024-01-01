#pragma once
#include "AddObjectDataLoader.h"
/// <summary>
/// 移動丸鋸の情報を読み取る
/// </summary>
class AddMoveSawDataLoader final: public AddObjectDataLoader
{
public:
    /// <summary>
    /// 移動丸鋸の情報を読み取る
    /// </summary>
    AddMoveSawDataLoader();

private:
    //丸鋸の追加情報スキーマ
    const std::string addDataSchema = "moveSawSchema.json";
};

