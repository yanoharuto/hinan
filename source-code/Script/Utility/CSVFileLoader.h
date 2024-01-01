#pragma once
#include <vector>
#include <string>

/// <summary>
/// CSV�t�@�C����ǂݍ���ŕ�����R���e�i�ŕԂ�
/// </summary>
class CSVFileLoader
{
public:
    /// <summary>
    /// CSV�t�@�C����ǂݍ���
    /// </summary>
    /// <param name="filePath">�ǂݍ��ރt�@�C���̃p�X</param>
    CSVFileLoader(std::string filePath);
    /// <summary>
    /// CSV�t�@�C���œǂݍ��񂾕������n��
    /// </summary>
    /// <returns> CSV�t�@�C���œǂݍ��񂾕�����</returns>
    std::vector <std::string> GetStringData()const;
    /// <summary>
    /// CSV�t�@�C���œǂݍ��񂾕������n��
    /// </summary>
    /// <returns> CSV�t�@�C���œǂݍ��񂾕�����</returns>
    std::vector <const char*> GetFileCharData()const;
    /// <summary>
    /// �ǂݍ��񂾃t�@�C���̍s�̐�
    /// </summary>
    /// <returns></returns>
    int GetLineCount()const;
    /// <summary>
    /// �t�@�C�����J�������ǂ���
    /// </summary>
    /// <returns>����ɊJ�����Ȃ�True</returns>
    bool IsOpenFile()const;
private:
    /// <summary>
    /// �ǂݍ��񂾃t�@�C���̊e�s�̃f�[�^�𒊏o
    /// </summary>
    /// <param name="input">�e�s�̃f�[�^</param>
    /// <param name="delimiter">�~�߂镶��</param>
    void Split(std::string& input, char delimiter);
    //�ǂݍ��񂾃t�@�C���̃f�[�^
    std::vector <std::string> loadData;
    //�ǂݍ��񂾃t�@�C���̍s
    int lineCount;
    //�t�@�C��������ɊJ�����Ȃ�True
    bool isOpen;
};

