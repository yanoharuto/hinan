#pragma once
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "DrawModel.h"
class Actor;
class DrawModel;
class CameraObserver;
/// <summary>
/// 1つの種類のactorの子クラスを動かすために使う
/// </summary>
class ActorController abstract
{
public:
    /// <summary>
    /// 操作するオブジェクトの名前を下さい
    /// </summary>
    ActorController(ObjectInit::InitObjKind kind) { controllObjKind = kind; };
    /// <summary>
    /// 描画役とオブジェクトのデリート
    /// </summary>
    virtual ~ActorController();
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update();
    /// <summary>
    /// ゲーム開始準備処理
    /// </summary>
    virtual void PrepareGame();
    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const;
protected:
    /// <summary>
    /// 描画役とActorListの解放
    /// </summary>
    void DeleteActorListAndDrawModel();
    /// <summary>
    /// 当たり判定を引数に追加
    /// </summary>
    /// <param name="hitCheckOwner">当たり判定の持ち主</param>
    void AddConflictManagement(std::shared_ptr<Actor>& hitCheckOwner);
    //このリストを回す
    std::list <std::shared_ptr<Actor>> actorList;
    //描画担当
    std::unique_ptr<DrawModel> drawModel;
    //操作するオブジェクトの種類
    ObjectInit::InitObjKind controllObjKind;
};