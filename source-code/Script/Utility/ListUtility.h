#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "DxLib.h"

/// <summary>
/// リストをベクターに変換する
/// </summary>
/// <typeparam name="T">リストに入っているクラス</typeparam>
/// <param name="list">ベクターにしたいリスト</param>
/// <returns>リストをベクターにしたもの</returns>
template<typename T>
static std::vector<T> ConvertListToVector(std::list<T> list)
{
    std::vector<T> newList(list.begin(), list.end());
    return newList;
}
/// <summary>
/// ベクターからリストにする
/// </summary>
/// <typeparam name="T">ベクターに入っているクラス</typeparam>
/// <param name="vector">リストにしたいベクター</param>
/// <returns>ベクターをリストにしたもの</returns>
template<typename T>
static std::list<T> ConvertVectorToList(std::vector<T> vector)
{
    std::list<T> newVec(vector.begin(), vector.end());
    return newVec;
}
/// <summary>
///　ベクターの中から特定の要素をイテレーターにして渡す
/// </summary>
/// <typeparam name="T">ベクターの中で格納されているクラス</typeparam>
/// <param name="vector">探したいイテレーターのあるベクター</param>
/// <param name="element">特定の要素</param>
/// <returns>ベクターの中に特定の要素がなかったらend()が返ってくる</returns>
template<typename T>
static std::vector<T*>::iterator FindVector(std::vector<T*>* vector,T* element)
{
    for (auto itr = (*vector).begin(); itr != (*vector).end(); itr++)
    {
        if ((*itr) == element)//探したい要素が見つかったらイテレーターを返す
        {
            return itr;
        }
    }
    return (*vector).end();
}
/// <summary>
/// リストの中から特定の要素をイテレーターにして渡す
/// </summary>
/// <typeparam name="T">リストの中で格納されているクラス</typeparam>
/// <param name="list">探したいイテレーターのあるリスト</param>
/// <param name="element">特定の要素</param>
/// <returns>リストの中に特定の要素がなかったらend()が返ってくる</returns>
template<typename T>
static std::list<T*>::iterator FindList(std::list<T*>* list, T* element)
{
    for (auto itr = (*list).begin(); itr != (*list).end(); itr++)
    {
        if ((*itr) == element)//探したい要素が見つかったらイテレーターを返す
        {
            return itr;
        }
    }
    return (*list).end();
}