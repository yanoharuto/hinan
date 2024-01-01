#include "JsonWriter.h"
#include <ostreamwrapper.h>
#include "writer.h"
#include "Utility.h"
/// <summary>
/// �ۑ�����t�@�C���̃p�X���w��
/// </summary>
/// <param name="filePath">�t�@�C���p�X</param>
JsonWriter::JsonWriter(std::string  filePath)
{
    fileName = filePath;
    //������Ȃ�������.json��ǉ�
    if (fileName.find(Utility::JSON_FILE)==std::string::npos)
    {
        fileName += Utility::JSON_FILE;
    }
}

/// <summary>
/// �����̃h�L�������g���o��
/// </summary>
/// <param name="writerDoc"></param>
void JsonWriter::Write(rapidjson::Document* writerDoc)const
{
    //�t�@�C���̒��g��S����������Ԃŏ�������
    std::ofstream ofs(fileName);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    writerDoc->Accept(writer);
}