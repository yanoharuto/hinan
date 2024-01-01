#include "UIDrawer.h"
#include "DxLib.h"
#include "Utility.h"

//����
 int UIDrawer::screenWidth = Utility::SCREEN_WIDTH;
//�c��
 int UIDrawer::screenHeight = Utility::SCREEN_HEIGHT;
//�����䗦
 float UIDrawer:: widthRaito = 0.0f;
//�c���䗦
 float UIDrawer:: heightRaito = 0.0f;
 //��ʂ̑傫���䗦
 float UIDrawer::UIDrawer::screenSizeRaito = 1.0f;
 /// <summary>
/// ��ʃT�C�Y��������
/// </summary>
 UIDrawer::UIDrawer()
 {
     int color;
     //��ʃT�C�Y
     GetScreenState(&screenWidth, &screenHeight, &color);
     //�����䗦
     widthRaito = static_cast<float>(screenWidth / Utility::SCREEN_WIDTH);
     //�c���䗦
     heightRaito = static_cast<float>(screenHeight / Utility::SCREEN_HEIGHT);
     //HD�̑傫���Ɣ�r�����傫��
     screenSizeRaito = static_cast<float>((screenWidth + screenHeight) / (Utility::SCREEN_WIDTH + Utility::SCREEN_HEIGHT));
 }
 /// <summary>
 /// drawRotaGraph����ʂ̃T�C�Y�ɍ��킹�ďo����悤�ɂ���
 /// </summary>
 /// <param name="data">�`�悵����UI</param>
 /// <param name="gHIndex">�`�悵����UI�̓Y����</param>
 /// <param name="angle">UI���X����</param>
 /// <param name="trans">�����x�L���t���O</param>
 /// <returns>���s�����false</returns>
bool UIDrawer::DrawRotaUI(UIData data, int gHIndex, float angle, bool trans)
{
   gHIndex = gHIndex % data.dataHandle.size();
   //��ʃT�C�Y�ɍ��킹���`��
   int x = static_cast<int>(data.x * widthRaito);
   int y = static_cast<int>(data.y * heightRaito);
   double size = static_cast<double>(data.size * screenSizeRaito);
   int success = DrawRotaGraph(x, y, size, angle, data.dataHandle[gHIndex], trans);
   return success != -1;
}
/// <summary>
/// �X�N���[���̑z��̑傫���Ƃ̍���{���œn��
/// </summary>
/// <returns></returns>
float UIDrawer::GetScreenRaito()
{
    return screenSizeRaito;
}