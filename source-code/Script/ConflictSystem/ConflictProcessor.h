#pragma once
#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>
struct CollisionResultInfo;
struct HitCheckInfo;
class Actor;
class SphereHitChecker;
/// <summary>
/// �Փˏ������s��
/// </summary>
class  ConflictProcessor
{
public:
    /// <summary>
    /// �Փˏ������s��
    /// </summary>
    /// <param name="obj">���s�������Փˏ���������I�u�W�F�N�g</param>
    ConflictProcessor(std::shared_ptr<Actor> obj);
    /// <summary>
    /// ���s��̃I�u�W�F�N�g�����Z�b�g
    /// </summary>
    virtual ~ConflictProcessor();
    /// <summary>
    /// �����蔻��̏������Ăяo��
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void OnConflict(CollisionResultInfo resultInfo);
    /// <summary>
    /// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;
    /// <summary>
    /// �Փˏ������s���I�u�W�F�N�g���������Ȃ��Ȃ�
    /// </summary>
    /// <returns>�������Ȃ��Ȃ�True</returns>
    bool IsDead();
protected:
    ConflictProcessor() {};
    /// <summary>
    /// �����蔻��̎�����
    /// </summary>
    std::shared_ptr<Actor> object = nullptr;
};