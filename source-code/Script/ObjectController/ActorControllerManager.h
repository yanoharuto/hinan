#pragma once
#include <list>
#include <memory>
#include <iostream>
class AddableObjectController;
class ActorController;
class DamageObjectGenerator;
class EnemyGenerator;
class BomberController;
class RotatingLaserController;
class CollectItemObserver;
class PlayerObserver;
class CameraObserver;
/// <summary>
/// actorの動きを制御している物を全部束ねて動かす
/// </summary>
class ActorControllerManager final
{
public:
    /// <summary>
    /// ゲーム中に使うオブジェクトの管理クラスの確保
    /// </summary>
    /// <param name="collectItemObserver">収集アイテムが取られたりしたら教えてもらう</param>
    ActorControllerManager();
    /// <summary>
    /// 敵の管理クラスやステージのオブジェクトなどをすべて解放
    /// </summary>
    ~ActorControllerManager();
    /// <summary>
    /// 更新
    /// </summary>
    void Update();
    /// <summary>
    /// ゲーム開始前更新
    /// </summary>
    void PrepareGame();
    /// <summary>
    /// 各アクターの描画
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver> cameraObserever)const;
    /// <summary>
    /// プレイヤーのシェアポインタを所得
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<PlayerObserver> GetSharedPlayerObserver()const { return playerObserver; };
    /// <summary>
    /// 収集アイテムのシェアポインタを所得
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<CollectItemObserver> GetSharedCollectObserver()const { return collectObserver; }
private:
    /// <summary>
    /// 2つのActor管理クラスどちらでも使えるゲーム開始前更新
    /// </summary>
    /// <typeparam name="controllerClass">Actor管理クラス</typeparam>
    /// <param name="controllerList">controllerClassを纏めたリスト</param>
    template<typename controllerClass>
    void PrepareGame(std::list<std::shared_ptr<controllerClass>> controllerList);
    /// <summary>
    /// 2つのActor管理クラスどちらでも使える更新
    /// </summary>
    /// <typeparam name="controllerClass">Actor管理クラス</typeparam>
    /// <param name="controllerList">controllerClassを纏めたリスト</param>
    template<typename controllerClass>
    void Update(std::list<std::shared_ptr<controllerClass>> controllerList);
    /// <summary>
    /// 2つのActor管理クラスどちらでも使える描画
    /// </summary>
    /// <typeparam name="controllerClass">Actor管理クラス</typeparam>
    /// <param name="controllerList">controllerClassを纏めたリスト</param>
    template<typename controllerClass>
    void Draw(std::list<std::shared_ptr<controllerClass>> controllerList, std::weak_ptr<CameraObserver> cameraObserever)const;
    /// <summary>
    ///　敵生成処理
    /// </summary>
    void GenerateEnemyProcess();
    //収集アイテムの数
    int collectNum = 0;
    //色んなオブジェクトの管理クラス
    std::list<std::shared_ptr<ActorController>> actorControllerList;
    //追加可能クラスActor管理クラスのリスト
    std::list<std::shared_ptr<AddableObjectController>> addableActorControllerList;
    //敵が発射してきたりしたアイテムを作成
    std::shared_ptr<DamageObjectGenerator> damageObjGenerator;
    //収集アイテムが回収されたかどうかを教えてもらう
    std::shared_ptr<CollectItemObserver> collectObserver;
    //収集アイテムが回収されると増える敵を作成する
    std::unique_ptr<EnemyGenerator> enemyGenerator;
    //プレイヤーの情報通達クラス
    std::shared_ptr<PlayerObserver> playerObserver;
};