#pragma once
#include "AssetManager.h"
/// <summary>
/// �`�惂�f���̕ۑ�
/// </summary>
class DrawModelManager final:AssetManager
{
public:
    //��������
    DrawModelManager();
    /// <summary>
    /// �e���f���̏����f���[�g
    /// </summary>
    ~DrawModelManager()override;
    /// <summary>
    /// model�����[�h���ēn��
    /// </summary>
    /// <param name="assetPath"></param>
    /// <returns>���łɃ��[�h���Ă��畡��</returns>
    int Get3DModelAssetHandle(std::string assetPath);
private:
    
    /// �`�惂�f���n���h��
    static std::unordered_map <std::string, int> modelMap;
};