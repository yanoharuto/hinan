#include "JsonWriter.h"
#include <ostreamwrapper.h>
#include "writer.h"
#include "Utility.h"
/// <summary>
/// 保存するファイルのパスを指定
/// </summary>
/// <param name="filePath">ファイルパス</param>
JsonWriter::JsonWriter(std::string  filePath)
{
    fileName = filePath;
    //見つからなかったら.jsonを追加
    if (fileName.find(Utility::JSON_FILE)==std::string::npos)
    {
        fileName += Utility::JSON_FILE;
    }
}

/// <summary>
/// 引数のドキュメントを出力
/// </summary>
/// <param name="writerDoc"></param>
void JsonWriter::Write(rapidjson::Document* writerDoc)const
{
    //ファイルの中身を全部消した状態で書き込む
    std::ofstream ofs(fileName);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    writerDoc->Accept(writer);
}