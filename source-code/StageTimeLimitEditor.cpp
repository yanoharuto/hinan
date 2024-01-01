#include <iostream>
#include <cassert>
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include <fstream>
#include "StageTimeLimitEditor.h"
#include "MouseInput.h"
#include "writer.h"
#include "Utility.h"

/// <summary>
/// �������Ԃ̕ύX
/// </summary>
void StageTimeLimitEditor::ChangeTimeLimit(std::weak_ptr<MouseInput> mouse)
{
    timeLimit += mouse.lock()->GetWheelIncreaseValue();//�z�C�[������ɉ񂵂���1�b������

    if (timeLimit < MIN_TIME_LIMIT)//�Œ�^�C�����~�b�g
    {
        timeLimit = MIN_TIME_LIMIT;
    }
}

/// <summary>
/// �������Ԃ�ۑ�����
/// </summary>
/// <param name="limitTime"></param>
void StageTimeLimitEditor::SaveLimitTime()
{
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
    jsonDoc.AddMember("width", STAGE_WIDTH_VALUE, allocator);
    jsonDoc.AddMember("length", STAGE_WIDTH_VALUE, allocator);
    jsonDoc.AddMember("editFilePath", editFIle, allocator);
    jsonDoc.AddMember("gameTime", timeLimit, allocator);
    jsonDoc.AddMember("stageScoreFilePath", scoreFile, allocator);
    //�t�@�C���̒��g��S����������Ԃŏ�������
    std::ofstream ofs(editFilePath + Utility::JSON_FILE);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    jsonDoc.Accept(writer);
}