#include <fstream>
#include <sstream>
#include "CSVFileLoader.h"
#include "Utility.h"


using namespace std;
/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <param name="filePath">読み込むファイルのパス</param>
CSVFileLoader::CSVFileLoader(std::string filePath)
{
    //ファイルを開いて
    lineCount = 0;
    ifstream ifs(filePath.c_str());
    isOpen = static_cast<bool>(ifs);
    //1行ずつ読み込む
    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');//,まで読み込む
    }
    //閉じる
    ifs.close();
}
/// <summary>
/// CSVファイルで読み込んだ文字列を渡す
/// </summary>
/// <returns> CSVファイルで読み込んだ文字列</returns>
std::vector<std::string> CSVFileLoader::GetStringData()const
{
    return loadData;
}
/// <summary>
/// CSVファイルで読み込んだ文字列を渡す
/// </summary>
/// <returns> CSVファイルで読み込んだ文字列</returns>
std::vector<const char*> CSVFileLoader::GetFileCharData()const
{
    std::vector<const char*> charVec;
    //charに変換して渡す
    for (int i = 0; i < CONTAINER_GET_SIZE(loadData); i++)
    {
        charVec.push_back(loadData[i].c_str());
    }
    return charVec;
}
/// <summary>
/// 読み込んだファイルの行数を渡す
/// </summary>
/// <returns>読み込んだファイルの行数</returns>
int CSVFileLoader::GetLineCount()const
{
    return lineCount;
}
/// <summary>
/// ファイルが開けたかどうか
/// </summary>
/// <returns>正常に開けたならTrue</returns>
bool CSVFileLoader::IsOpenFile() const
{
    return isOpen;
}
/// <summary>
/// 読み込んだファイルの各行のデータを抽出
/// </summary>
/// <param name="input">各行のデータ</param>
/// <param name="delimiter">止める文字</param>
void CSVFileLoader::Split(std::string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    //第二引数まで移していく
    while (getline(stream, field, delimiter)) 
    {
        loadData.push_back(field);
    }
}
