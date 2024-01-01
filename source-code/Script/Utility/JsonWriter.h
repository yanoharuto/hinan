#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <rapidjson.h>
#include <document.h>

/// <summary>
/// Jsonを書き込むクラス
/// </summary>
class JsonWriter abstract
{
public:
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    JsonWriter() {};
    /// <summary>
    /// 保存するファイルのパスを指定
    /// </summary>
    /// <param name="filePath">ファイルパス</param>
    JsonWriter(std::string filePath);
    /// <summary>
    /// 引数のドキュメントを出力
    /// </summary>
    /// <param name="writerDoc"></param>
    void Write(rapidjson::Document* writerDoc)const;
protected:
    //保存するファイル
    std::string fileName;
};