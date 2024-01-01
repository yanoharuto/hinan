#pragma once
#include <memory>
class MouseInput;
//�ŒZ�^�C�����~�b�g
constexpr int MIN_TIME_LIMIT = 30;
constexpr int STAGE_WIDTH_VALUE = 6000;
/// <summary>
/// �������Ԃ̕ύX���s��
/// </summary>
class StageTimeLimitEditor
{
public:
    StageTimeLimitEditor() {};
    ~StageTimeLimitEditor() {};
    /// <summary>
    /// �������Ԃ̏�������
    /// </summary>
    void SaveLimitTime();
    /// <summary>
    /// �������Ԃ̕ύX
    /// </summary>
    void ChangeTimeLimit(std::weak_ptr<MouseInput> mouse);
    /// <summary>
    /// ���̃X�e�[�W�̃^�C�����~�b�g
    /// </summary>
    /// <returns></returns>
    int GetTimeLimit()const { return timeLimit; };
private:
    //�^�C�����~�b�g
    int timeLimit = MIN_TIME_LIMIT;
    //�ҏW�t�@�C���u����
    const std::string editFilePath = "data/Json/StageData/Stage4/editData";
    //�ҏW���e��ۑ�����t�@�C����
    const char editFIle[41] = "data/Json/StageData/Stage4/editData.json";
    //�X�R�A��ۑ�����t�@�C����
    const char scoreFile[42] = "data/Json/StageData/Stage4/scoreData.json";
};

