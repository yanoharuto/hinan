#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include <iostream>
class ConflictProcessor;
class SphereHitChecker;
struct CollisionResultInfo;
/// <summary>
///  �����蔻���Z�߂čs�����߂̓z
/// </summary>
class ConflictManager
{
public:
    /// <summary>
    /// �����蔻���Z�߂čs�����߂̓z
    /// </summary>
    ConflictManager();
    /// <summary>
    /// �����蔻��o�^Map�S����
    /// </summary>
    ~ConflictManager();
    /// <summary>
    /// �����蔻��ǉ�
    /// </summary>
    /// <param name="hitChecker">�����蔻��</param>
    static void AddHitChecker(std::shared_ptr<SphereHitChecker>& hitChecker);
    static void AddConflictProcessor(std::unique_ptr<ConflictProcessor>& conflictProcessor,std::shared_ptr<SphereHitChecker>& hitChecker);
    /// <summary>
    /// �f�o�b�O�p�����o��
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// �����Փ˂��Ă��镨���Ȃ������ׂ�
    /// </summary>
    void Update();
private:
    void Conflict(int i, std::shared_ptr<SphereHitChecker>& hitChecker);
    //�����������ʂ𔽉f������N���X�̃}�b�v
    static std::vector<std::pair<std::unique_ptr<ConflictProcessor>, std::shared_ptr<SphereHitChecker>>> processorKeyMap;
    //�������Ă��邩���ׂ�N���X�̃��X�g
    static std::vector<std::shared_ptr<SphereHitChecker>> hitCheckList;
};