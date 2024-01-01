#include "TitleObject.h"
#include "ActorControllerManager.h"
#include "TitleCarController.h"
#include "Timer.h"
#include "StageObjectController.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "TitleCamera.h"
#include "CollectController.h"
#include "ShadowMap.h"
#include "EnemyGenerator.h"
#include "EffekseerForDXLib.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
#include "CameraObserver.h"
#include "ObjectObserver.h"
/// <summary>
/// タイトル画面の裏で車を走らせる
/// </summary>
TitleObject::TitleObject()
{
    //初期化タイマー
    initTimer = std::make_shared<ReusableTimer>(initTime);
    //タイトルシーンの車
    titleCarController = std::make_shared <TitlteCarController>(demoCarFirstPos, demoCarFirstDir,initTimer);
    demoObserver = titleCarController->CreateCarObserver();
    //管理クラスに渡す
    manager = std::make_unique<ActorControllerManager>();
    
    shadowMap = std::make_unique<ShadowMap>(demoObserver);
    camera = std::make_shared<TitleCamera>(demoObserver);
    cameraObserever = std::make_shared<CameraObserver>(camera);
}
/// <summary>
/// 初期化周期タイマーや走っている車などの解放
/// </summary>
TitleObject::~TitleObject()
{
    initTimer.reset();
    camera.reset(); 
    cameraObserever.reset();
    SAFE_RESET(manager);
    SAFE_RESET(shadowMap);
}
/// <summary>
/// 車やステージ選択の更新
/// </summary>
void TitleObject::Update()
{
    manager->Update();
    shadowMap->SetShadowMapArea();
    camera->Update();
    //エフェクトの位置を現在のカメラに合わせる
    Effekseer_Sync3DSetting();
    UpdateEffekseer3D();
    UpdateEffekseer2D();
    //タイマーが切れたらデモを最初からにする
    if (initTimer->IsOverLimitTime())
    {
        if (isAValueIncrement)//フェードアウト
        {
            fadeValue += fadeSpeed;

            if (fadeValue > Utility::MAX_ONE_BYTE_RANGE)//限界まで来たら次は減らしていく
            {
                isAValueIncrement = false;
            }
        }
        else if (!isAValueIncrement)//フェードイン
        {
            fadeValue -= fadeSpeed;

            if (fadeValue < 0)
            {
                initTimer->Reuse();//タイマー再利用
                isAValueIncrement = true;
            }
        }
    }
}
/// <summary>
/// タイトル画面で走っている車と風景とエフェクトと影を描画
/// </summary>
void TitleObject::Draw() const
{
    //影とオブジェクトを描画
    shadowMap->SetUpDrawShadow();
    manager->Draw(cameraObserever);
    shadowMap->EndDrawShadow();
    manager->Draw(cameraObserever);
    shadowMap->Use();

    DrawEffekseer3D();
    DrawEffekseer2D();
    //一定時間かかるとフェードインフェードアウト
    if (initTimer->IsOverLimitTime())
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int> (fadeValue));//α値をいじる
        int colorValue = Utility::MAX_ONE_BYTE_RANGE;
        DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
    }
}
