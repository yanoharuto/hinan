#pragma once
#include <iostream>
#include <memory>
#include "Object.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class CameraObserver;
class MouseInput;
constexpr int EDIT_OBJECT_KIND = 7;
/// <summary>
/// エディタ上で表示するオブジェクト
/// </summary>
class EditorObject : public Object
{
public:
    /// <summary>
    /// 編集したいものを引数に下さい
    /// </summary>
    EditorObject();
    /// <summary>
    /// 編集オブジェクトの種類を変更
    /// </summary>
    void UpdateKind(std::weak_ptr<MouseInput> input);
    /// <summary>
    /// マウスの位置になるべく移動
    /// </summary>
    /// <param name="cameraObserever">カメラの伝達役</param>
    /// <param name="input">マウス入力</param>
    void Move(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input);
    /// <summary>
    /// マウスに沿って回転
    /// </summary>
    /// <param name="cameraObserever">カメラの伝達役</param>
    /// <param name="input">マウス入力</param>
    void Rotate(std::weak_ptr<CameraObserver> cameraObserever, std::weak_ptr<MouseInput> input);
    /// <summary>
    /// 描画に必要な構造体を渡す
    /// </summary>
    /// <returns>位置と向きと描画したいオブジェクトの種類</returns>
    PlacementData GetPlacementData()const;
    /// <summary>
    /// 引数の配置を引き継ぎ位置を変える
    /// </summary>
    /// <param name="setData">配置</param>
    void SetArrangementData(PlacementData setData);
protected:
    //回転速度
    static const float rotaSpeed;
    //移動速度
    static const float moveSpeed;
    //マウスの位置保存用
    int mouseX;
    //マウスの位置保存用
    int mouseY;
    //マウスの端判定で使う
    static const int mouseEdge;
    //編集中のオブジェクトの種類番号
    int kind;
    //kindsの添え字として使う
    int changeKindCount = 0;
    //編集中のオブジェクトの種類番号の参照先
    ObjectInit::InitObjKind kinds[EDIT_OBJECT_KIND] = 
    {
        ObjectInit::InitObjKind::saw,
        ObjectInit::InitObjKind::moveSaw,
        ObjectInit::InitObjKind::bomberShip,
        ObjectInit::InitObjKind::circleLaserShip,
        ObjectInit::InitObjKind::upDownLaserShip,
        ObjectInit::InitObjKind::collect,
        ObjectInit::InitObjKind::player
    };
};