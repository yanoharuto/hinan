#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <rapidjson.h>
#include <document.h>
#include "writer.h"
#include "DxLib.h"
//�������f�[�^�̎�ނ̐�
#define EDIT_ARRANGEMENT_DATA_KIND_NUM 6
//Json�Ŏg���I�u�W�F�N�g���ʔԍ��̕�����
constexpr char OBJNUM_MEMBER[] = "objNum";
//���W�A�C�e���������ꂽ�Ƃ��ɏo�Ă��邩��\���p�����[�^�[
constexpr char COLLECTNUM_MEMBER[] = "collectNum";
//X���W
constexpr char POSX_MEMBER[] = "x";
//Z���W
constexpr char POSZ_MEMBER[] = "z";
//X����
constexpr char DIRX_MEMBER[] = "dirX";
//Z����
constexpr char DIRZ_MEMBER[] = "dirZ";
//��L�̗v�f���܂Ƃ߂��z��
constexpr char ARRANGEDATA_MEMBER[] = "arrangeData";
/// <summary>
/// �ۑ����������̎��
/// </summary>
enum class EditArrangementDataKind
{
    //�ۑ�����I�u�W�F�N�g�̎��
    objectKindNum = 0,
    //�o�Ă���^�C�~���O�̎��W�A�C�e���̐�
    appearCollectNum = 1,
    //�������WX
    positionX = 2,
    //�������WY
    positionZ = 3,
    //��������X
    directionX = 4,
    //��������Z
    directionZ = 5,
};
/// <summary>
/// �ۑ����������
/// </summary>
struct PlacementData
{
    //�I�u�W�F�N�g�̎��
    int objKind = 0;
    //���Ԗڂ̎��W�A�C�e���̃^�C�~���O��
    int collectNum = 0;
    //�|�W�V����X
    float posX = 0;
    //�|�W�V����Z
    float posZ = 0;
    //����X
    float dirX = 0;
    //����Z
    float dirZ = 0;
    /// <summary>
    /// �ۑ����邽�߂�Json��Value�ɓo�^���ĕԂ�
    /// </summary>
    /// <param name="allocator">Json�̃A���P�[�^�[</param>
    /// <returns></returns>
    void SetEditPlaceData(rapidjson::Value& objValue, rapidjson::Document::AllocatorType& allocator) const
    {
        objValue.AddMember(OBJNUM_MEMBER, objKind, allocator);
        objValue.AddMember(COLLECTNUM_MEMBER, collectNum, allocator);
        objValue.AddMember(POSX_MEMBER, posX, allocator);
        objValue.AddMember(POSZ_MEMBER, posZ, allocator);
        objValue.AddMember(DIRX_MEMBER, dirX, allocator);
        objValue.AddMember(DIRZ_MEMBER, dirZ, allocator);
    }
    /// <summary>
    /// Json�̒l����ϊ����ďꏊ�f�[�^�ɂ���
    /// </summary>
    /// <returns></returns>
    void ConversionJsonToPlacementData(const rapidjson::Value* objValue)
    {
        objKind = objValue->FindMember(OBJNUM_MEMBER)->value.GetInt();
        collectNum = objValue->FindMember(COLLECTNUM_MEMBER)->value.GetInt();
        posX = objValue->FindMember(POSX_MEMBER)->value.GetFloat();
        posZ = objValue->FindMember(POSZ_MEMBER)->value.GetFloat();
        dirX = objValue->FindMember(DIRX_MEMBER)->value.GetFloat();
        dirZ = objValue->FindMember(DIRZ_MEMBER)->value.GetFloat();
    }
};