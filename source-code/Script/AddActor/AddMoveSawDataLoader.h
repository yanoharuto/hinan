#pragma once
#include "AddObjectDataLoader.h"
/// <summary>
/// �ړ��ۋ��̏���ǂݎ��
/// </summary>
class AddMoveSawDataLoader final: public AddObjectDataLoader
{
public:
    /// <summary>
    /// �ړ��ۋ��̏���ǂݎ��
    /// </summary>
    AddMoveSawDataLoader();

private:
    //�ۋ��̒ǉ����X�L�[�}
    const std::string addDataSchema = "moveSawSchema.json";
};

