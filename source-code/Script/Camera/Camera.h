#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "Camera.h"
#include "CameraDataLoader.h"
class ObjectObserver;
class Actor;

/// <summary>
/// カメラ
/// </summary>
class Camera abstract
{
public:
    /// <summary>
    /// カメラの速度や高さの初期化
    /// </summary>
    /// <param name="type">どのタイミングで使うか教えて</param>
    Camera(CameraDataLoader::UseCameraSceneKind type);
    /// <summary>
    /// 監視対象の解放
    /// </summary>
    virtual ~Camera();
    /// <summary>
    /// カメラの向きを所得
    /// </summary>
    /// <returns>カメラの向きベクトル</returns>
    VECTOR GetNormDirection()const;
    /// <summary>
    /// カメラのターゲットの位置を渡す
    /// </summary>
    /// <returns>ターゲットの位置</returns>
    VECTOR GetTargetPosition()const;
    /// <summary>
    /// カメラの位置を所得
    /// </summary>
    /// <returns>カメラの座標</returns>
    VECTOR GetPosition()const;
    /// <summary>
    /// 見える角度を所得
    /// </summary>
    /// <returns></returns>
    float GetLookingAngle()const;
    /// <summary>
    /// カメラとターゲットとの距離
    /// </summary>
    /// <returns></returns>
    float GetTargetBetweenSize() const { return targetBetweenSize; }
protected:
    /// <summary>
    /// カメラのパラメータ等を読み取る
    /// </summary>
    /// <param name="type">シーンによってカメラの性能を変える</param>
    void LoadData(CameraDataLoader::UseCameraSceneKind type);
    //見たいものの位置等を教えてくれるやつ
    std::shared_ptr<ObjectObserver> targetObserver;
    //カメラの位置
    VECTOR position;
    //カメラの方向
    VECTOR direction;
    //狙うべき場所
    VECTOR targetPos = { 0,0,0 };
    //描画しようとする範囲
    float nearValue;
    //描画しようとする範囲
    float farValue;
    //ターゲットとの距離
    float targetBetweenSize;
    //高さ
    float posY;
    //カメラの追いつく速度
    float cameraSpeed;
    //カメラの見える範囲角
    static float lookingAngle;
};