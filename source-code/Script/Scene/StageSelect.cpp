#include "StageSelect.h"
#include "UserInput.h"
#include "UIDrawer.h"
#include "Utility.h"
#include "StageDataManager.h"
/// <summary>
/// ステージ選択UIの読み込み
/// 一番最初のステージに変更
/// </summary>
StageSelect::StageSelect()
{
    selectStageNum = 0;
    StageDataManager::ChangeStageData(this);
    stageNameUIData = UIManager::CreateUIData(UIKind::stageName);
    selectButtonUIData = UIManager::CreateUIData(UIKind::stageSelectButton);
}
/// <summary>
/// UIの削除
/// </summary>
StageSelect::~StageSelect()
{
    UIManager::DeleteUIGraph(&selectButtonUIData);
    UIManager::DeleteUIGraph(&stageNameUIData);
}
/// <summary>
/// 十字キーで遊ぶステージ変更
/// </summary>
void StageSelect::Update()
{
    int totalStageNum = StageDataManager::GetStageTotalNumber();
    //上下に押したら変更
    if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Push)
    {
        selectStageNum++;
        //ステージ数の限界に来たら0に
        if (selectStageNum >= totalStageNum)
        {
            selectStageNum = totalStageNum - 1;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Push)
    {
        selectStageNum--;
        //ステージ数の最低に来たら最大値に
        if (selectStageNum < 0)
        {
            selectStageNum = 0;
        }
    }
    isEditStage = selectStageNum == totalStageNum - 1;
    //変更したことを伝える
    StageDataManager::ChangeStageData(this);
}
/// <summary>
/// ステージ一覧を表示
/// </summary>
void StageSelect::Draw() const
{
    //stageNameUIのCopy
    UIData stageNameUI = stageNameUIData;
    for (int i = 0; i < CONTAINER_GET_SIZE(stageNameUIData.dataHandle); i++)
    {
        if (i == selectStageNum)//現在選んでいるステージは大きくちょっとずらして表示
        {
            stageNameUI.x -= stageNameUIData.width / 2;
            stageNameUI.size *= selectSizeCoefficient;
        }
        else
        {
            stageNameUI.x = stageNameUIData.x;
            stageNameUI.size = stageNameUIData.size;
        }
        //各ステージの選択UIを描画
        UIDrawer::DrawRotaUI(stageNameUI, i);
        stageNameUI.y += stageNameUIData.height;
    }
    //選択するときのボタンを表示
    UIDrawer::DrawRotaUI(selectButtonUIData);
}
/// <summary>
/// ステージの番号所得
/// </summary>
/// <returns>今選択しているステージの番号</returns>
int StageSelect::GetSelectStageNum()const
{
    return selectStageNum;
}