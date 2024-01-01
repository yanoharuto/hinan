#pragma once
#include <vector>
#include <string>

/// <summary>
/// CSVファイルを読み込んで文字列コンテナで返す
/// </summary>
class CSVFileLoader
{
public:
    /// <summary>
    /// CSVファイルを読み込む
    /// </summary>
    /// <param name="filePath">読み込むファイルのパス</param>
    CSVFileLoader(std::string filePath);
    /// <summary>
    /// CSVファイルで読み込んだ文字列を渡す
    /// </summary>
    /// <returns> CSVファイルで読み込んだ文字列</returns>
    std::vector <std::string> GetStringData()const;
    /// <summary>
    /// CSVファイルで読み込んだ文字列を渡す
    /// </summary>
    /// <returns> CSVファイルで読み込んだ文字列</returns>
    std::vector <const char*> GetFileCharData()const;
    /// <summary>
    /// 読み込んだファイルの行の数
    /// </summary>
    /// <returns></returns>
    int GetLineCount()const;
    /// <summary>
    /// ファイルが開けたかどうか
    /// </summary>
    /// <returns>正常に開けたならTrue</returns>
    bool IsOpenFile()const;
private:
    /// <summary>
    /// 読み込んだファイルの各行のデータを抽出
    /// </summary>
    /// <param name="input">各行のデータ</param>
    /// <param name="delimiter">止める文字</param>
    void Split(std::string& input, char delimiter);
    //読み込んだファイルのデータ
    std::vector <std::string> loadData;
    //読み込んだファイルの行
    int lineCount;
    //ファイルが正常に開けたならTrue
    bool isOpen;
};

