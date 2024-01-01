#include <fstream>
#include <sstream>
#include "CSVFileLoader.h"
#include "Utility.h"


using namespace std;
/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
/// <param name="filePath">�ǂݍ��ރt�@�C���̃p�X</param>
CSVFileLoader::CSVFileLoader(std::string filePath)
{
    //�t�@�C�����J����
    lineCount = 0;
    ifstream ifs(filePath.c_str());
    isOpen = static_cast<bool>(ifs);
    //1�s���ǂݍ���
    string line;
    while (getline(ifs, line)) 
    {
        lineCount++;
        Split(line, ',');//,�܂œǂݍ���
    }
    //����
    ifs.close();
}
/// <summary>
/// CSV�t�@�C���œǂݍ��񂾕������n��
/// </summary>
/// <returns> CSV�t�@�C���œǂݍ��񂾕�����</returns>
std::vector<std::string> CSVFileLoader::GetStringData()const
{
    return loadData;
}
/// <summary>
/// CSV�t�@�C���œǂݍ��񂾕������n��
/// </summary>
/// <returns> CSV�t�@�C���œǂݍ��񂾕�����</returns>
std::vector<const char*> CSVFileLoader::GetFileCharData()const
{
    std::vector<const char*> charVec;
    //char�ɕϊ����ēn��
    for (int i = 0; i < CONTAINER_GET_SIZE(loadData); i++)
    {
        charVec.push_back(loadData[i].c_str());
    }
    return charVec;
}
/// <summary>
/// �ǂݍ��񂾃t�@�C���̍s����n��
/// </summary>
/// <returns>�ǂݍ��񂾃t�@�C���̍s��</returns>
int CSVFileLoader::GetLineCount()const
{
    return lineCount;
}
/// <summary>
/// �t�@�C�����J�������ǂ���
/// </summary>
/// <returns>����ɊJ�����Ȃ�True</returns>
bool CSVFileLoader::IsOpenFile() const
{
    return isOpen;
}
/// <summary>
/// �ǂݍ��񂾃t�@�C���̊e�s�̃f�[�^�𒊏o
/// </summary>
/// <param name="input">�e�s�̃f�[�^</param>
/// <param name="delimiter">�~�߂镶��</param>
void CSVFileLoader::Split(std::string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    //�������܂ňڂ��Ă���
    while (getline(stream, field, delimiter)) 
    {
        loadData.push_back(field);
    }
}
