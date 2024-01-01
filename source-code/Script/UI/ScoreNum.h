#pragma once
#include "NumUI.h"
#include "DxLib.h"
#include "UIManager.h"
/// <summary>
/// 合計スコアの表示
/// </summary>
class ScoreNum : private NumUI
{
public:
    /// <summary>
    /// スコアの評価の線引きを所得
    /// </summary>
    ScoreNum();
    /// <summary>
    /// highScoreUIの削除
    /// </summary>
    ~ScoreNum();
    /// <summary>
    /// スコアによって大きさ変更
    /// </summary>
    /// <param name="num">合計score</param>
    void Draw(int num)const override;
private:
    //前回のハイスコア
    int prevHiScore = 0;
    //上手にクリアしたときのスコアのライン
    int first = 0;
    //普通にクリアしたときのスコアのライン
    int second = 0;
    //なんとかクリアしたときのスコアのライン
    int third = 0;
    //secondより上のスコアになった時の文字のフォント
    float secondBorderFontSize = 0.9f;
    //thirdより上のスコアになった時の文字のフォント
    float thirdBorderFontSize = 0.85f;
    //thirdより下のスコアになった時の文字のフォント
    float thirdUnderFontSize = 0.8f;
    //ハイスコアの表記
    UIData highScoreUIData;
    //一番いいスコアの色
    VECTOR firstColor = VGet(255,215,0);
    //ちょっといいときの色
    VECTOR thirdColor = VGet(196,112,34);
    //二番目にいい時の色
    VECTOR secondColor = VGet(192, 192, 192);
    //最初になっているスコアの色
    VECTOR thirdUnderColor = VGet(100,100,100);
};