#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
#include "Timer.h"
#include "UIManager.h"
#include "NumUI.h"

/// <summary>
/// �c�莞�Ԃ̃Z�b�g�Ɛ����摜�̓ǂݍ���
/// </summary>
/// <param name="setTimer">�c�莞�ԃ^�C�}�[</param>
TimerUI::TimerUI(std::weak_ptr<Timer> setTimer)
{
    timer = setTimer;
    frameUIData = UIManager::CreateUIData(UIKind:: timerFrame);
    pointUIData = UIManager::CreateUIData(UIKind::point);
    numUI = std::make_unique<NumUI>(UIKind::timeNum);
    //�^�C�}�[�̘g�̉��ʒu
    frameX = frameUIData.x + numUI->GetNumWidthSize() * 2;
}
/// <summary>
/// �^�C�}�[�̃��b�N�����@UI�폜
/// </summary>
TimerUI::~TimerUI()
{
    timer.reset();
    UIManager::DeleteUIGraph(&frameUIData);
    UIManager::DeleteUIGraph(&pointUIData);
}
/// <summary>
/// �^�C�}�[�̎c�莞�Ԃ�`��
/// </summary>
void TimerUI::Draw()
{
    //�^�C�}�[�̘g��`��@�����ɂ��邽�߂�
    DrawRotaGraph(frameX , frameUIData.y, frameUIData.size, 0, frameUIData.dataHandle[0], true);
    //�c�莞�Ԃ̕`��
    float limit = static_cast<float>(timer.lock()->GetRemainingTime());
    numUI->Draw(limit);
}