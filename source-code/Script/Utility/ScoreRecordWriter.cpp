#include "ScoreRecordWriter.h"
#include "ResultScore.h"
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include <writer.h>

/// <summary>
/// �X�R�A�̋L�^������
/// </summary>
/// <param name="filePath">�X�R�A�̃t�@�C���̃p�X</param>
/// <param name="scoreBorder">���̃X�e�[�W�̃X�R�A�̋L�^�̐�����</param>
ScoreRecordWriter::ScoreRecordWriter(std::string filePath, StageDataManager::ScoreBorder scoreBorder)
{
    //CSV�t�@�C���̋�؂蕶��
    std::string colon = ",";
    scoreRecordFilePath = filePath;
    border = scoreBorder;
    //�ύX���Ȃ��������̉ӏ�
    borderString = std::to_string(scoreBorder.gold) + colon + std::to_string(scoreBorder.silver) + colon + std::to_string(scoreBorder.bronze) + colon;
}
/// <summary>
/// �X�R�A�̋L�^�̍X�V
/// </summary>
/// <param name="score">���ݗV��ł���X�e�[�W�̋L�^�������Ă��炤</param>
void ScoreRecordWriter::UpdateScoreRecord(ResultScore* const resultScore)
{
    //�ō��X�R�A
    int highScore = resultScore->GetUpdateScore();
    //CSV�t�@�C���̋�؂蕶��
    std::string colon = ",";
    //�X�R�A�̃����L���O������
    std::string updateString;
    //�n�C�X�R�A�̕�����
    std::string highScoreStr = std::to_string(highScore);
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    jsonDoc.AddMember(GOLDSCORE_MEMBER, border.gold, allocator);
    jsonDoc.AddMember(SILVERSCORE_MEMBER, border.silver, allocator); 
    jsonDoc.AddMember(BROWNZESCORE_MEMBER, border.bronze, allocator);
    //�n�C�X�R�A�����L���O1�ʂ̍X�V
    if (border.highScore < highScore)
    {
        updateString = highScoreStr + colon + std::to_string(border.highScore) + colon + std::to_string(border.second) + colon;
        jsonDoc.AddMember(HIGHSCORE_MEMBER, highScore, allocator);
        jsonDoc.AddMember(SECONDSCORE_MEMBER, border.second, allocator);
        jsonDoc.AddMember(THIRDSCORE_MEMBER, border.third, allocator);

    }
    //2�ʂ̍X�V
    else if (border.second < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + highScoreStr + colon + std::to_string(border.second) + colon;
        jsonDoc.AddMember(HIGHSCORE_MEMBER, border.highScore, allocator);
        jsonDoc.AddMember(SECONDSCORE_MEMBER, highScore, allocator);
        jsonDoc.AddMember(THIRDSCORE_MEMBER, border.third, allocator);
    }
    //3�ʂ̍X�V
    else if (border.third < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + std::to_string(border.second) + colon + highScoreStr + colon; 
        jsonDoc.AddMember(HIGHSCORE_MEMBER, border.highScore, allocator);
        jsonDoc.AddMember(SECONDSCORE_MEMBER, border.second, allocator);
        jsonDoc.AddMember(THIRDSCORE_MEMBER, highScore, allocator);
    }
    //�X�R�A�X�V�L��Ȃ珑������
    if (!updateString.empty())
    {
        // �t�@�C�����J����
        std::ofstream writing_file;
        writing_file.open(scoreRecordFilePath, std::ios::out);
        //�X�R�A�̍X�V
        writing_file << borderString + updateString << std::endl;
        //�������ݏI��
        writing_file.close();
        //�t�@�C���̒��g��S����������Ԃŏ�������
        std::ofstream ofs(scoreRecordFilePath,std::ios::out);
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        jsonDoc.Accept(writer);
    }
}