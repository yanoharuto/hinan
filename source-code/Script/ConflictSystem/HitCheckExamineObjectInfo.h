#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// 当たり判定で使う引数にして渡したい情報
/// </summary>
struct HitCheckInfo
{
    //ポジション
    VECTOR pos = {};
    //移動量
    VECTOR velocity = {};
    //半径
    float radius = 0;
    //オブジェクトの種類
    Object::ObjectTag tag;
    /// <summary>
    /// 当たり判定に必要な情報をセット
    /// </summary>
    /// <param name="obj">セットしたいオブジェクト</param>
    void SetExamineInfo(Object* const obj)
    {
        tag = obj->GetTag();
        pos = obj->GetPos();
        radius = obj->GetRadius();
    }
};