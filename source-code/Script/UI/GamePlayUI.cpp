#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "EndCountDown.h"
#include "CollectCompass.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
/// <summary>
/// �v���C���[�␧�����ԁA���W�A�C�e���̐��Ȃǂ�\���ł���悤�ɂ���
/// </summary>
/// <param name="player">�v���C���[�̈ʒu</param>
/// <param name="timer">��������</param>
/// <param name="collectItemObserver">���W�A�C�e�����</param>
GamePlayUI::GamePlayUI(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer, std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    //�c�莞��
    gameTimerUI = std::make_unique <TimerUI>(timer);
    //�~�j�}�b�v
    minimapUI = std::make_unique <MiniMap>(player);
    //�c��̎��W�A�C�e���̐�
    allCollectNum = collectItemObserver->GetTotalItemNum();
    firstCollectNumUI = std::make_unique<NumUI>(UIKind::allCollectItemNum);
    //���ݎ������
    getNumUI = std::make_unique<NumUI>(UIKind::getCollectItemNum);
    remainingNumUI = std::make_unique<NumUI>(UIKind::remainingCollectItemNum);
    //���W�A�C�e���Ɋւ���UI�̘g
    frameUIData = UIManager::CreateUIData(UIKind::collectItemFrameUI);
    //�c����W�A�C�e���ɂ��ẴR�����gUI
    remainingFrazeUIData = UIManager::CreateUIData(UIKind::remainingCollectItemPhrase);
    //�v���C���[�̃A�C�e���������������Ă��炤
    playerObserver = player;
    //���W�A�C�e���̕������o��
    collectCompass = std::make_unique <CollectCompass>(player, collectItemObserver);
    //�Q�[���I���J�E���g�_�E��
    countDown = std::make_unique <EndCountDown>(timer);
    //�c�莞��
    remainingNumDrawTimer = std::make_unique <ReusableTimer>(remainingNumDrawTime);
    //������@
    playManual = std::make_unique <PlayManual>();
}

/// <summary>
/// �eUI���J��
/// </summary>
GamePlayUI::~GamePlayUI()
{
    SAFE_RESET(gameTimerUI);
    SAFE_RESET(minimapUI);
    getNumUI.reset();
    firstCollectNumUI.reset();
    remainingNumUI.reset();
    SAFE_RESET(countDown);
    SAFE_RESET(collectCompass);
    SAFE_RESET(remainingNumDrawTimer);
    SAFE_RESET(playManual);
    playerObserver.reset();
    UIManager::DeleteUIGraph(&remainingFrazeUIData);
    UIManager::DeleteUIGraph(&frameUIData);
}
/// <summary>
/// �~�j�}�b�v�̍X�V����W�A�C�e���̖������X�V
/// </summary>
void GamePlayUI::Update()
{
    int tempNum = nowGetCollectNum;
    //���W�A�C�e���̐�
    nowGetCollectNum = playerObserver.lock()->GetCollectCount();
    //�Q�b�g�����A�C�e���̐�����������UI��\��
    if (nowGetCollectNum != tempNum)
    {
        isDrawGetNum = true;
        remainingNumDrawTimer->Reuse();
    }
    //�\������������false�ɂ���
    if (remainingNumDrawTimer->IsOverLimitTime())
    {
        isDrawGetNum = false;
    }
    //�Q�[���̎c�莞�Ԃ��Z���Ȃ����瓮��
    countDown->Update();
    //�~�j�}�b�v
    minimapUI->Update();
    //���W�A�C�e���̈ʒu�������Ă����
    collectCompass->Update();
    //������@�X�V
    playManual->Update();
}
/// <summary>
/// �`��
/// </summary>
void GamePlayUI::Draw()const
{
    if (isDrawGetNum)//���W�A�C�e��������Ă��΂炭�̊ԁA�c��̐����o��
    {
        int safeNum = 0;
        switch (allCollectNum - nowGetCollectNum)//�c��̃A�C�e���̐��ɉ����Ď�������̃��b�Z�[�W��ς���
        {
        case 0:
            break;
        case 1:
            safeNum = 1;
            //�c��̎��W�A�C�e���ɂ��Ẵ��b�Z�[�W
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            break;
        default:
            //�c��̎��W�A�C�e���ɂ��Ẵ��b�Z�[�W
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            remainingNumUI->Draw(allCollectNum - nowGetCollectNum);
            break;
        }
        
    }
    //���W�A�C�e���̐�����\��
    UIDrawer::DrawRotaUI(frameUIData);
    firstCollectNumUI->Draw(allCollectNum);
    getNumUI->Draw(nowGetCollectNum);
    //�c�莞��
    gameTimerUI->Draw();
    //�~�j�}�b�v
    minimapUI->Draw();
    //�c�莞�Ԃ킸���ɂȂ�Ɠ����J�E���g�_�E��
    countDown->DrawUI();
    //������@�`��
    playManual->Draw();
}