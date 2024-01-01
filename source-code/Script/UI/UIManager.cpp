#include "UIManager.h"
#include "CSVFileLoader.h"
#include "JsonFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
//全てのUIのパス
std::vector<std::string> UIManager::uiPathVec;
//UI読み取りに使うスキーマ
std::string UIManager::shemaPath = "uiDataSchema.json";
/// <summary>
/// 全てのUI画像のパスをuiPathVecに渡す
/// </summary>
UIManager::UIManager()
{
    uiPathVec = GetAssetList(AssetList::ui);
}
/// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUIの種類</param>
/// <returns>UIの描画に必要な情報を返す</returns>
UIData UIManager::CreateUIData(UIInit::UIKind uiKind)
{
    return CreateUIData(CAST_I(uiKind));
}
/// <summary>
/// 引数のUIの画像を削除する
/// </summary>
/// <param name="ui">消したいUI画像</param>
void UIManager::DeleteUIGraph(UIData* ui)
{
    int size = ui->dataHandle.size();
    for (int i = 0; i < size; i++)
    {
        DeleteGraph(ui->dataHandle[i]);
    }
}
/// <summary>
/// UIを所得
/// </summary>
/// <param name="uiKind">所得したいUI</param>
/// <returns></returns>
UIData UIManager::CreateUIData(int kindNum)
{
    UIData data;
    std::vector<std::string> dataVec;
    if (IsExistJsonFile())
    {
        JsonFileLoader* jsonFile = new JsonFileLoader(uiPathVec[kindNum], shemaPath);
        dataVec.push_back(std::to_string(jsonFile->GetLoadInt("x")));
        dataVec.push_back(std::to_string(jsonFile->GetLoadInt("y")));
        dataVec.push_back(std::to_string(jsonFile->GetLoadInt("width")));
        dataVec.push_back(std::to_string(jsonFile->GetLoadInt("height")));
        dataVec.push_back(std::to_string(jsonFile->GetLoadInt("xNum")));
        dataVec.push_back(std::to_string(jsonFile->GetLoadInt("yNum")));
        dataVec.push_back(jsonFile->GetLoadString("graphPass"));
        dataVec.push_back(std::to_string(jsonFile->GetLoadFloat("size")));
        dataVec.push_back(std::to_string(jsonFile->GetLoadFloat("frameSpeed")));
        
    }
    else
    {
        //データ読み取り
        CSVFileLoader* initDataFile = new CSVFileLoader(uiPathVec[kindNum]);
        dataVec = initDataFile->GetStringData();
        //初期化データを消す
        SAFE_DELETE(initDataFile);
    }
    //位置とか幅とか分割数を読み取る
    data.x = STR_TO_I(dataVec[CAST_I(InitUIData::drawX)]);
    data.y = STR_TO_I(dataVec[CAST_I(InitUIData::drawY)]);
    //横分割数
    int divXNum = STR_TO_I(dataVec[CAST_I(InitUIData::xNum)]);
    //縦分割数
    int divYNum = STR_TO_I(dataVec[CAST_I(InitUIData::yNum)]);
    data.width = STR_TO_I(dataVec[CAST_I(InitUIData::width)]) / divXNum;
    data.height = STR_TO_I(dataVec[CAST_I(InitUIData::height)]) / divYNum;
    //画像を分割読み込み
    int graphArray[1000];
    LoadDivGraph(dataVec[CAST_I(InitUIData::graphPath)].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
    for (int i = 0; i < divXNum + divYNum - 1; i++)
    {
        data.dataHandle.push_back(graphArray[i]);
    }
    //大きさとコマ送り速度
    data.size = STR_TO_F(dataVec[CAST_I(InitUIData::size)]);
    data.frameSpeed = STR_TO_F(dataVec[CAST_I(InitUIData::frameSpeed)]);

    return data;
}