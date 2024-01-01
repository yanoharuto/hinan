#pragma once
#include <string>
class StageDataEditor;
/// <summary>
/// 編集中の操作説明
/// </summary>
class EditManual final
{
public:
    /// <summary>
    /// フォントサイズと表示位置の調整
    /// </summary>
    EditManual();
    /// <summary>
    /// 編集操作説明表示
    /// </summary>
    void DrawEditManualString()const;
    /// <summary>
    /// 何を編集するか選択中の操作説明表示
    /// </summary>
    void DrawSelectManualString()const;
private:
    /// <summary>
    /// 編集時も選択中でも描画する操作説明
    /// </summary>
    /// <param name="x">描画開始X</param>
    /// <param name="y">描画開始Y</param>
    void DrawCommonString(int x, int y)const;
    /// <summary>
    /// 文字列を書くXの場所を決める
    /// </summary>
    /// <param name="prevStr">直前に書いた文字</param>
    /// <param name="nowX">今のX座標</param>
    /// <returns>次に書くべきX座標</returns>
    int GetNextDrawX(std::string prevStr, int nowX)const;
    /// <summary>
    /// 説明文の描画
    /// </summary>
    /// <param name="drawStr">説明文</param>
    /// <param name="x">描画位置X</param>
    /// <param name="y">描画位置Y</param>
    void DrawManualString(std::string drawStr,int x,int y)const;
    //十字編集中
    const std::string selectCrossKeyAction="十字キー編集物変更";
    //十字選択中
    const std::string editCrossAction="十字キー編集物移動";
    //SpaceKey選択中
    const std::string selectSpaceKeyAction="spaceで編集開始";
    //SpaceKey編集中
    const std::string editSpaceKeyAction="spaceで配置";
    //DKeyの役割説明
    const std::string dKeyAction="Dで削除";
    //WKeyの役割説明
    const std::string wKeyAction="方向変更";
    //AKeyの役割説明
    const std::string aKeyAction="Aと十字でカメラ操作";
    //SKeyの役割説明
    const std::string sKeyAction="Sと十字で出てくる時期を変更";
    //ESCKeyの役割説明
    const std::string escKeyAction="ESCでメニュー";
    //表示位置の高さ
    int screenHeight;
    //描画する文字のサイズ
    const int fontSize = 24;
    //文字列の距離Y
    const int strBetweenY = 50;
    //文字列の距離X
    const int strBetweenX = 50;

};

