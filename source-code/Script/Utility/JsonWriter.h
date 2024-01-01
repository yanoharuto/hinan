#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <rapidjson.h>
#include <document.h>

/// <summary>
/// Json���������ރN���X
/// </summary>
class JsonWriter abstract
{
public:
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    JsonWriter() {};
    /// <summary>
    /// �ۑ�����t�@�C���̃p�X���w��
    /// </summary>
    /// <param name="filePath">�t�@�C���p�X</param>
    JsonWriter(std::string filePath);
    /// <summary>
    /// �����̃h�L�������g���o��
    /// </summary>
    /// <param name="writerDoc"></param>
    void Write(rapidjson::Document* writerDoc)const;
protected:
    //�ۑ�����t�@�C��
    std::string fileName;
};