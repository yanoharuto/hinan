#pragma once
/// <summary>
/// シーンの内訳
/// </summary>
enum class SceneType
{
    //再ロード
    reload,
    //タイトル
    title,
    //ゲームプレイ
    play,
    //編集
    editor,
    //ゲーム終了
    escape
};