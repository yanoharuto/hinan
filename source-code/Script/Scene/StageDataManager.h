#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "DxLib.h"
#include "Object.h"
#include "AssetManager.h"
//Json�Ŏg���X�R�A�̃p�����[�^�̃����o�̖��O
//�S�[���h�����N
constexpr char GOLDSCORE_MEMBER[] = "gold";
//�V���o�[�����N
constexpr char SILVERSCORE_MEMBER[] = "silver";
//�u�����Y�����N
constexpr char BROWNZESCORE_MEMBER[] = "bronze";
//�ō��L�^
constexpr char HIGHSCORE_MEMBER[] = "firstScore";
//��Ԗڂ̋L�^
constexpr char SECONDSCORE_MEMBER[] = "secondScore";
//�O�Ԗڂ̋L�^
constexpr char THIRDSCORE_MEMBER[] = "thirdScore";

class StageSelect;
class ResultScore;
class StopTimer;
class ScoreRecordWriter;
/// <summary>
/// �V�ԃX�e�[�W�̃f�[�^��n��
/// </summary>
class StageDataManager :public AssetManager
{
public:
    /// <summary>
    /// �X�e�[�W�̏��Ǘ���
    /// </summary>
    StageDataManager();
    struct ScoreBorder;
    /// <summary>
    /// ��������X�e�[�W�̕ύX
    /// </summary>
    /// <param name="select">���I��ł���X�e�[�W�������Ă��炤</param>
    static void ChangeStageData(StageSelect* const select);
    /// <summary>
    /// �X�e�[�W�̑���
    /// </summary>
    /// <returns>�X�e�[�W�̑������Ԃ��Ă���</returns>
    static int GetStageTotalNumber();
    /// <summary>
    /// �V�ԃX�e�[�W�̃X�R�A�̃{�[�_�[���C����Ԃ�
    /// </summary>
    /// <returns>���ݗV��ł���X�e�[�W�̃X�R�A�̐�������Z�߂�����</returns>
    static StageDataManager::ScoreBorder GetScoreBorder();
    /// <summary>
    /// �����ʒu�̏����ʒu�̏����Ă���t�@�C���̃p�X��������
    /// </summary>
    /// <returns>�����ʒu�̏����Ă���t�@�C���̃p�X</returns>
    static std::string GetPlaceStrData();
    /// <summary>
    /// �Q�[���̐������Ԃ̃^�C�}�[���쐬
    /// </summary>
    /// <returns>�Q�[���������ԃ^�C�}�[</returns>
    static std::shared_ptr<StopTimer> CreateGameTimer();
    /// <summary>
    /// �X�R�A�̋L�^�X�V����n��
    /// </summary>
    /// <returns>�X�R�A�̋L�^�X�V��</returns>
    static ScoreRecordWriter* GetScoreRecordWriter();
    /// <summary>
   /// �X�e�[�W���Ƃɐݒ肵�Ă���f�[�^
   /// </summary>
    enum class StageData
    {
        //����
        width,
        //�c��
        length,
        //��Q���̈ʒu�̃t�@�C���p�X
        editFilePath,
        //��������
        gameTime,
        //�X�e�[�W�̃X�R�A
        stageScoreFilePath
    };
    /// <summary>
    /// �X�R�A�̐�����
    /// </summary>
    enum class StageScore
    {
        //��Ԗڂɂ����X�R�A
        goldScore,
        //��Ԗڂɂ����X�R�A
        silverScore,
        //�O�Ԗڂɂ����X�R�A
        bronzeScore,
        //�V�񂾒��ōō��X�R�A
        highScore,
        //��Ԗڂɂ����X�R�A
        secondScore,
        //3�Ԗڂɂ����X�R�A
        thirdScore
    };
    /// <summary>
    /// �X�R�A�̊K��
    /// </summary>
    struct  ScoreBorder
    {
        //��Ԗڂɂ����X�R�A
        int gold;
        //��Ԗڂɂ����X�R�A
        int silver;
        //�O�Ԗڂɂ����X�R�A
        int bronze;
        //�V�񂾒��ōō��X�R�A
        int highScore;
        //��Ԗڂɂ����X�R�A
        int second;
        //3�Ԗڂɂ����X�R�A
        int third;
    };
private:

    /// <summary>
    /// �e�X�e�[�W�̃f�[�^������Ă���
    /// </summary>
    /// <param name="dataKind">�~�����X�e�[�W�̃f�[�^�̎��</param>
    /// <returns>�X�e�[�W�̐������Ԃ�c�������A�����ʒu�̓������t�@�C���̃p�X�Ȃǂ��Ԃ��Ă���</returns>
    static std::string GetSelectStageData(StageData dataKind);
    /// <summary>
    /// �S�X�e�[�W�ꗗ��ǂݎ��
    /// </summary>
    static void LoadStageData();
    //�X�e�[�W�̃f�[�^
    static std::vector<std::string> dataVector;
    //�e�X�e�[�W�̃f�[�^�̃p�X
    static std::string fileAddres;
    //��
    static int stageWidth;
    //����
    static int stageLength;
    //�e�X�e�[�W�̃f�[�^�̃X�L�[�}
    const static std::string stageDataSchema;
    //�e�X�e�[�W�̃X�R�A�̃X�L�[�}
    const static std::string scoreDataSchema;
    //�z�u���̃X�L�[�}
    const static std::string arrangeDataSchema;
};