#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "AssetManager.h"
namespace UIInit
{
    /// <summary>
    /// UI�̎��
    /// </summary>
    enum class UIKind
    {
        //�Q�[���̖ڕW
        gamePurose,
        //�J�E���g�_�E��
        countDownUI,
        //�R���N�g�A�C�e���̎c�萔�Ȃǂ�UI
        collectItemFrameUI,
        //���W���̃X�R�A�̕���
        collectScore,
        //���W���̃X�R�A
        collectScoreIcon,
        //�_���[�W���󂯂�ƌ�������X�R�A�̕���
        damageScore,
        //�_���[�W���󂯂�ƌ�������X�R�A
        damageScoreNum,
        //���W�A�C�e���̍ŏ��̐��ɂ��Ă�UI
        allCollectItemNum,
        //�������
        manual,
        //�����_
        point,
        //���[�_�[
        radar,
        //�^�C�g�����S
        tilteLogo,
        //�^�C�}�[�̘g
        timerFrame,
        //�c�莞�ԃX�R�A�̕���
        timeScore,
        //�c�莞�Ԃ̃X�R�A
        timeScoreNum,
        //���v�X�R�A�̕���
        totalScore,
        //���v�X�R�A
        totalScoreNum,
        //���W�A�C�e���̂����Q�b�g�������ɂ���
        getCollectItemNum,
        //�c�莞��
        timeNum,
        //���j���[��ʂ̘g
        menuFrame,
        //�v���C���s
        playUI,
        //���g���C
        retryUI,
        //���j���[��ʂ̃J�[�\��
        menuCursor,
        //�Q�[���I��UI
        exitUI,
        //�^�C�g����ʂŃX�e�[�W�I��������Ƃ��Ɏg��
        stageName,
        //�^�C�g���X�y�[�X�L�[�Ñ�
        titlePressSpaceKey,
        //�^�C�g����ʂɕ\������n�C�X�R�A
        titleHighScore,
        //�^�C�g����ʂɕ\������n�C�X�R�A����
        titleHiScoreNum,
        //�J�E���g�_�E���I����
        onGameStartCountDownEnd,
        //�_�ߌ��t
        PraiseWord,
        //�Q�[���I�����̃J�E���g�_�E��
        onGameEndCountDownEnd,
        //�c��̎��W�A�C�e���̐�
        remainingCollectItemNum,
        //�c��̎��W�A�C�e���ɂ��Ẵt���[�Y
        remainingCollectItemPhrase,
        //���W�A�C�e���̃A�C�R��
        collectIcon,
        //���W�A�C�e���̏W�߂鐔
        collectTargetNumberUI,
        //���U���g�X�y�[�X�L�[�Ñ�
        resultSpaceKey,
        //�`���[�W���@�����}�j���A��
        chargeManual,
        //�^�[�{�����}�j���A��
        turboManual,
        //���{�^��
        leftButton,
        //�E�̃{�^��
        rightButton,
        //���{�^��
        downButton,
        //�Q�[���I���A�i�E���X
        finishAnnounce,
        //�^�C�g���ɖ߂�{�^��
        returnTitleBottonUI,
        //������@�̌��ɒu���Ă����V�[�g
        playManualSheat,
        //�^�C�g���ŃX�e�[�W�����肷��Ƃ��̃{�^��
        stageSelectButton,
        //�p�b�h�ŗV�ԏꍇ�̉��{�^��
        xDownButton,
        //���̃X�e�[�W�œ�Ԗڂɂ����X�R�A
        titleSecondScoreNum,
        //���̃X�e�[�W��3�Ԗڂɂ����X�R�A
        titleThirdScoreNum,
        //�����L���O�̂P
        rank1,
        //�����L���O�̂Q
        rank2,
        //�����L���O�̂R
        rank3,
        //�ҏW�����X�e�[�W��V�Ԃ��߂�UI
        playEditStage,
        //�}�E�X
        editMenu,
        //�E�N���b�N�����Ƃ��̃}�E�X
        rightHoldMouse,
        //�ҏW���̑������
        editManual
    };

    /// <summary>
    /// UI�̏��������@�����͓ǂݍ��ݒi��
    /// </summary>
    enum class InitUIData
    {
        //�`��ꏊX
        drawX ,
        //Y
        drawY ,
        //�摜����
        width ,
        //�摜�c��
        height,
        //����������
        xNum,
        //�c������
        yNum,
        //�摜�̑��΃p�X
        graphPath,
        //�傫��
        size,
        //�������Ă���ꍇ�̃R�}����X�s�[�h
        frameSpeed
    };
    /// <summary>
    /// UI�Ŏ��ۂɎg�����
    /// </summary>
    struct  UIData
    {
        //�`��ꏊX
        int x = 0;
        //�`��ꏊY
        int y = 0;
        //������̉摜����
        int width = 0;
        //������̉摜�c��
        int height = 0;
        //�摜�n���h��
        std::vector<int> dataHandle;
        //�傫��
        float size = 0.0f;
        //�R�}���葬�x
        float frameSpeed = 0.0f;
    };
}
using namespace UIInit;
/// <summary>
/// UI��Z�߂�}�l�[�W���[
/// </summary>
class UIManager final:public AssetManager
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    UIManager();
    /// <summary>
    /// UI������
    /// </summary>
    /// <param name="uiKind">����������UI�̎��</param>
    /// <returns>UI�̕`��ɕK�v�ȏ���Ԃ�</returns>
    static UIData CreateUIData(UIKind uiKind);
    /// <summary>
    /// ������UI�̉摜���폜����
    /// </summary>
    /// <param name="ui">��������UI�摜</param>
    static void DeleteUIGraph(UIData* ui);
 private:
     /// <summary>
     /// UI�̏�������
     /// </summary>
     /// <param name="uiKind">����������UI</param>
     /// <returns>UI�̏����܂Ƃ߂��\����</returns>
     static UIData CreateUIData(int kindNum);
     //�S�Ă�UI�̃p�X
    static std::vector<std::string> uiPathVec;
    //UI�����Ɏg���X�L�[�}�̃p�X
    static std::string shemaPath;

};