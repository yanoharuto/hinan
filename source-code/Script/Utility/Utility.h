#pragma once 
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <filesystem>
#include <memory>
namespace Utility
{
    //�֐��̃}�N��
    //���S�ɃC���X�^���X���J�� 
#define SAFE_DELETE(p) {if(p){ delete p; p = nullptr;}}
#define SAFE_RESET(p) {if(p){ p.reset(); p = nullptr;}}

//�������float�^�ɕύX
#define STR_TO_F(str) static_cast<float>(atof(str.c_str()))
//�������double�^�ɕύX
#define STR_TO_D(str) static_cast<double>(atof(str.c_str()))
//�������int�^�ɕύX
#define STR_TO_I(str) static_cast<int>(atoi(str.c_str()))
//���X�g��x�N�^�[�̃T�C�Y��int�^��
#define CONTAINER_GET_SIZE(container) static_cast<int>(container.size())
//static_cast<int>�������
#define CAST_I(data) static_cast<int>(data)
//�G���[�E�B���h�E
#define ERROR_MSG(str){MessageBox(NULL,TEXT(str),TEXT("Error"),MB_OK|MB_ICONERROR);}
//��ʉ��T�C�Y
    constexpr int SCREEN_WIDTH = 1920;
    //��ʏc�T�C�Y
    constexpr int SCREEN_HEIGHT = 1030;
    //1�o�C�g�ő�l
    constexpr int MAX_ONE_BYTE_RANGE = 255;
    //�f���^�^�C��
    constexpr float DELTATIME = 0.016667f;
    //100
    constexpr int HUNDRED = 100;

    constexpr char JSON_FILE[] = ".json";

    constexpr char CSV_FILE[] = ".csv";
}