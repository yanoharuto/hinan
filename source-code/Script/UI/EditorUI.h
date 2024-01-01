#include <iostream>
#include <memory>
#include "UIManager.h"
#include "UIDrawer.h"
class NumUI;
class StageDataEditor;
/// <summary>
/// 編集時に出すUI
/// </summary>
class EditorUI
{
public:
    /// <summary>
    /// UIの所得
    /// </summary>
    EditorUI();
    /// <summary>
    /// UIの開放
    /// </summary>
    ~EditorUI();
    /// <summary>
    /// 編集時のUIの種類
    /// </summary>
    enum class EditUIKind
    {
        faseChange,
        time,
        stagePlay,
        free
    };
    /// <summary>
    /// 入力処理にマウスが今どのUIの上にいるか渡す
    /// </summary>
    /// <param name="mouseX">マウスの位置</param>
    /// <param name="mouseY">マウスの位置</param>
    /// <returns>当たってなかったらfree</returns>
    EditUIKind GetUIOnMouse(int mouseX,int mouseY) const;
    /// <summary>
    /// UI表示
    /// </summary>
    /// <param name="editor">収集アイテムの数やタイムリミットを所得</param>
    /// <param name="input">入力</param>
    void Draw(std::weak_ptr<StageDataEditor> const editor)const;
private:
    /// <summary>
    /// UIにマウスが当たってるか調べる
    /// </summary>
    /// <param name="data">調べるUI</param>
    /// <param name="mouseX">マウスの位置</param>
    /// <param name="mouseY">マウスの位置</param>
    /// <returns>当たってたらTrue</returns>
    bool IsUICollider(UIData data,int mouseX,int mouseY)const;

    //収集アイテムのフレームUI
    UIData collectFrameUIData;
    //編集したステージを遊ぶボタン
    UIData playEditStageUI;
    //編集中のフェーズの数字
    std::unique_ptr<NumUI> editFaseUI;
    //収集アイテムの数を描画するクラス
    std::unique_ptr<NumUI> totalCollectNumUI;
};