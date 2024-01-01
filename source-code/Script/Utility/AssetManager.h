#pragma once
#include <vector>
#include <string>
#include <unordered_map>
class JsonFileLoader;
/// <summary>
/// �A�Z�b�g�܂ł̃p�X�����L�ł���悤�ɐe�N���X�ɓn��
/// </summary>
class AssetManager abstract
{
public:
    enum class AssetList;
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    AssetManager();
    virtual ~AssetManager() {};

    enum class AssetList
    {
        camera,//�J����
        effect,//�G�t�F�N�g
        object,//�I�u�W�F�N�g
        ui,//UI
        sound,//��
        stageData,//�X�e�[�W�̏����ʒu�␧������
        objectAddData//�I�u�W�F�N�g�̒ǉ����
    };
    /// <summary>
    /// �����̃t�@�C�������݂��邩���ׂ�
    /// </summary>
    /// <param name="fileName"></param>
    /// <returns>���݂���Ȃ�true</returns>
    static bool IsExistFile(std::string fileName);
    /// <summary>
    /// jsonFile�œǂݎ�ꂻ�������ׂ�
    /// </summary>
    /// <returns>���ׂꂻ���Ȃ�true</returns>
    static bool IsExistJsonFile();
protected:
    /// <summary>
    /// �������Ŏg��CSV�t�@�C���̃p�X������
    /// </summary>
    /// <param name="fileKind">�~�����t�@�C���̎��</param>
    /// <returns>�������Ŏg��CSV�t�@�C���̃p�X</returns>
   static std::string GetInitCsvFilePath(AssetList fileKind);
   /// <summary>
   /// �������Ŏg��Json�t�@�C���̃p�X������
   /// </summary>
   /// <param name="fileKind">�~�����t�@�C���̎��</param>
   /// <returns>�������Ŏg��Json�t�@�C���̃p�X</returns>
   static std::string GetInitJsonFilePath(AssetList fileKind);
   /// <summary>
   /// asset�ꗗ��Vector�Ɉڂ��Ă���
   /// </summary>
   /// <param name="listKind">�ǂݎ�肽���t�@�C���̎��</param>
   static std::vector<std::string> GetAssetList(AssetList listKind);
   //csv�t�@�C���܂ł̃p�X
   static std::string const initCSVFilePath;
   //json�t�@�C���܂ł̃p�X
   static std::string const initJSONFilePath;
private:
    //asset�ꗗ�Ŏg���X�L�[�}�̃p�X
    static const std::string listSchemaPath;
    //Json�t�@�C�������邩���ׂ�̂Ɏg��
    static const std::string jsonExistFile;
    //�������t�@�C���̖��O
    static std::string const initFileNames[];
};