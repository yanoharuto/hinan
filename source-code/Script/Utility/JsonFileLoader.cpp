#include <fstream>
#include <iostream>
#include "JsonFileLoader.h"
//�X�L�[�}�t�@�C���܂ł̃p�X
std::string const JsonFileLoader::jsonSchemaFilePath = "data/Json/Schema/";
/// <summary>
/// Json�`���̃t�@�C�����J��
/// </summary>
/// <param name="filePath">�J�������t�@�C��</param>
/// <param name="schemaFileName">�J���t�@�C����Schema</param>
JsonFileLoader::JsonFileLoader(std::string filePath, std::string schemaFileName)
{
    //�X�L�[�}���珑�����𒲂ׂ�
    std::ifstream schema_ifs(jsonSchemaFilePath + schemaFileName);
    rapidjson::IStreamWrapper schema_isw(schema_ifs);
    rapidjson::Document schema_doc;
    schema_doc.ParseStream(schema_isw);
    //�ǂݎ�肽���f�[�^�t�@�C�����J��
    std::ifstream ifs(filePath);
    rapidjson::IStreamWrapper isw(ifs);
    loadDoc.ParseStream(isw);
    //�X�L�[�}�ʂ�̏����������ׂ�
    rapidjson::SchemaDocument schema(schema_doc);
    rapidjson::SchemaValidator validator(schema);
    isAccept = loadDoc.Accept(validator);
    //���s����
    if (!isAccept) {
        rapidjson::StringBuffer sb;
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);//���\�[�X�̏ꏊ��SB�ɓn��
        std::cout << "Invalid schema:" << sb.GetString() << std::endl;
        std::cout << "Invalid keyword:" << validator.GetInvalidSchemaKeyword() << std::endl;
    }
}
/// <summary>
/// Schema�ƊJ�������t�@�C�����K�����Ă���Ȃ�
/// </summary>
/// <returns>�K�������Ȃ�True</returns>
bool JsonFileLoader::IsAccept() const
{
    return isAccept;
}
/// <summary>
/// integer�^��ǂݎ��
/// </summary>
/// <param name="dataName">�ǂݎ�肽�������o�̖��O</param>
/// <returns>�~�����f�[�^</returns>
int JsonFileLoader::GetLoadInt(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetInt();
}
/// <summary>
/// float�^
/// </summary>
/// <param name="dataName">�ǂݎ�肽���f�[�^</param>
/// <returns>��肽���f�[�^</returns>
float JsonFileLoader::GetLoadFloat(std::string dataName)const
{
    return loadDoc[dataName.c_str()].GetFloat();
}
/// <summary>
/// �K�v�ȃf�[�^�������ǂݎ��
/// </summary>
/// <param name="dataName">�ǂݎ�肽���f�[�^�̖��O</param>
/// <returns>��肽���f�[�^</returns>
std::string JsonFileLoader::GetLoadString(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetString();
}
/// <summary>
/// �K�v�Ȕz���ǂݎ��
/// </summary>
/// <param name="dataName">�~�����z��̖��O</param>
/// <returns>rapidjson::Value�^�̔z��</returns>
const rapidjson::Value& JsonFileLoader::GetLoadArray(std::string dataName) const
{
    return loadDoc[dataName.c_str()].GetArray();
}

/// <summary>
/// �ǂݎ�������e��Value�Ɉڂ�
/// </summary>
/// <param name="value">�ڂ���</param>
/// <param name="dataName">�ڂ��������e</param>
void JsonFileLoader::MoveValue(rapidjson::Value& value, std::string dataName)
{
    value = loadDoc.FindMember(dataName.c_str())->value;
}
