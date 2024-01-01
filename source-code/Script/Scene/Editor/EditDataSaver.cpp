#include <iostream>
#include <cassert>
#include <vector>
#include "EditDataSaver.h"
#include "Utility.h"
#include "writer.h"
#include "StageDataEditor.h"

/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="limitTime">��������</param>
/// <param name="placeVector">�ҏW��������Z�߂�Vector</param>
void EditDataSaver::SaveEditData(std::string fileName, std::vector<PlacementData> placeVector)
{
    SaveEditDataForJSON(fileName,placeVector);
}

/// <summary>
/// �ҏW��������ۑ�����
/// </summary>
/// <param name="editData">�ҏW�������</param>
/// <param name="saveFileName">�ۑ�����t�@�C��</param>
void EditDataSaver::SaveEditDataForCSV(std::string fileName, std::vector<PlacementData> editData) const
{
    //�z�u�������W�A�C�e����ۑ�
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        std::ofstream writing_file;
        auto data = editData[i];
        // �t�@�C�����J����
        writing_file.open(fileName + Utility::CSV_FILE, std::ios::app);
        //��؂蕶��
        std::string colon = ",";
        //�I�u�W�F�N�g�̎�ނ�
        writing_file << std::to_string(data.objKind) + colon << std::endl;
        //���Ԗڂ̎��W�A�C�e���̎���
        writing_file << std::to_string(data.collectNum) + colon << std::endl;
        //�ʒu
        writing_file << std::to_string(data.posX) + colon << std::endl;
        writing_file << std::to_string(data.posZ) + colon << std::endl;
        //����
        writing_file << std::to_string(data.dirX) + colon << std::endl;
        writing_file << std::to_string(data.dirZ) + colon << std::endl;
        writing_file.close();
    }
}
/// <summary>
/// �����̕ҏW����Json�ɕۑ��ł���悤�ɂ���
/// </summary>
/// <param name="editData">�ҏW���</param>
/// <param name="allocator">�ҏW�̂��߂ɕK�v��allocator</param>
/// <returns>Json�ɕۑ��ł���悤�ɂ�������</returns>
rapidjson::Value EditDataSaver::GetEditPlaceData(PlacementData editData, rapidjson::Document::AllocatorType& allocator) const
{
    //�ҏW���e�������o�ɓo�^
    rapidjson::Value objValue;
    objValue.SetObject();
    objValue.AddMember(OBJNUM_MEMBER, editData.objKind, allocator);
    objValue.AddMember(COLLECTNUM_MEMBER, editData.collectNum, allocator);
    objValue.AddMember(POSX_MEMBER, editData.posX, allocator);
    objValue.AddMember(POSZ_MEMBER, editData.posZ, allocator);
    objValue.AddMember(DIRX_MEMBER, editData.dirX, allocator);
    objValue.AddMember(DIRZ_MEMBER, editData.dirZ, allocator);
    return objValue;
}
/// <summary>
/// Json�`���ŕۑ�����
/// </summary>
/// <param name="editData">�ҏW���������Z��</param>
/// <param name="saveFileName">�ۑ���̃t�@�C���̖��O</param>
void EditDataSaver::SaveEditDataForJSON(std::string fileName, std::vector<PlacementData> editData)const
{
    //�h�L�������g�쐬
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //json�ɏ������ޏ���
    //�z��ɂ��ċl�ߍ���
    rapidjson::Value myArray(rapidjson::kArrayType);
    //�z�u�������W�A�C�e����ۑ�
    for (int i = 0; i < CONTAINER_GET_SIZE(editData); i++)
    {
        rapidjson::Value objValue;
        objValue.SetObject();
        editData[i].SetEditPlaceData(objValue, allocator);
        myArray.PushBack(objValue,allocator);
    }
    //�ҏW���e��saveFileName�̃t�@�C���ɏ�������
    jsonDoc.AddMember(ARRANGEDATA_MEMBER, myArray, allocator);
    //�t�@�C���̒��g��S����������Ԃŏ�������
    std::ofstream ofs(fileName + Utility::JSON_FILE);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    jsonDoc.Accept(writer);
}