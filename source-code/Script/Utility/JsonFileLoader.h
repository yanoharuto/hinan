#pragma once
#include <vector>
#include <rapidjson.h>
#include <string>
#include "document.h"
#include "istreamwrapper.h"
#include "schema.h"
#include "stringbuffer.h"
/// <summary>
/// Json�t�@�C���ǂݎ��N���X
/// </summary>
class JsonFileLoader
{
public:
    /// <summary>
    /// Json�`���̃t�@�C�����J��
    /// </summary>
    /// <param name="filePath">�J�������t�@�C��</param>
    /// <param name="schemaFileName">�J���t�@�C����Schema</param>
    JsonFileLoader(std::string filePath,std::string schemaFileName);
    /// <summary>
    /// Schema�ƊJ�������t�@�C�����K�����Ă���Ȃ�
    /// </summary>
    /// <returns>�K�������Ȃ�True</returns>
    bool IsAccept()const;
    /// <summary>
    /// integer�^��ǂݎ��
    /// </summary>
    /// <param name="dataName">�ǂݎ�肽�������o�̖��O</param>
    /// <returns>�~�����f�[�^</returns>
    int GetLoadInt(std::string dataName)const;
    /// <summary>
    /// �K�v��float�^��ǂݎ��
    /// </summary>
    /// <param name="dataName">�ǂݎ�肽�������o�̖��O</param>
    /// <returns>��肽���f�[�^</returns>
    float GetLoadFloat(std::string dataName)const;
    /// <summary>
    /// �K�v�ȕ������ǂݎ��
    /// </summary>
    /// <param name="dataName">�ǂݎ�肽�������o�̖��O</param>
    /// <returns>��肽���f�[�^</returns>
    std::string GetLoadString(std::string dataName)const;
    /// <summary>
    /// �K�v�Ȕz���ǂݎ��
    /// </summary>
    /// <param name="dataName">�~�����z��̖��O</param>
    /// <returns>rapidjson::Value�^�̔z��</returns>
    const rapidjson::Value& GetLoadArray(std::string dataName)const;
    /// <summary>
    /// �ǂݎ�������e��Value�Ɉڂ�
    /// </summary>
    /// <param name="value">�ڂ���</param>
    /// <param name="dataName">�ڂ��������e</param>
    void MoveValue(rapidjson::Value& value, std::string dataName);
private:
    //Schema�ƊJ�������t�@�C�����K�����Ă���Ȃ�
    bool isAccept;
    //�ǂݎ����
    rapidjson::Document loadDoc;
    //�X�L�[�}�t�@�C���܂ł̃p�X
    static std::string const jsonSchemaFilePath;
};