#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "JsonFileLoader.h"
#include "StageSelect.h"
#include "StopTimer.h"
#include "ResultScore.h"
#include "ScoreRecordWriter.h"
//�X�e�[�W�̃t�@�C���̖��O
std::string StageDataManager::fileAddres = "-1";
//�e�X�e�[�W�̃f�[�^�̃X�L�[�}
const std::string StageDataManager::stageDataSchema = "stageDataSchema.json";
//�e�X�e�[�W�̃X�R�A�̃X�L�[�}
const std::string StageDataManager::scoreDataSchema = "scoreDataSchema.json";
//�z�u�ɕK�v�ȃX�L�[�}
const std::string StageDataManager::arrangeDataSchema = "arrangeDataSchema.json";
//�X�e�[�W�̃f�[�^
std::vector<std::string> StageDataManager::dataVector;
//�X�e�[�W�̉���
int StageDataManager::stageWidth;
//�X�e�[�W�̏c��
int StageDataManager::stageLength;

StageDataManager::StageDataManager()
{
}
/// <summary>
/// ��������X�e�[�W�̕ύX
/// </summary>
/// <param name="select">���I��ł���X�e�[�W�������Ă��炤</param>
void StageDataManager::ChangeStageData(StageSelect* const select)
{
    if (dataVector.empty())
    {
        LoadStageData();
    }
    //�I��ł���X�e�[�W�̃A�h���X��ۑ�
    fileAddres = dataVector[select->GetSelectStageNum()];

    stageWidth = STR_TO_I(GetSelectStageData(StageData::width));

    stageLength = STR_TO_I(GetSelectStageData(StageData::length));
}
/// <summary>
/// �X�e�[�W�̐�
/// </summary>
/// <returns></returns>
int StageDataManager::GetStageTotalNumber()
{
    return dataVector.size();
}

/// <summary>
/// �e�X�e�[�W�̃f�[�^������Ă���
/// </summary>
/// <param name="dataKind">�~�����X�e�[�W�̃f�[�^�̎��</param>
/// <returns>�X�e�[�W�̐������Ԃ�c�������A�����ʒu�̓������t�@�C���̃p�X�Ȃǂ��Ԃ��Ă���</returns>
std::string StageDataManager::GetSelectStageData(StageData dataKind)
{
    std::vector<std::string> setStageInitDataVec;
    if (IsExistJsonFile())
    {
        auto fileLoader = new JsonFileLoader(fileAddres, stageDataSchema);
        setStageInitDataVec.push_back(std::to_string(fileLoader->GetLoadInt("width")));
        setStageInitDataVec.push_back(std::to_string(fileLoader->GetLoadInt("length")));
        setStageInitDataVec.push_back(fileLoader->GetLoadString("editFilePath"));
        setStageInitDataVec.push_back(std::to_string(fileLoader->GetLoadInt("gameTime")));
        setStageInitDataVec.push_back(fileLoader->GetLoadString("stageScoreFilePath"));
    }
    else
    {
        //���I�𒆂̃X�e�[�W�̏�������
        auto fileLoader = new CSVFileLoader(fileAddres);
        setStageInitDataVec = fileLoader->GetStringData();
        SAFE_DELETE(fileLoader);
    }
    //�����̏���Ԃ�
    return setStageInitDataVec[CAST_I(dataKind)];
}
/// <summary>
/// �V�ԃX�e�[�W�̃X�R�A�̃{�[�_�[���C����Ԃ�
/// </summary>
/// <returns>���ݗV��ł���X�e�[�W�̃X�R�A�̐�������Z�߂�����</returns>
StageDataManager::ScoreBorder StageDataManager::GetScoreBorder()
{
    ScoreBorder scoreBorder = {};//�X�e�[�W�̃X�R�A�̐�����
    std::vector<std::string> scoreStrInfoVec;
    if (IsExistJsonFile())//json�œǂݍ���
    {
        auto fileLoader = new JsonFileLoader(GetSelectStageData(StageData::stageScoreFilePath), scoreDataSchema);
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(GOLDSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(SILVERSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(BROWNZESCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(HIGHSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(SECONDSCORE_MEMBER)));
        scoreStrInfoVec.push_back(std::to_string(fileLoader->GetLoadInt(THIRDSCORE_MEMBER)));
    }
    else//�������œǂݍ���
    {
        auto fileLoader = new CSVFileLoader(GetSelectStageData(StageData::stageScoreFilePath));
        //�X�e�[�W��񕶎���R���e�i
        scoreStrInfoVec = fileLoader->GetStringData();
        SAFE_DELETE(fileLoader);
    }
    //����
    scoreBorder.gold = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::goldScore)]);
    scoreBorder.silver = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::silverScore)]);
    scoreBorder.bronze = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::bronzeScore)]);
    scoreBorder.highScore = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::highScore)]);
    scoreBorder.second = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::secondScore)]);
    scoreBorder.third = STR_TO_I(scoreStrInfoVec[CAST_I(StageScore::thirdScore)]);
    return scoreBorder;
}
/// <summary>
/// �����ʒu�̕�������
/// </summary>
/// <returns>�����ʒu�̏����Ă���t�@�C���̃p�X</returns>
std::string StageDataManager::GetPlaceStrData()
{
    ///���I�����Ă���X�e�[�W�̏����ʒu�̓������t�@�C���̃p�X
    std::string selectStageFirstPlaceFilePath;
    //�e�I�u�W�F�N�g�̏����ʒu�̃t�@�C���܂ł̃p�X������
    selectStageFirstPlaceFilePath = GetSelectStageData(StageData::editFilePath);
    return selectStageFirstPlaceFilePath;
}
/// <summary>
/// �Q�[���̐������Ԃ̃^�C�}�[���쐬
/// </summary>
/// <returns>�Q�[���������ԃ^�C�}�[</returns>
std::shared_ptr<StopTimer> StageDataManager::CreateGameTimer()
{
    double gameLimitTime = STR_TO_F(GetSelectStageData(StageData::gameTime));
    return std::make_shared<StopTimer>(gameLimitTime);
}
/// <summary>
/// �X�R�A�̋L�^�X�V����n��
/// </summary>
/// <returns>�X�R�A�̋L�^�X�V��</returns>
ScoreRecordWriter* StageDataManager::GetScoreRecordWriter()
{
    return new ScoreRecordWriter(GetSelectStageData(StageData::stageScoreFilePath),GetScoreBorder());
}
/// <summary>
/// �S�X�e�[�W�ꗗ��ǂݎ��
/// </summary>
void StageDataManager::LoadStageData()
{
    dataVector = GetAssetList(AssetList::stageData);
    fileAddres = dataVector[0];//�Ƃ肠�����擪�̃X�e�[�W��n��
}
