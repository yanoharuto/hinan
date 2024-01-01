#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
/// <summary>
/// �G�t�F�N�g�̏�����
/// </summary>
/// <returns>���s������-1</returns>
int Effect_Initialize() 
{
    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);
    //Effekseer������������
    if (Effekseer_Init(8000) == -1)
    {
        return -1;
    }
    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();
    // Z�o�b�t�@��L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetUseZBuffer3D(TRUE);
    // Z�o�b�t�@�ւ̏������݂�L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetWriteZBuffer3D(TRUE);

    Effekseer_Set2DSetting(Utility::SCREEN_WIDTH,Utility::SCREEN_HEIGHT);
    return 0;
}
/// <summary>
/// �G�t�F�N�g�̏I������
/// </summary>
void Effect_Finalize() {

    // Effekseer���I������B
    Effkseer_End();
}