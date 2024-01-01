#pragma once
/// <summary>
/// 場面の切り替えをするよ
/// </summary>
class FadeInFadeOut
{
public:
    /// <summary>
    /// フェードインの更新
    /// </summary>
    static void FadeIn();
    /// <summary>
    /// フェードアウトの更新
    /// </summary>
    static void FadeOut();
private:
    /// <summary>
    /// アウト中なら白くなる　インなら周りのモデルとかが見える
    /// </summary>
    static void Fading();
    /// <summary>
    /// フェードインフェードアウトをする
    /// </summary>
    FadeInFadeOut() {};
    //高いほど白くなるよ
    static int fadeValue;
    //フェードアウトする速度
    static const int fadeSpeed;
    //後ろで描画する画像
    static int backScreen;
};

