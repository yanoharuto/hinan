#pragma once
#include "AddObjectDataLoader.h"
/// <summary>
/// ��s�D�̒ǉ����ǂݎ��N���X
/// </summary>
class AddFlyShipDataLoader final:public AddObjectDataLoader
{
public:
    /// <summary>
    /// ��s�D�̏���ǂݎ��
    /// </summary>
    /// <param name="data">�ǂݎ���s�D</param>
    AddFlyShipDataLoader(AddData data);
private:
    //��s�D�̒ǉ����X�L�[�}
    const std::string addDataSchema = "flyShipAddDataSchema.json";
};

