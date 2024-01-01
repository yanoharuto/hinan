#pragma once
#include<iostream>
#include<memory>
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// オブジェクトの監視役
/// </summary>
class ObjectObserver
{
public:
    /// <summary>
    /// オブジェクトの監視役
    /// </summary>
    /// <param name="setSubject">監視したいオブジェクト</param>
    ObjectObserver(std::shared_ptr<Object>  setSubject);
    /// <summary>
    /// 監視対象の開放
    /// </summary>
    ~ObjectObserver();
    /// <summary>
    /// 監視対象の位置を渡す
    /// </summary>
    /// <returns></returns>
    virtual VECTOR GetSubjectPos() const;
    /// <summary>
    /// 監視対象の向き
    /// </summary>
    /// <returns></returns>
    virtual VECTOR GetSubjectDir() const;
    /// <summary>
    /// 監視対象の状態
    /// </summary>
    /// <returns></returns>
    virtual Object::ObjectState GetSubjectState()const;
protected:
    /// <summary>
    /// 子クラス用のコンストラクタ
    /// </summary>
    ObjectObserver() {};
    //監視している物
    std::shared_ptr<Object> subject;
};