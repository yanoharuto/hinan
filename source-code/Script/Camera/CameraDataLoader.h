#pragma once
#include "AssetManager.h"

/// <summary>
/// カメラの初期化を行う
/// </summary>
class CameraDataLoader final: public AssetManager
{
public:
	struct  CameraParamater
	{
		float nearValue;//カメラの見れる開始位置
		float farValue;//カメラの見れる最終1
		float lookAngle;//カメラの画角
		float targetBetween;//ターゲットまでの距離
		float setYPos;//高さ
		float speed;//移動速度
	};
    /// <summary>
    /// カメラに必要なパラメータ
    /// </summary>
    enum class CameraParameter
    {
        //描画範囲の開始距離
        setNearValue = 0,
        //描画範囲の最終距離
        setFarValue = 1,
        //オブジェクトの見える範囲角
        setLookingAngle = 2,
        //描画対象との距離
        setTargetBetween = 3,
        //カメラのY距離
        setYPosition = 4,
        //カメラの移動速度
        setCameraSpeed = 5,
    };
    /// <summary>
    /// カメラが使われるシーンの種類
    /// </summary>
    enum class UseCameraSceneKind
    {
        //タイトルシーンのカメラ
        title = 0,
        //遊んでる時のカメラ
        game = 1,
        //リザルト画面でのカメラ
        editor = 2
    };
    /// <summary>
    /// 初期化情報所得
    /// </summary>
    /// <param name="type">シーンによってカメラの性能を変える</param>
	CameraParamater GetCameraParamator(UseCameraSceneKind type) const;
private:
    static std::string schemaPath;
};

