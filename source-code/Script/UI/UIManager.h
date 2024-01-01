#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "AssetManager.h"
namespace UIInit
{
    /// <summary>
    /// UIの種類
    /// </summary>
    enum class UIKind
    {
        //ゲームの目標
        gamePurose,
        //カウントダウン
        countDownUI,
        //コレクトアイテムの残り数などのUI
        collectItemFrameUI,
        //収集物のスコアの文字
        collectScore,
        //収集物のスコア
        collectScoreIcon,
        //ダメージを受けると減少するスコアの文字
        damageScore,
        //ダメージを受けると減少するスコア
        damageScoreNum,
        //収集アイテムの最初の数についてのUI
        allCollectItemNum,
        //操作説明
        manual,
        //小数点
        point,
        //レーダー
        radar,
        //タイトルロゴ
        tilteLogo,
        //タイマーの枠
        timerFrame,
        //残り時間スコアの文字
        timeScore,
        //残り時間のスコア
        timeScoreNum,
        //合計スコアの文字
        totalScore,
        //合計スコア
        totalScoreNum,
        //収集アイテムのもうゲットした数について
        getCollectItemNum,
        //残り時間
        timeNum,
        //メニュー画面の枠
        menuFrame,
        //プレイ続行
        playUI,
        //リトライ
        retryUI,
        //メニュー画面のカーソル
        menuCursor,
        //ゲーム終了UI
        exitUI,
        //タイトル画面でステージ選択をするときに使う
        stageName,
        //タイトルスペースキー催促
        titlePressSpaceKey,
        //タイトル画面に表示するハイスコア
        titleHighScore,
        //タイトル画面に表示するハイスコア数字
        titleHiScoreNum,
        //カウントダウン終了時
        onGameStartCountDownEnd,
        //誉め言葉
        PraiseWord,
        //ゲーム終了時のカウントダウン
        onGameEndCountDownEnd,
        //残りの収集アイテムの数
        remainingCollectItemNum,
        //残りの収集アイテムについてのフレーズ
        remainingCollectItemPhrase,
        //収集アイテムのアイコン
        collectIcon,
        //収集アイテムの集める数
        collectTargetNumberUI,
        //リザルトスペースキー催促
        resultSpaceKey,
        //チャージ方法説明マニュアル
        chargeManual,
        //ターボ説明マニュアル
        turboManual,
        //左ボタン
        leftButton,
        //右のボタン
        rightButton,
        //下ボタン
        downButton,
        //ゲーム終了アナウンス
        finishAnnounce,
        //タイトルに戻るボタン
        returnTitleBottonUI,
        //操作方法の後ろに置いておくシート
        playManualSheat,
        //タイトルでステージを決定するときのボタン
        stageSelectButton,
        //パッドで遊ぶ場合の下ボタン
        xDownButton,
        //そのステージで二番目にいいスコア
        titleSecondScoreNum,
        //そのステージで3番目にいいスコア
        titleThirdScoreNum,
        //ランキングの１
        rank1,
        //ランキングの２
        rank2,
        //ランキングの３
        rank3,
        //編集したステージを遊ぶためのUI
        playEditStage,
        //マウス
        editMenu,
        //右クリックしたときのマウス
        rightHoldMouse,
        //編集時の操作説明
        editManual
    };

    /// <summary>
    /// UIの初期化情報　数字は読み込み段数
    /// </summary>
    enum class InitUIData
    {
        //描画場所X
        drawX ,
        //Y
        drawY ,
        //画像横幅
        width ,
        //画像縦幅
        height,
        //横幅分割数
        xNum,
        //縦分割数
        yNum,
        //画像の相対パス
        graphPath,
        //大きさ
        size,
        //分割してある場合のコマ送りスピード
        frameSpeed
    };
    /// <summary>
    /// UIで実際に使う情報
    /// </summary>
    struct  UIData
    {
        //描画場所X
        int x = 0;
        //描画場所Y
        int y = 0;
        //分割後の画像横幅
        int width = 0;
        //分割後の画像縦幅
        int height = 0;
        //画像ハンドル
        std::vector<int> dataHandle;
        //大きさ
        float size = 0.0f;
        //コマ送り速度
        float frameSpeed = 0.0f;
    };
}
using namespace UIInit;
/// <summary>
/// UIを纏めるマネージャー
/// </summary>
class UIManager final:public AssetManager
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    UIManager();
    /// <summary>
    /// UIを所得
    /// </summary>
    /// <param name="uiKind">所得したいUIの種類</param>
    /// <returns>UIの描画に必要な情報を返す</returns>
    static UIData CreateUIData(UIKind uiKind);
    /// <summary>
    /// 引数のUIの画像を削除する
    /// </summary>
    /// <param name="ui">消したいUI画像</param>
    static void DeleteUIGraph(UIData* ui);
 private:
     /// <summary>
     /// UIの情報を所得
     /// </summary>
     /// <param name="uiKind">所得したいUI</param>
     /// <returns>UIの情報をまとめた構造体</returns>
     static UIData CreateUIData(int kindNum);
     //全てのUIのパス
    static std::vector<std::string> uiPathVec;
    //UI所得に使うスキーマのパス
    static std::string shemaPath;

};