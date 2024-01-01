#pragma once
#include "DxLib.h"
#include <string>

/// <summary>
/// �^�C����Y������Ɖ�]���a���o��
/// </summary>
class Wheels 
{
public:
	/// <summary>
	/// �^�C���̍��E�̌X����������
	/// </summary>
	Wheels();
	/// <summary>
	/// ���E�L�[����͂�����^�C���̊p�x��ύX
	/// </summary>
	void Update();
	/// <summary>
	/// �i�s���������x�Ȃ��邩�Ԃ�
	/// </summary>
	/// <param name="velocitySize">�����̃x�N�g���̑傫��</param>
	/// <returns>�i�s���������E�ɉ��x����邩�Ԃ�</returns>
	float GetMoveDirTheta(const float velocitySize) const;
private:	
	/// <summary>
    /// ��]���邽�߂̔��a��Ԃ�
    /// </summary>
	/// <returns>��]���a</returns>
	float GetRotationRadius() const;
	//�Ԃ̍��E�ւ̌X��
	float axisY = 0.0f;
	//�Ԃ̉�]��
	static const float wheelDriveRotaPower;
	//�^�C�������E�ɌX����
	static const float wheelCurvePower;
	//���̊p�x�܂Ń^�C���͌X����
	static const float maxAxisY;
	//�i�s�����ɉe������܂łɕK�v�ȃ^�C���̊p�x
	static const float curbCalculationLine;
	//�����@�O�ւƌ�ւ̋���
	static const float wheelbase;
};