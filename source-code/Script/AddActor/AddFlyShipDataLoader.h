#pragma once
#include "AddObjectDataLoader.h"
/// <summary>
/// 飛行船の追加情報読み取りクラス
/// </summary>
class AddFlyShipDataLoader final:public AddObjectDataLoader
{
public:
    /// <summary>
    /// 飛行船の情報を読み取る
    /// </summary>
    /// <param name="data">読み取る飛行船</param>
    AddFlyShipDataLoader(AddData data);
private:
    //飛行船の追加情報スキーマ
    const std::string addDataSchema = "flyShipAddDataSchema.json";
};

