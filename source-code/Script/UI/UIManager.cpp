#include "UIManager.h"
#include "CSVFileLoader.h"
#include "JsonFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
//�S�Ă�UI�̃p�X
std::vector<std::string> UIManager::uiPathVec;
//UI�ǂݎ��Ɏg���X�L�[�}
std::string UIManager::shemaPath = "uiDataSchema.json";
/// <summary>
/// �S�Ă�UI�摜�̃p�X��uiPathVec�ɓn��
/// </summary>
UIManager::UIManager()
{
    uiPathVec = GetAssetList(AssetList::ui);
}
/// <summary>
/// UI������
/// </summary>
/// <param name="uiKind">����������UI�̎��</param>
/// <returns>UI�̕`��ɕK�v�ȏ���Ԃ�</returns>
UIData UIManager::CreateUIData(UIInit::UIKind uiKind)
{
    return CreateUIData(CAST_I(uiKind));
}
/// <summary>
/// ������UI�̉摜���폜����
/// </summary>
/// <param name="ui">��������UI�摜</param>
void UIManager::DeleteUIGraph(UIData* ui)
{
    int size = ui->dataHandle.size();
    for (int i = 0; i < size; i++)
    {
        DeleteGraph(ui->dataHandle[i]);
    }
}
/// <summary>
/// UI������
/// </summary>
/// <param name="uiKind">����������UI</param>
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
        //�f�[�^�ǂݎ��
        CSVFileLoader* initDataFile = new CSVFileLoader(uiPathVec[kindNum]);
        dataVec = initDataFile->GetStringData();
        //�������f�[�^������
        SAFE_DELETE(initDataFile);
    }
    //�ʒu�Ƃ����Ƃ���������ǂݎ��
    data.x = STR_TO_I(dataVec[CAST_I(InitUIData::drawX)]);
    data.y = STR_TO_I(dataVec[CAST_I(InitUIData::drawY)]);
    //��������
    int divXNum = STR_TO_I(dataVec[CAST_I(InitUIData::xNum)]);
    //�c������
    int divYNum = STR_TO_I(dataVec[CAST_I(InitUIData::yNum)]);
    data.width = STR_TO_I(dataVec[CAST_I(InitUIData::width)]) / divXNum;
    data.height = STR_TO_I(dataVec[CAST_I(InitUIData::height)]) / divYNum;
    //�摜�𕪊��ǂݍ���
    int graphArray[1000];
    LoadDivGraph(dataVec[CAST_I(InitUIData::graphPath)].c_str(), divXNum * divYNum, divXNum, divYNum, data.width, data.height, graphArray);
    for (int i = 0; i < divXNum + divYNum - 1; i++)
    {
        data.dataHandle.push_back(graphArray[i]);
    }
    //�傫���ƃR�}���葬�x
    data.size = STR_TO_F(dataVec[CAST_I(InitUIData::size)]);
    data.frameSpeed = STR_TO_F(dataVec[CAST_I(InitUIData::frameSpeed)]);

    return data;
}