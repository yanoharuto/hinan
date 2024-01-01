#include <fstream>
#include <string>
#include "StageDataEditor.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "CameraObserver.h"
#include "Utility.h"
#include "StageDataManager.h"
#include "EditDataSaver.h"
#include "MouseInput.h"
#include "EditLog.h"
/// <summary>
///ステージに配置するオブジェクトの位置などを保存する
/// </summary>
StageDataEditor::StageDataEditor()
{
    //収集アイテムの数と出てくるタイミングの初期化
    collectNum = 0;
    appearFaseNum = 0;
    //もしすでにファイルがあるならデータを取ってくる
    editedPlacementDataVec = FirstPositionGetter::GetPlaceData(editFilePath);

    if (!editedPlacementDataVec.empty())
    {
        for (int i = 0; i < CONTAINER_GET_SIZE(editedPlacementDataVec); i++)
        {
            switch (editedPlacementDataVec[i].objKind)
            {
                //プレイヤーのデータがあるなら移す
            case PLAYER_NUMBER:
                playerData = editedPlacementDataVec[i];
                editedPlacementDataVec.erase(editedPlacementDataVec.begin() + i);
                break;
                //収集アイテムならカウント
            case COLLECT_NUMBER:
                collectNum++;
                break;
            default:
                break;
            }
        }
    }
    //記録係
    log = std::make_unique<EditLog>(editLogFilePath, CONTAINER_GET_SIZE(editedPlacementDataVec));
    //一つも収集アイテムがなかったら追加する
    if (collectNum == 0)
    {
        collectNum++;
        PlacementData placeData = playerData;
        placeData.objKind = COLLECT_NUMBER;
        editedPlacementDataVec.push_back(placeData);
    }
}
/// <summary>
/// 編集オブジェクトの履歴の開放とJsonファイルに書き写す
/// </summary>
StageDataEditor::~StageDataEditor()
{
    auto dataSaver = std::make_unique <EditDataSaver>();
    dataSaver->SaveEditData(editFilePath,GetAllEditEndPlacementData());//編集したすべてを書き込む
    SAFE_RESET(dataSaver);
    SAFE_RESET(log);
}
/// <summary>
/// 編集してほしいデータを渡す
/// </summary>
/// <returns>編集してほしいデータ</returns>
PlacementData StageDataEditor::GetEditData() const
{    
    if(isEditPlayer)
    {
        return playerData;
    }
    else if (isReEdit && CONTAINER_GET_SIZE(editedPlacementDataVec) != 0)
    {
        return editedPlacementDataVec[editNum];
    }
}
/// <summary>
/// 描画してほしいものを渡すを渡す
/// </summary>
/// <returns>今のフェーズの編集済みデータの纏めたもの</returns>
std::vector<PlacementData> StageDataEditor::GetNowFaseEditEndPlacementData() const
{
    std::vector<PlacementData> returnValue;

    for (int i = 0; i < CONTAINER_GET_SIZE(editedPlacementDataVec); i++)
    {
        //同じフェーズに出てくるか
        if (editedPlacementDataVec[i].collectNum == appearFaseNum)
        {
            returnValue.push_back(editedPlacementDataVec[i]);
        }
    }
    returnValue.push_back(playerData);
    return returnValue;
}
/// <summary>
/// 保存してほしい編集済みデータを纏めたものを渡す
/// </summary>
/// <returns>全ての編集済みデータの纏めたもの</returns>
std::vector<PlacementData> StageDataEditor::GetAllEditEndPlacementData() const
{
    std::vector<PlacementData> returnValue = editedPlacementDataVec;
    returnValue.push_back(playerData);
    return returnValue;
}
/// <summary>
/// 現在編集しているアイテムの出てくるタイミングを変更
/// </summary>
void StageDataEditor::ChangeAppearFase(std::weak_ptr<MouseInput> mouse)
{
    appearFaseNum += mouse.lock()->GetWheelIncreaseValue();
    //収集アイテムの数より多くならない
    if (appearFaseNum >= collectNum)
    {
        appearFaseNum = collectNum - 1;
    }
    //0より少なくならない
    if (appearFaseNum < 0)
    {
        appearFaseNum = 0;
    }
}

