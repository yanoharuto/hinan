#pragma once
#include "AssetManager.h"
#include <string>
#include <vector>
/// <summary>
/// �I�u�W�F�N�g�̒ǉ�����ǂݎ��N���X
/// </summary>
class AddObjectDataLoader abstract:public AssetManager
{
public:
    enum class AddData;
    /// <summary>
    /// �ǉ�����ǂݎ��
    /// </summary>
    AddObjectDataLoader();
    /// <summary>
    /// �ǉ����𕶎���œn��
    /// </summary>
    /// <returns>������œn��</returns>
    virtual std::vector<std::string> GetLoadData()const { return loadData; };
    //�ǉ����̎��
    enum class AddData
    {
        playerSpeed,//�v���C���[�̈ړ����
        circleFlyShip,//�~�w�g��ł��s�D�̒ǉ����
        upDownFlyShip,//�㉺�Ɉړ������s�D�̒ǉ����
        bomberShip,//���e���Ƃ���s�D�̒ǉ����
        moveSaw//�ړ���]�̂�����̒ǉ����
    };
protected:
    //�ǉ���񕶎���
    std::vector<std::string> loadData;
    //�ǂݎ�����ǉ����̃��X�g
    std::vector<std::string> addDataList;
};