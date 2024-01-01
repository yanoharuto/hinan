#pragma once
#include <map>
#include <string>
#include <vector>
#include "DxLib.h"
#include "AssetManager.h"
namespace SoundInit
{
    /// <summary>
    /// 音を鳴らすのに必要なパラメータ-
    /// </summary>
    enum class SoundParamator
    {
        //音の相対パス
        soundPath ,
        //音量
        soundVolume,
        //音が聞こえる範囲
        soundRadius
    };
    /// <summary>
    /// 音の種類
    /// </summary>
    enum class SoundKind
    {
        //爆撃機の飛ぶ音
        bomberShipFlight,
        //プレイヤーの動くときの音
        playerFlight,
        //プレイヤーのダメージを受けた時の音
        playerDamage,
        //コインをゲットしたときの音
        coinGet,
        //カウントダウン
        countDown,
        //遊んでいるときのBGM
        playBGM,
        //拍手
        clap,
        //ゲーム開始
        fanfare,
        //タイトルのBGM
        titleBGM,
        //スコアを表示するときに鳴る音
        scoreStartSE,
        //スコアを表示し終わったときに鳴る音
        scoreEndSE,
        //次のシーンに行く時の音
        sceneNextSE,
        //スコア表示したときのファンファーレ
        gameEndFanfare,
        //プレイヤーがチャージしたときの音
        playerCharge 
    };
}
using namespace SoundInit;
class SoundPlayer final :public AssetManager
{
public:
    /// <summary>
    /// 全音のパスを把握
    /// </summary>
    SoundPlayer();
    /// <summary>
    /// 音を全部止めて解放
    /// </summary>
    ~SoundPlayer();
    /// <summary>
    /// 効果音を鳴らす
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void Play2DSE(SoundKind kind);
    /// <summary>
    /// 3d空間での音を鳴らす
    /// </summary>
    /// <param name="pos">なっている音の位置</param>
    /// <param name="kind">音の種類</param>
    static void Play3DSE(SoundKind kind);
    /// <summary>
    /// 鳴らしたい音の位置を変える
    /// </summary>
    /// <param name="pos">なっている音の位置</param>
    /// <param name="kind">音の種類</param>
    static void SetPosition3DSound(VECTOR pos, SoundKind kind);
    /// <summary>
    /// 音を鳴らす
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void PlayBGM(SoundKind kind);
    /// <summary>
    /// 音を止める
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void StopSound(SoundKind kind);
    /// <summary>
    /// 全ての音を止める
    /// </summary>
    static void StopAllSound();
    /// <summary>
    /// 音をロードして音量を初期化して使いまわせるようにする
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void LoadAndInitSound(SoundKind kind);
    /// <summary>
    /// ３Dの音をロードして音量を初期化して使いまわせるようにする
    /// </summary>
    /// <param name="kind">音の種類</param>
    static void LoadAndInit3DSound(SoundKind kind);
    /// <summary>
    /// その音が鳴ってるかどうか調べる
    /// </summary>
    /// <param name="kind">音の種類</param>>
    /// <returns>なってたらTrue</returns>
    static bool IsPlaySound(SoundKind kind);
    
private:
    //modelのアドレスを貰うとモデルハンドルを返す
    static std::map<SoundKind, int> soundHandleMap;
    //初期化ファイルに入っている音の情報パスのコンテナ
    static std::vector <std::string> initFilePathData;
    static const std::string soundSchema;
};