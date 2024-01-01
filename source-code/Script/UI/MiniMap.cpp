#include "MiniMap.h"
#include "UIManager.h"
#include "OriginalMath.h"
#include "Object.h"
#include "Utility.h"
#include "UIDrawer.h"
#include "StageWall.h"
//自機のIconの大きさ
const int MiniMap::iconSize;
//ミニマップに表示する点
std::list<std::unique_ptr<ObjectObserver>> MiniMap::markerObserverList;
//ミニマップのデータ
UIData MiniMap::miniMapUIData;
/// <summary>
/// 収集アイテムとかを描画するための奴
/// </summary>
MiniMap::MiniMap(std::weak_ptr<ObjectObserver> player)
{
    //UI読み込み
    miniMapUIData = UIManager::CreateUIData(UIInit::UIKind::radar);
    //ミニマップの縦幅
    int mapGraphLength;
    GetGraphSize(miniMapUIData.dataHandle[0], &mapGraphWidth, &mapGraphLength);
    
    playerObserver = player;
    betweenSize = mapGraphWidth / 6000 * betweenSize;
}
/// <summary>
/// 描画するマーカーを消去
/// </summary>
MiniMap::~MiniMap()
{
    //描画するリストを全消し
    for (auto itr = markerObserverList.begin(); itr != markerObserverList.end(); itr++)
    {
        (*itr).reset();
    }
    markerObserverList.clear();
    UIManager::DeleteUIGraph(&miniMapUIData);
}
/// <summary>
/// 収集アイテムの位置を更新
/// </summary>
/// <param name="objInfo"></param>
void MiniMap::Update()
{
    //一度全消し
    drawPosList.clear();
    //これからUpdateDrawPosListで追加されたものだけmapに反映する
    for (auto ite = markerObserverList.begin(); ite != markerObserverList.end(); ite++)
    {
        //アクティブなオブジェクトなら
        if ((*ite)->GetSubjectState() == Object::ObjectState::active)
        {
            VECTOR itePos = (*ite)->GetSubjectPos();
            //DrawPosListにオブジェクトの位置を追加していく
            UpdateDrawPosList(itePos);
        }
    }
    //北の位置をmapに反映
    northPos = VGet(mapGraphWidth / 2 * miniMapUIData.size / betweenSize, 0, 0);
    northPos = ConvertPosition(northPos);
}
/// <summary>
/// マップに表示する点とレーダーの枠
/// </summary>
void MiniMap::Draw()const
{
    //枠描画
    UIDrawer::DrawRotaUI(miniMapUIData);
    //プレイヤーアイコンの描画
    DrawCircle(miniMapUIData.x, miniMapUIData.y, iconSize, playerColor, 1, 1);
    //収集アイテムの描画
    for (auto ite = drawPosList.begin(); ite != drawPosList.end(); ite++)
    {
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize, coinColor, 1, 1);
    }
    //北の位置をmapに反映
    DrawCircle(static_cast<int>(northPos.x), static_cast<int>(northPos.y), iconSize, northColor, 1, 1);
}
/// <summary>
/// マップに反映させたいアイテムの追加
/// </summary>
/// <param name="obserber"></param>
void MiniMap::AddMarker(std::unique_ptr<ObjectObserver> obserber)
{
    markerObserverList.push_back(std::move(obserber));
}
/// <summary>
/// ミニマップの大きさに変換する
/// </summary>
/// <param name="between">中央のアイテムからの距離</param>
/// <returns></returns>
VECTOR MiniMap::ConvertPosition(VECTOR between)
{
    VECTOR playerDir = playerObserver.lock()->GetSubjectDir();
    //マップの中央物の向きとマーカーの位置の角度差
    float rotate = OriginalMath::GetDegreeMisalignment(between, playerDir);
    //右側か左側か
    rotate = VCross(between, playerDir).y < 0 ? -rotate : rotate ;
    //角度分曲がっている行列で距離を曲げる
    MATRIX pM = MGetRotY(-rotate * RAGE);
    between = VTransform(VGet(0, 0, -VSize(between)), pM);
    //ミニマップの大きさに変換
    VECTOR convertPos;
    convertPos.x = -between.x * betweenSize + miniMapUIData.x;
    convertPos.y = between.z * betweenSize + miniMapUIData.y;
    return convertPos;
}
/// <summary>
/// 描画するマーカーのポジション
/// </summary>
/// <param name="subjectPos">書きたいマーカーのオブジェクトのポジション</param>
void MiniMap::UpdateDrawPosList(VECTOR subjectPos)
{
    //プレイヤーがマップの中心になるようにする
    VECTOR playerPos = playerObserver.lock()->GetSubjectPos();
    playerPos.y = 0;
    //引数までのプレイヤーの距離ベクトル
    VECTOR distance = VSub(subjectPos, playerPos);
    distance.y = 0;
    //距離がマップに反映可能な大きさなら
    if (VSize(distance) * betweenSize < mapGraphWidth / 2)
    {
        distance = ConvertPosition(distance);

        drawPosList.push_back(distance);
    }
}