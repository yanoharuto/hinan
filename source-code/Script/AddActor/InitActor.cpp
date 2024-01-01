#include <iostream>
#include <fstream>
#include <sstream>
#include <document.h>
#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "DrawModelManager.h"
#include "JsonFileLoader.h"
//initActorFileNameの先のファイルから所得したデータをまとめたVector
std::vector<std::string> InitActor::objectInitDataPathVec;
//初期化要素のJsonSchemaのパス
std::string InitActor::initObjParamatorSchemaPath = "InitObjParamatorSchema.json";
//描画モデルの管理担当
std::unique_ptr<DrawModelManager> InitActor::drawModelManager;
/// <summary>
/// 全てのactorの初期化をするためのパスが入ったファイルを読み込む
/// </summary>
InitActor::InitActor()
{
    auto initDataLoader = std::make_unique<CSVFileLoader>(GetInitCsvFilePath(AssetList::object));
    if (initDataLoader->IsOpenFile())//ファイルが見つかったかどうか
    {
        objectInitDataPathVec = initDataLoader->GetStringData();
    }
    else//Jsonで読み込む
    {
        objectInitDataPathVec = GetAssetList(AssetList::object);
    }
    SAFE_RESET(initDataLoader);
    drawModelManager = std::make_unique<DrawModelManager>();
}
/// <summary>
/// 描画モデル管理担当の解放
/// </summary>
InitActor::~InitActor()
{
    SAFE_RESET(drawModelManager);
}
/// <summary>
/// 初期化に必要な情報を所得
/// </summary>
/// <param name="obj">初期化したいオブジェクト</param>
/// <returns>初期化に必要な情報</returns>
ActorParameter InitActor::GetActorParamator(InitObjKind kind)
{
    //初期化情報文字列ベクター
    auto initData = GetActorParametorStrVec(kind);
    ActorParameter initParam = {};
    char* end;

    //各情報をString型からfloat型に置き換え
    initParam.firstPosY = strtof(initData[CAST_I(InitObjParamator::firstPosY)].c_str(), &end);
    initParam.setBouncePow = strtof(initData[CAST_I(InitObjParamator::bouncePower)].c_str(), &end);
    initParam.setRadius = strtof(initData[CAST_I(InitObjParamator::collRadius)].c_str(), &end);
    return initParam;
}
/// <summary>
/// 引数の種類の描画モデルハンドルを渡す
/// </summary>
/// <param name="kind">取り出したい描画モデル</param>
/// <returns>描画モデルハンドル</returns>
int InitActor::GetModelHandle(InitObjKind kind)
{
    auto initData = GetActorParametorStrVec(kind);
    //描画モデル
    int modelHandle = drawModelManager->Get3DModelAssetHandle(initData[CAST_I(InitObjParamator::assetPath)]);
    char* end;
    //modelの大きさを変更
    float modelScale = strtof(GetActorParametorStrVec(kind)[CAST_I(InitObjParamator::modelSize)].c_str(), &end);
    MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));
    return modelHandle;
}

/// <summary>
/// 初期化したいパラメータを文字列で所得
/// </summary>
/// <param name="obj">初期化したいオブジェクト</param>
/// <returns>初期化したいパラメータの文字列</returns>
std::vector<std::string> InitActor::GetActorParametorStrVec(InitObjKind objKind)
{
    std::vector<std::string> initData;
    //初期化したいオブジェクトの種類をint型にする
    int num = CAST_I(objKind);
    //データ読み取り
    auto initDataLoader = std::make_unique<CSVFileLoader>(objectInitDataPathVec[num]);
    initData = initDataLoader->GetStringData();
    SAFE_RESET(initDataLoader);
    return initData;
}