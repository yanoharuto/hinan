#include <iostream>
#include <cassert>
#include <vector>
#include "EditLog.h"
#include "Utility.h"
#include "writer.h"
#include "JsonFileLoader.h"
EditLog::EditLog(std::string logFileName)
{
    fileName = logFileName;
}
/// <summary>
/// placeData����납��prevNum�Ԗڂɒǉ�
/// </summary>
/// <param name="prevNum">�߂肽���ꏊ</param>
/// <param name="totalEdit">�ۑ��������I�u�W�F�N�g�̑���</param>
/// <param name="nowEditNum">�ҏW�ԍ�</param>
/// <param name="placeData">�ۑ����������</param>
void EditLog::SaveEditDataLog(int prevNum, int totalEdit,int nowEditNum, PlacementData placeData)
{
    auto json = new JsonFileLoader(fileName+Utility::JSON_FILE,schemaStr);
    if (json->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
    {
        //�h�L�������g�쐬
        rapidjson::Document jsonDoc;
        jsonDoc.SetObject();
        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
        rapidjson::Value myArray(rapidjson::kArrayType);
        const rapidjson::Value& list = json->GetLoadArray("arrangeData");
        
        //�ߋ��̃��O���ēx��������
        for (auto array = list.Begin(); array != list.End(); array++)
        {
            myArray.PushBack(GetEditPlaceData(array,allocator), allocator);
        }
        myArray.PushBack(GetEditPlaceData(totalEdit, nowEditNum, placeData, allocator), allocator);

        //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
        jsonDoc.AddMember("arrangeData", myArray, allocator);
        
        //�t�@�C���̒��g��S����������Ԃŏ�������
        std::ofstream ofs(fileName + Utility::JSON_FILE);
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        jsonDoc.Accept(writer);
        SAFE_DELETE(json);
    }
}
/// <summary>
/// �ЂƂO�̏�Ԃɖ߂��邩
/// </summary>
/// <returns></returns>
bool EditLog::CanBackPrevState(int prevNum) const
{
    auto json = new JsonFileLoader(fileName + Utility::JSON_FILE, schemaStr);
    if (json->IsAccept())//�X�L�[�}�Ɠǂݍ��ރt�@�C���̃o���f�[�V�����`�F�b�N
    {
        //�h�L�������g�쐬
        rapidjson::Document jsonDoc;
        jsonDoc.SetObject();
        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
        const rapidjson::Value& list = json->GetLoadArray("arrangeData");
        auto alocator = list.End() - prevNum;
        
        //��ԍŏ��̏�ԂɂȂ��Ă��Ȃ���
        return alocator!=list.Begin();
    }
    return false;
}

/// <summary>
/// �ЂƂO�ɕҏW�������̂̏���n��
/// </summary>
/// <param name="prevNum"></param>
/// <returns></returns>
PlacementData EditLog::GetPrevEditData(int prevNum)
{
    auto json = new JsonFileLoader(fileName + Utility::JSON_FILE, schemaStr);
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    //�z��ɂ��ċl�ߍ���
    rapidjson::Value myArray(rapidjson::kArrayType);
    const rapidjson::Value& list = json->GetLoadArray("arrangeData");
    auto array = list.End();
    array -= prevNum;
    totalNum = array->FindMember("totalEdit")->value.GetInt();
    editNum = array->FindMember("editNum")->value.GetInt();
    PlacementData editPlaceData;
    editPlaceData.objKind = array->FindMember("objNum")->value.GetInt();
    editPlaceData.collectNum = array->FindMember("collectNum")->value.GetInt();
    editPlaceData.posX = array->FindMember("x")->value.GetFloat();
    editPlaceData.posZ = array->FindMember("z")->value.GetFloat();
    editPlaceData.dirX = array->FindMember("dirX")->value.GetFloat();
    editPlaceData.dirZ = array->FindMember("dirZ")->value.GetFloat();
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
    objValue.AddMember("totalEdit", totalEdit, allocator);
    objValue.AddMember("editNum", editNum, allocator);
    objValue.AddMember("objKind", editData.objKind, allocator);
    objValue.AddMember("collectNum", editData.collectNum, allocator);
    objValue.AddMember("x", editData.posX, allocator);
    objValue.AddMember("z", editData.posZ, allocator);
    objValue.AddMember("dirX", editData.dirX, allocator);
    objValue.AddMember("dirZ", editData.dirZ, allocator);
    return objValue;
}  
/// <summary>
/// ������邽�߂�Json��Value�ɓo�^���ĕԂ�
/// </summary>
/// <param name="editData">�ҏW���</param>
/// <param name="allocator">Json�̃A���P�[�^�[</param>
/// <returns></returns>
rapidjson::Value EditLog::GetEditPlaceData(const rapidjson::Value* editData, rapidjson::Document::AllocatorType& allocator) const
{
    //�ҏW���e�������o�ɓo�^
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember("totalEdit", editData->FindMember("totalEdit")->value.GetInt(), allocator);
    objValue.AddMember("editNum", editData->FindMember("editNum")->value.GetInt(), allocator);
    objValue.AddMember("objNum", editData->FindMember("objNum")->value.GetInt(), allocator);
    objValue.AddMember("collectNum", editData->FindMember("collectNum")->value.GetInt(), allocator);
    objValue.AddMember("x", editData->FindMember("x")->value.GetFloat(), allocator);
    objValue.AddMember("z", editData->FindMember("z")->value.GetFloat(), allocator);
    objValue.AddMember("dirX", editData->FindMember("dirX")->value.GetFloat(), allocator);
    objValue.AddMember("dirZ", editData->FindMember("dirZ")->value.GetFloat(), allocator);
    return objValue;
}
