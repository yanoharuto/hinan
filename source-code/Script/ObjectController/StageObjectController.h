#pragma once
#include <string>
#include <vector>
#include "ActorController.h"
class StageWall;
class Rock;
class FirstPositionGetter;
/// <summary>
/// 走る場所
/// </summary>
class StageObjectController final : public ActorController
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    StageObjectController();
    /// <summary>
    /// ステージを囲むオブジェクトの解放
    /// </summary>
    ~StageObjectController() override;
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw(std::weak_ptr<CameraObserver>& cameraObserever)const override;
private:
    //地面
    int floorModelHandle;
    //空
    int skyDomeModelHandle;
    //壁
    std::unique_ptr<StageWall> stageWall;
};