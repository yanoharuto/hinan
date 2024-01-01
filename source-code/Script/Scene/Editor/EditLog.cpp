#include "EditLog.h"
#include "Utility.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <rapidjson.h>
#include <document.h>
#include "istreamwrapper.h"
#include "JsonFileLoader.h"
/// <summary>
/// �ҏW����t�@�C���̖��O�ƕҏW������ۑ��@
/// </summary>
/// <param name="logFileName">�t�@�C���̖��O</param>
/// <param name="firstTotalEditNum">�ҏW����</param>
EditLog::EditLog(std::string logFileName, int firstTotalEditNum)
    :JsonWriter(logFileName)
{
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    rapidjson::Value myArray(rapidjson::kArrayType);
    //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);
    //�t�@�C���̒��g��S����������Ԃŏ�������
    Write(&jsonDoc);
    firstTotalNum = firstTotalEditNum;
}
/// <summary>
/// placeData����납��prevNum�Ԗڂɒǉ�
/// </summary>
/// <param name="prevNum">�߂肽���ꏊ</param>
/// <param name="totalEdit">�ۑ��������I�u�W�F�N�g�̑���</param>
/// <param name="nowEditNum">�ҏW�ԍ�</param>
/// <param name="placeData">�ۑ����������</param>
void EditLog::SaveEditDataLog(int prevNum, int totalEdit, int nowEditNum, PlacementData placeData)
{
    auto json = new JsonFileLoader(fileName, schemaStr);
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    //�ǂݍ��񂾓��e�����n
    rapidjson::Value myArray(rapidjson::kArrayType);
    json->MoveValue(myArray,ARRANGEDATA_MEMBER);
    //�ߋ��̃f�[�^�������̂ڂ��Ă������ɋL�^������
    if (!myArray.Empty() && prevNum != 0)
    {
        myArray.Erase(myArray.End() - prevNum, myArray.End());//�����̂ڂ����Ƃ���܂ŕۑ�
    }
    //�ǋL���������̂�ǉ�
    myArray.PushBack(GetEditPlaceData(totalEdit, nowEditNum, placeData, allocator), allocator);

    //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);

    //�t�@�C���̒��g��S����������Ԃŏ�������
    Write(&jsonDoc);
    SAFE_DELETE(json);
}
/// <summary>
/// �ЂƂO�̏�Ԃɖ߂��邩
/// </summary>
/// <param name="prevNum">�߂肽���ꏊ</param>
/// <returns>�߂�邩�ǂ���</returns>
bool EditLog::CanBackPrevState(int prevNum) const
{
    auto json = new JsonFileLoader(fileName , schemaStr);
    if (json->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
    {
        const rapidjson::Value& list = json->GetLoadArray(ARRANGEDATA_MEMBER);
        //�k��Ȃ��Ȃ�false
        return prevNum < list.Size();
    }
    return false;
}
/// <summary>
/// �ĕҏW�̎���Log�𔽉f�������Ƃ��L�^�����ւ���
/// </summary>
/// <param name="prevNum">����ւ���</param>
/// <param name="editData">����ւ��O�̃f�[�^</param>
/// <param name="placeData">����ւ���̃f�[�^</param>
void EditLog::UpdateReEditData(int prevNum,EditData editData, PlacementData placeData)
{
    //�ĕҏW�̏��Ɠ���ւ������Ƃ��̂�
    if (editData.editAction != EditActionKind::reEdit)return;

    auto json = new JsonFileLoader(fileName, schemaStr);
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    //�ǂݍ��񂾓��e�����n
    rapidjson::Value myArray(rapidjson::kArrayType);
    json->MoveValue(myArray, ARRANGEDATA_MEMBER);
    //�ĕҏW�����ꍇ�A�O�ɖ߂������ɖ߂����肵���ꍇ�A����ւ���
    if (!myArray.Empty())
    {
        prevNum = myArray.Size() - prevNum - 1;   
        myArray[prevNum].FindMember(OBJNUM_MEMBER)->value = placeData.objKind;
        myArray[prevNum].FindMember(COLLECTNUM_MEMBER)->value = placeData.collectNum;
        myArray[prevNum].FindMember(POSX_MEMBER)->value = placeData.posX;
        myArray[prevNum].FindMember(POSZ_MEMBER)->value = placeData.posZ;
        myArray[prevNum].FindMember(DIRX_MEMBER)->value = placeData.dirX;
        myArray[prevNum].FindMember(DIRZ_MEMBER)->value = placeData.dirZ;
    }
    //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);

    //�t�@�C���̒��g��S����������Ԃŏ�������
    Write(&jsonDoc);
    SAFE_DELETE(json);
}
/// <summary>
/// �ЂƂO�ɕҏW�������̂̏���n��
/// </summary>
/// <param name="prevNum">�߂肽���i�K�� 0�Ȃ��ԍŌ�̃��O�������@���̐��͂Ȃ�</param>
/// <returns></returns>
EditLog::EditData EditLog::GetPrevEditData(int prevNum)
{
    auto json = new JsonFileLoader(fileName, schemaStr);//���O�������̂ڂ�
    auto& list = json->GetLoadArray(ARRANGEDATA_MEMBER);
    auto arrayValue = list.End() - prevNum - 1;

    //���O�Ɏc�����I�u�W�F�N�g�̏��
    EditData editPlaceData;
    editPlaceData.data.ConversionJsonToPlacementData(arrayValue);
    editPlaceData.editNum = arrayValue->FindMember(EDIT_MEMBER)->value.GetInt();
    //�ҏW�̑��ʂ��ЂƂO�Ɣ�r
    int editNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();
    //�ЂƂO�̕ҏW�����@�����l��New�������̏����ҏW����
    int prevTotalNum = firstTotalNum;
    //���X�g�̐擪����Ȃ��Ȃ�ҏW����������
    if (arrayValue != list.Begin())
    {
        arrayValue--;
        prevTotalNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();
    }
    editPlaceData.editAction = EditActionKind::addData;//�V�K�쐬���ꂽ�f�[�^������
    if (editNum == prevTotalNum)//�ĕҏW�O�̏�������
    {
        editPlaceData.editAction = EditActionKind::reEdit;
        editPlaceData.data.ConversionJsonToPlacementData(arrayValue);
    }
    else if (editNum < prevTotalNum)//�폜���ꂽ�f�[�^������
    {
        editPlaceData.editAction = EditActionKind::deleteData;
    }
    SAFE_DELETE(json);
    return editPlaceData;
}
/// <summary>
/// �ЂƂO�̏�Ԃ̂Ƃ��Ɉ��̏�Ԃɖ߂�
/// </summary>
/// <param name="prevNum">�߂肽���i�K�� 0�Ȃ��ԍŌ�̃��O�������@���̐��͂Ȃ�</param>
/// <returns></returns>
EditLog::EditData EditLog::GetStepEditData(int prevNum)
{
    auto json = new JsonFileLoader(fileName, schemaStr);//���O�������̂ڂ�
    auto& list = json->GetLoadArray(ARRANGEDATA_MEMBER);
    auto arrayValue = list.End() - prevNum - 1;
    //���O�Ɏc�����I�u�W�F�N�g�̏��
    EditData editPlaceData;
    editPlaceData.data.ConversionJsonToPlacementData(arrayValue);
    editPlaceData.editNum = arrayValue->FindMember(EDIT_MEMBER)->value.GetInt();
    //�ҏW�̑��ʂ��ЂƂ�Ɣ�r
    int editNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();    
    //������̕ҏW����
    int destinationTotalNum = firstTotalNum;
    //���X�g�̐擪����Ȃ��Ȃ�ҏW����������
    if (arrayValue != list.Begin())
    {
        arrayValue--;
        destinationTotalNum = arrayValue->FindMember(TOTALNUM_MEMBER)->value.GetInt();
    }
    editPlaceData.editAction = EditActionKind::deleteData;//���Ȃ��Ȃ�폜�������̂̏�������

    //��̃f�[�^�̕��������Ȃ�ǉ��������̂̏�������
    if (editNum > destinationTotalNum)
    {
        editPlaceData.editAction = EditActionKind::addData;
    }
    else if (editNum == destinationTotalNum)//�����Ȃ�ĕҏW��̏�������
    {
        editPlaceData.editAction = EditActionKind::reEdit;
    }
    SAFE_DELETE(json);
    return editPlaceData;
}
/// <summary>
/// �ۑ����邽�߂�Json��Value�ɓo�^���ĕԂ�
/// </summary>
/// <param name="totalEdit">�ҏW����</param>
/// <param name="editNum">�ҏW�z��ԍ�</param>
/// <param name="editData">�ҏW���</param>
/// <param name="allocator">Json�̃A���P�[�^�[</param>
/// <returns></returns>
rapidjson::Value EditLog::GetEditPlaceData(int totalEdit, int editNum, PlacementData editData, rapidjson::Document::AllocatorType& allocator) const
{
    //�ҏW���e�������o�ɓo�^
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember(TOTALNUM_MEMBER, totalEdit, allocator);
    objValue.AddMember(EDIT_MEMBER, editNum, allocator);
    editData.SetEditPlaceData(objValue,allocator);
    return objValue;
}  