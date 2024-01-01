#include "Wheels.h"
#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "AssetManager.h"
//�Ԃ̉�]��
const float Wheels::wheelDriveRotaPower = 4.4f;
//�^�C�������E�ɌX����
const float Wheels::wheelCurvePower = 1.7f;
//���̊p�x�܂Ń^�C���͌X����
const float Wheels::maxAxisY = 45.5f;
//�i�s�����ɉe������܂łɕK�v�ȃ^�C���̊p�x
const float Wheels::curbCalculationLine = 1.2f;
//�����@�O�ւƌ�ւ̋���
const float Wheels::wheelbase = 10.0f;
/// <summary>
/// �^�C���̍��E�̌X����������
/// </summary>
Wheels::Wheels()
{
	axisY = 0.0f;
}
/// <summary>
/// ���E�L�[����͂�����^�C���̊p�x��ύX
/// </summary>
void Wheels::Update()
{	
	//�E����������
	if (UserInput::GetInputState(UserInput::KeyInputKind::Right) != UserInput::InputState::Free)
	{		
		//y����]
		axisY = axisY < maxAxisY ? axisY + wheelCurvePower : maxAxisY;
	}
	//������������
	else if (UserInput::GetInputState(UserInput::KeyInputKind::Left) != UserInput::InputState::Free)
	{
		axisY = axisY > -maxAxisY ? axisY - wheelCurvePower : -maxAxisY;
	}
	//�ǂ�����������ĂȂ�������^�C�������ɖ߂�
	else if (fabsf(axisY) > curbCalculationLine)
	{
		axisY += axisY > 0 ? -wheelCurvePower : wheelCurvePower;
		//������x�߂��Ă���p�x��0�ɂ���
		if (fabsf(axisY) < curbCalculationLine)
		{
			axisY = 0;
		}
	}	
}

/// <summary>
/// �i�s���������x�Ȃ��邩�Ԃ�
/// </summary>
/// <param name="velocitySize">�����̃x�N�g���̑傫��</param>
/// <returns>�i�s���������E�ɉ��x����邩�Ԃ�</returns>
float Wheels::GetMoveDirTheta(const float velocitySize)const
{
	//�E�Ƀ^�C�����Ȃ����Ă���Ȃ�
	if (axisY > curbCalculationLine)
	{
		//��]���a�ƈړ����x�ŋȂ���ʂ��o��
		return atan2f(velocitySize, GetRotationRadius()); 
	}
	//���Ƀ^�C�����Ȃ����Ă���Ȃ�
	else if (axisY < -curbCalculationLine)
	{
		return -atan2f(velocitySize,GetRotationRadius());
	}
	return 0.0f;
}

/// <summary>
/// ��]���邽�߂̔��a��Ԃ�
/// </summary>
/// <returns>��]���a</returns>
float Wheels::GetRotationRadius()const
{
	//������x�^�C�����Ȃ����Ă�����Ȃ���n�߂�
	if (fabsf(axisY) > curbCalculationLine)
	{
		//�^�C���̊p�x���^���W�F���g��
		float rota = tan(static_cast<float> (fabsf(axisY)) * RAGE);
		//�����������ĉ�]���a���o��
		return  wheelbase / rota;
	}
	return 0.0f;
}