/// <summary>
/// 引数の場所に編集したものがあるかしらべる
/// </summary>
/// <param name="placeData">今編集している場所の情報</param>
void StageDataEditor::UpdateEditTarget(PlacementData placeData) 
{
    //初期化
    //近くのもの（再編集する物）がないときは新しく追加するためFalse
    isReEdit = false;
    isEditPlayer = false;
    editNum = CONTAINER_GET_SIZE(editedPlacementDataVec) - 1;//新規作成なら追加前の最大数と同じ
    //調べる位置
    const VECTOR checkPosition = VGet(placeData.posX, 0, placeData.posZ);
    //編集済みのオブジェクトの位置情報
    VECTOR editedPosition = VGet(playerData.posX, 0, playerData.posZ);
    //距離の最小値
    float minScale = nearDistanceReferenceValue;
    //距離の大きさ
    float betweenScale = VSize(VSub(editedPosition, checkPosition));
    
    //プレイヤーと近いものを調べる
    if(minScale > betweenScale)
    {
        isEditPlayer = true;
        minScale = betweenScale;
    }
    //プレイヤー以外のもので距離が近いものを調べる
    for (int i = 0; i < CONTAINER_GET_SIZE(editedPlacementDataVec); i++)
    {
        PlacementData data = editedPlacementDataVec[i];
        //編集中のフェーズに出てくるオブジェクトなら比較する
        if (data.collectNum == appearFaseNum)
        {
            editedPosition = VGet(data.posX, 0, data.posZ);
            betweenScale = VSize(VSub(editedPosition, checkPosition));
            //距離を比較
            if (minScale > betweenScale)
            {
                isReEdit = true;
                isEditPlayer = false;
                editNum = i;
            }
        }
    }
}
/// <summary>
/// 再編集している物は削除する
/// </summary>
void StageDataEditor::OnEraceEditData()
{
    if(!editedPlacementDataVec.empty())
    {
        //消したい場所に移動
        auto editData = editedPlacementDataVec.begin();
        editData += editNum;
        //収集アイテムなら数えている変数の値を減らす
        if ((*editData).objKind == COLLECT_NUMBER|| 1 > collectNum)
        {
            collectNum--;
            if (collectNum <= appearFaseNum)
            {
                appearFaseNum = collectNum - 1;
            }
        }
        //消したものをログに残す
        auto eraceData = *editData;
        editedPlacementDataVec.erase(editData);
        log->SaveEditDataLog(prevNum,CONTAINER_GET_SIZE(editedPlacementDataVec), editNum, eraceData);
        prevNum = 0;
    }
}
/// <summary>
/// 再編集中かどうか
/// </summary>
/// <returns>再編集中ならTrue</returns>
bool StageDataEditor::IsReEdit() const
{
    return isReEdit || isEditPlayer;
}
/// <summary>
/// ひとつ前の状態に戻す
/// </summary>
void StageDataEditor::OnBackStepPrevState()
{
    if (log->CanBackPrevState(prevNum))//編集履歴が残っているなら
    {
        //過去の配置情報を所得 ホイールが下なら前に戻る　上なら先に戻る
        auto placeData = log->GetPrevEditData(prevNum);
        //プレイヤーだったらプレイヤーの位置と回転を戻す
        if (placeData.data.objKind == PLAYER_NUMBER)
        {
            log->UpdateReEditData(prevNum, placeData, playerData);
            playerData = placeData.data;
        }
        else
        {
            //ログが指しているオブジェクト
            auto allocator = editedPlacementDataVec.begin();
            switch (placeData.editAction)
            {
            case EditLog::EditActionKind::reEdit://再編集なら元に戻す
                log->UpdateReEditData(prevNum, placeData, editedPlacementDataVec[placeData.editNum]);
                editedPlacementDataVec[placeData.editNum] = placeData.data;
                break;
            case EditLog::EditActionKind::deleteData://戻の場所に追加
                allocator += placeData.editNum;
                editedPlacementDataVec.insert(allocator, placeData.data);
                break;
            case EditLog::EditActionKind::addData://ひとつ前は新しいものがないので削除
                editedPlacementDataVec.erase(editedPlacementDataVec.end() - 1);
                break;
            };
        }
        //ひとつ前の状態に戻す
        prevNum++;
    }
}
/// <summary>
/// ひとつ前の状態から復元して一つ先にする
/// </summary>
void StageDataEditor::OnStepState()
{
    if (prevNum > 0)//ひとつ前に戻っているなら復元可能
    {
        //一つ先の状態に戻す
        prevNum--;
        //過去の配置情報を所得
        auto placeData = log->GetStepEditData(prevNum);
        //プレイヤーだったらプレイヤーの位置と回転を戻す
        if (placeData.data.objKind == PLAYER_NUMBER)
        {
            log->UpdateReEditData(prevNum, placeData, playerData);//元に戻す前の状態を記録
            playerData = placeData.data;
        }
        else
        {
            //ログが指しているオブジェクト
            auto allocator = editedPlacementDataVec.begin();
            switch (placeData.editAction)
            {
            case EditLog::EditActionKind::reEdit://再編集なら元に戻す
                log->UpdateReEditData(prevNum, placeData, editedPlacementDataVec[placeData.editNum]);
                editedPlacementDataVec[placeData.editNum] = placeData.data;
                break;
            case EditLog::EditActionKind::deleteData://編集箇所は削除されていた
                allocator += placeData.editNum;
                editedPlacementDataVec.erase(allocator);
                break;
            case EditLog::EditActionKind::addData://一つ先で追加されているのでpush_back
                editedPlacementDataVec.push_back(placeData.data);
                break;
            }
        }
    }
}
/// <summary>
/// 編集情報を登録
/// </summary>
void StageDataEditor::OnPut(PlacementData placeData)
{
    //再編集モードなら該当箇所のデータを差し替え
    if (isReEdit && placeData.objKind != PLAYER_NUMBER)
    {
        //収集アイテムを編集して別のものに変えたなら最大数を減らす
        if (editedPlacementDataVec[editNum].objKind == COLLECT_NUMBER &&
            placeData.objKind != COLLECT_NUMBER)
        {
            collectNum--;
            appearFaseNum = appearFaseNum < collectNum ? appearFaseNum : collectNum - 1;
        }
        if(placeData.objKind == COLLECT_NUMBER)//再編集したものが収集アイテムなら
        {
            placeData.collectNum = collectNum;
            appearFaseNum = collectNum;
            collectNum++;
        }
        //再編集後と前を入れ替え
        std::swap(editedPlacementDataVec[editNum], placeData);
    }
    else//新規登録か
    {
        switch (placeData.objKind)
        {
        case COLLECT_NUMBER://収集アイテムの数が増えたら
            placeData.collectNum = collectNum;
            appearFaseNum = collectNum;
            collectNum++;
            //新しい編集オブジェクトをコンテナに納品
            editedPlacementDataVec.push_back(placeData);
            break;
            //プレイヤーは一つだけでいいので変数に収納
        case PLAYER_NUMBER:
            playerData = placeData;
            break;
        default:
            //何個目のアイテムを回収したかで出てくるか設定する
            placeData.collectNum = appearFaseNum;
            //新しい編集オブジェクトをコンテナに納品
            editedPlacementDataVec.push_back(placeData);
            break;
        }
    }
    //配置したらログに残す
    log->SaveEditDataLog(prevNum,CONTAINER_GET_SIZE(editedPlacementDataVec),editNum,placeData);
    //ひとつ前の状態に戻すをリセット
    prevNum = 0;
}