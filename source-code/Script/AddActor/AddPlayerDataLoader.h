#pragma once
#include "AddObjectDataLoader.h"
/// <summary>
/// �v���C���[�̒ǉ����ǂݎ��N���X
/// </summary>
class AddPlayerDataLoader final: public AddObjectDataLoader
{
public:
    /// <summary>
    /// �v���C���[�̒ǉ���������
    /// </summary>
    AddPlayerDataLoader();
private:
    //�v���C���[�̒ǉ����X�L�[�}
    const std::string addDataSchema = "playerSpeedSchema.json";
};

