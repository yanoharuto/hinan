#pragma once
#include "AssetManager.h"
namespace EffectInit
{
    /// <summary>
    /// エフェクトの種類
    /// </summary>
    enum class EffectKind
    {
        //車がぶつかった時のエフェクト
        carConflict ,
        //車が風を切っているときのエフェクト
        carWind ,
        //車が加速したときのエフェクト
        carTurbo,
        //車がダメージを受けた時のエフェクト
        carDamage,
        //回転半径が小さいレーザー
        littleRadiusLaserEffect ,
        //回転半径が大きいレーザー
        laser ,
        //レーザーの跡
        laserTrack ,
        //コインをゲットしたときのエフェクト
        getCollect,
        //爆弾の爆発
        bombExplosion,
        //コインの出すオーラ
        collectAura,
        //収集アイテムの方角を指すエフェクト
        comPath,
        //車の後ろから出すエフェクト
        burner,
        //車が速くなる前に出すエフェクト
        turboCourse,
        //勝利後の紙吹雪
        confetti,
        //ターボ前段階のバーナーエフェクト
        chargeBurner, 
        //高速移動中のバーナー
        turboBurner
    };
    /// <summary>
    /// エフェクトの初期化に必要なもの
    /// </summary>
    enum class EffectInitData
    {
        effectPath,//エフェクトのパス
        effectSize//エフェクトの大きさ
    };
}
using namespace EffectInit;
/// <summary>
/// エフェクトの保管庫
/// </summary>
class EffectManager final:public AssetManager
{
public:
    /// <summary>
    /// エフェクトを読み込んだり渡したりする
    /// </summary>
    EffectManager();
    /// <summary>
    /// エフェクトを解放
    /// </summary>
    ~EffectManager();
    /// <summary>
    /// エフェクトを読み込む
    /// </summary>
    /// <param name="kind">エフェクトの種類</param>
    static void LoadEffect(EffectKind kind);
    /// <summary>
    /// ロード済みの3Ⅾエフェクトを渡す
    /// </summary>
    /// <param name="kind">エフェクトの種類</param>
    /// <returns>3Ⅾエフェクトのハンドル</returns>
    static int GetPlayEffect3D(EffectKind kind);
    /// <summary>
    /// ロード済みの2Dエフェクトを渡す
    /// </summary>
    /// <param name="kind"></param>
    /// <returns>2Ⅾエフェクトのハンドル</returns>
    static int GetPlayEffect2D(EffectKind kind);
private:
    //エフェクトのハンドルが入るマップ
    static std::unordered_map <EffectKind, int> effectMap;
    //エフェクトのパスが入る文字列
    static std::vector<std::string> initDataVec;
    //jsonスキーマのパス
    static std::string schemaPath;
};