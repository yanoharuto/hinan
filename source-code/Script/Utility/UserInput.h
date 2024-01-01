#pragma once
#include "DxLib.h"
//���͂̎��
constexpr int KEY_INPUT_KIND_NUM = 15;
//���o�[�̒l�̕�
constexpr int LEVER_VALUE = 12767;
//�}�E�X�̃L�[�̎��
constexpr int EDIT_KEY_KIND = 5;
/// <summary>
/// ���[�U�[�����͂������
/// </summary>
class UserInput
{
public:

    /// <summary>
    /// ���͂����L�[���ǂꂩ������悤�ɏ���
    /// </summary>
    UserInput();
    ~UserInput() {};
    /// <summary>
    /// �{�^���̓��͏�
    /// </summary>
    enum class InputState
    {
        //�������Ă��Ȃ�
        Free,
        //����
        Push,
        //�����Ɠ���
        Hold,
        //������
        Detach
    };
    /// <summary>
    /// �{�^���̏��
    /// </summary>
    enum class KeyInputKind
    {
        //�����
        Up = 0,
        //������
        Down = 1,
        //��
        Left = 2,
        //�E
        Right = 3,
        //�X�y�[�X�L�[
        Space = 4,
        //�G�X�P�[�v�L�[
        EscapeKey = 5,
        //W�L�[
        WKey = 6,
        //D�L�[
        DKey = 7,
        //S�L�[
        SKey = 8,
        //A�L�[
        AKey = 9,
        //�}�E�X�̍�
        MouseLeft = 10,
        //�}�E�X�̉E
        MouseRight = 11,
        //�R���g���[���L�[
        CtrKey = 12,
        //Z�L�[
        ZKey = 13,
        //Y�L�[
        YKey = 14
    };

    /// <summary>
    /// ���͏󋵍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �{�^���̓��͏��
    /// </summary>
    /// <param name="inputKind"></param>
    /// <returns></returns>
    static UserInput::InputState GetInputState(KeyInputKind inputKind);
    /// <summary>
    /// �Q�[���p�b�h�ŗV��ł��邩
    /// </summary>
    /// <returns>�V��ł�����True</returns>
    static bool IsInputPad() { return isInputPad; };
private:
    /// <summary>
    /// �{�^���̓��͍X�V
    /// </summary>
    /// <param name="_Input">���͏�</param>    
    /// <param name="_Button">�X�V�������{�^��</param>
    void UpdateButton(bool inputJudge,InputState* _Button);
    /// <summary>
    /// �ҏW�Ŏg���{�^���̍X�V
    /// </summary>
    /// <param name="code"></param>
    void UpdateButton(KeyInputKind code);
    /// <summary>
    /// �Q�[���p�b�h�̓��͍X�V
    /// </summary>
    void UpdateGamePadButton();
    //�{�^���̏��
    static InputState keyInputState[KEY_INPUT_KIND_NUM];
    //�p�b�h�̏��
    static XINPUT_STATE xInput;
    //A�{�^���̊��蓖�Ĕԍ�
    const int aButtonNum = 12;
    //B�{�^���̊��蓖�Ĕԍ�
    const int bButtonNum = 13;
    //�Q�[���p�b�h�œ��͂��邩
    static bool isInputPad;
    //�Ή����Ă���{�^���̈ꗗ
    const int keyInputCode[KEY_INPUT_KIND_NUM] = { PAD_INPUT_UP ,PAD_INPUT_DOWN ,PAD_INPUT_LEFT ,PAD_INPUT_RIGHT ,PAD_INPUT_10 ,PAD_INPUT_9 ,PAD_INPUT_8 ,PAD_INPUT_6 ,PAD_INPUT_5,PAD_INPUT_4,MOUSE_INPUT_LEFT, MOUSE_INPUT_RIGHT,KEY_INPUT_LCONTROL,KEY_INPUT_Z,KEY_INPUT_Y };
};