#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"

//プレイヤーの識別番号
constexpr int PLAYER_NUMBER = static_cast<int>(ObjectInit::InitObjKind::player);
//プレイヤーの識別番号
constexpr int COLLECT_NUMBER = static_cast<int>(ObjectInit::InitObjKind::collect);

class EditorDrawModel;
class CameraObserver;
class MouseInput;
class EditLog;
using namespace ObjectInit;
/// <summary>
/// ステージに配置するオブジェクトの位置などを保存する
/// </summary>
class StageDataEditor
{
public: 
    /// <summary>
    ///ステージに配置するオブジェクトの位置などを保存する
    /// </summary>
    StageDataEditor();
    /// <summary>
    /// 編集オブジェクトの履歴の開放とJsonファイルに書き写す
    /// </summary>
    virtual ~StageDataEditor();
    /// <summary>
    /// 編集操作
    /// </summary>
    void OnPut(PlacementData placeData);
    /// <summary>
    /// 編集してほしいデータを渡す
    /// </summary>
    /// <returns>編集してほしいデータ</returns>
    PlacementData GetEditData() const;
    /// <summary>
    /// 描画してほしいものを渡すを渡す
    /// </summary>
    /// <returns>今のフェーズの編集済みデータの纏めたもの</returns>
    std::vector<PlacementData> GetNowFaseEditEndPlacementData()const;
    /// <summary>
    /// 保存してほしい編集済みデータを纏めたものを渡す
    /// </summary>
    /// <returns>全ての編集済みデータの纏めたもの</returns>
    std::vector<PlacementData> GetAllEditEndPlacementData()const;
    /// <summary>
    /// 現在編集しているアイテムの出てくるタイミングを変更
    /// </summary>
    void ChangeAppearFase(std::weak_ptr<MouseInput> mouse);
    /// <summary>
    /// 引数の場所に編集したものがあるかしらべる
    /// </summary>
    /// <param name="placeData">今編集している場所の情報</param>
    void UpdateEditTarget(PlacementData placeData);
    /// <summary>
    /// 再編集している物は削除する
    /// </summary>
    void OnEraceEditData();
    /// <summary>
    /// ひとつ前の状態に戻す
    /// </summary>
    void OnBackStepPrevState();
    /// <summary>
    /// ひとつ前の状態から復元して一つ先にする
    /// </summary>
    void OnStepState();
    /// <summary>
    /// 再編集中かどうか
    /// </summary>
    /// <returns>再編集中ならTrue</returns>
    bool IsReEdit()const;
    /// <summary>
    /// 収集アイテムの数
    /// </summary>
    /// <returns></returns>
    int GetCollectNum()const { return collectNum; };
    /// <summary>
    /// 今編集しているFase番号
    /// </summary>
    /// <returns></returns>
    int GetApperFaseNum()const { return appearFaseNum; };
protected:

    /// 収集アイテムの数
    int collectNum;  
    /// 収集アイテムを取ったどのタイミングで出てくるか
    int appearFaseNum;
    //現在編集している番号
    int editNum = 0;
    //再編集中かどうかのフラグ
    bool isReEdit = false;
    //プレイヤー編集中かどうかのフラグ
    bool isEditPlayer = false;
    //編集済みデータ
    std::vector<PlacementData> editedPlacementDataVec;
    //編集ファイル置き場
    const std::string editFilePath = "data/Json/StageData/Stage4/editData";
    //ひとつ前の状態に戻すための外部ファイル
    const std::string editLogFilePath = "data/Json/StageData/Stage4/editLogData";
    //マウスでクリックした場所から300より近かったら再編集
    const float nearDistanceReferenceValue = 30.0f;
    //プレイヤー番号
    PlacementData playerData = { PLAYER_NUMBER,0,0,0,1,0 };
    //どのくらい前の状態に戻すか 0なら一番最新の状態
    int prevNum = 0;
    //過去の編集データ
    std::unique_ptr<EditLog> log;
};