#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "InitObjKind.h"
#include "AssetManager.h"

namespace ObjectInit
{
    /// <summary>
    ///����������v�f
    /// </summary>
    enum class InitObjParamator
    {
        //model�̑��΃p�X
        assetPath = 0,
        //�傫��
        modelSize = 1,
        //�ŏ��̃|�W�V����
        firstPosY = 2,
        //model�̓����蔼�a
        collRadius = 3,
        //���˕Ԃ�̑傫��
        bouncePower = 4
    };
    /// <summary>
    /// �Q�[���L�����̏����ʒu�Ƃ������蔻��̑傫���Ƃ�
    /// </summary>
    struct ActorParameter
    {
        //�������x
        float firstPosY;
        //�����蔻��̑傫��
        float setRadius;
        //���˕Ԃ��
        float setBouncePow;
    };
}
class DrawModelManager;
using namespace ObjectInit;
/// <summary>
/// actor�̏�����������
/// </summary>
class InitActor final:public AssetManager
{
public:
    /// <summary>
    /// �S�Ă�actor�̏����������邽�߂̃p�X���������t�@�C����ǂݍ���
    /// </summary>
    InitActor();
    /// <summary>
    /// �`�惂�f���Ǘ��S���̉��
    /// </summary>
    ~InitActor();
    /// <summary>
    /// �������ɕK�v�ȏ�������
    /// </summary>
    /// <param name="obj">�������������I�u�W�F�N�g</param>
    /// <returns>�������ɕK�v�ȏ��</returns>
    static ActorParameter GetActorParamator(InitObjKind obj);
    /// <summary>
    /// �����̎�ނ̕`�惂�f���n���h����n��
    /// </summary>
    /// <param name="kind">���o�������`�惂�f��</param>
    /// <returns>�`�惂�f���n���h��</returns>
    static int GetModelHandle (InitObjKind obj);
private:
    /// <summary>
    /// �������������p�����[�^�𕶎���ŏ���
    /// </summary>
    /// <param name="obj">�������������I�u�W�F�N�g</param>
    /// <returns>�������������p�����[�^�̕�����</returns>
    static std::vector<std::string> GetActorParametorStrVec(InitObjKind obj);
    //initActorFileName�̐�̃t�@�C�����珊�������f�[�^���܂Ƃ߂�Vector
    static std::vector<std::string> objectInitDataPathVec;
    //initActorJsonFilePath��JsonSchema�̃p�X
    static std::string initActorSchemaPath; 
    //�������v�f��JsonSchema�̃p�X
    static std::string initObjParamatorSchemaPath; 
    //�`�惂�f���n���h��������
    static std::unique_ptr<DrawModelManager> drawModelManager;
};