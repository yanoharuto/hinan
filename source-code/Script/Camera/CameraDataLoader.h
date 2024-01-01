#pragma once
#include "AssetManager.h"

/// <summary>
/// �J�����̏��������s��
/// </summary>
class CameraDataLoader final: public AssetManager
{
public:
	struct  CameraParamater
	{
		float nearValue;//�J�����̌����J�n�ʒu
		float farValue;//�J�����̌����ŏI1
		float lookAngle;//�J�����̉�p
		float targetBetween;//�^�[�Q�b�g�܂ł̋���
		float setYPos;//����
		float speed;//�ړ����x
	};
    /// <summary>
    /// �J�����ɕK�v�ȃp�����[�^
    /// </summary>
    enum class CameraParameter
    {
        //�`��͈͂̊J�n����
        setNearValue = 0,
        //�`��͈͂̍ŏI����
        setFarValue = 1,
        //�I�u�W�F�N�g�̌�����͈͊p
        setLookingAngle = 2,
        //�`��ΏۂƂ̋���
        setTargetBetween = 3,
        //�J������Y����
        setYPosition = 4,
        //�J�����̈ړ����x
        setCameraSpeed = 5,
    };
    /// <summary>
    /// �J�������g����V�[���̎��
    /// </summary>
    enum class UseCameraSceneKind
    {
        //�^�C�g���V�[���̃J����
        title = 0,
        //�V��ł鎞�̃J����
        game = 1,
        //���U���g��ʂł̃J����
        editor = 2
    };
    /// <summary>
    /// ��������񏊓�
    /// </summary>
    /// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
	CameraParamater GetCameraParamator(UseCameraSceneKind type) const;
private:
    static std::string schemaPath;
};

