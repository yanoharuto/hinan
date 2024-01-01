#pragma once
#include <memory>
#include <iostream>
class ObjectObserver;
class BomberController;
class RotatingLaserController;
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
class DamageObjectGenerator final
{
public:
    /// <summary>
    /// ダメージ判定のある物の種類
    /// </summary>
    enum DamageObjectKind
    {
        bomber,//爆弾
        laser//レーザー
    };
    /// <summary>
    /// レーザーと爆弾の管理クラスを追加
    /// </summary>
    /// <param name="laserController">レーザー管理クラス</param>
    /// <param name="bombController">爆弾管理クラス</param>
    DamageObjectGenerator(std::shared_ptr<RotatingLaserController>& laserController,std::shared_ptr<BomberController> bombController);
    /// <summary>
    /// レーザーと爆弾の管理クラスを解放
    /// </summary>
    ~DamageObjectGenerator();
    /// <summary>
    /// ダメージを与えるオブジェクトを生成
    /// </summary>
    /// <param name="itemTag">作成したいオブジェクトの種類</param>
    /// <param name="sub">発射した人の情報を渡す</param>
    void GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub);
private:
    //回転レーザー管理クラス
    std::shared_ptr<RotatingLaserController> rotaLaserController;
    //爆弾管理クラス
    std::shared_ptr<BomberController> bomberController;
};