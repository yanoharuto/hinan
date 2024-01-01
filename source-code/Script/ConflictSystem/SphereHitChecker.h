#pragma once
#include "Object.h"
#include <iostream>
#include <memory>
struct HitCheckInfo;
struct CollisionResultInfo;
class Actor;
/// <summary>
/// �����m�̓����蔻������܂�
/// </summary>
class SphereHitChecker
{
public:
    /// <summary>
    /// �����m�̓����蔻����s��
    /// </summary>
    /// <param name="obj">�����蔻��̎�����</param>
    SphereHitChecker(std::shared_ptr<Actor> obj);
    ~SphereHitChecker() {};
    /// <summary>
    /// �������Ă��邩���א�����ԕ����Ƃ���Ԃ�
    /// </summary>
    /// <param name="hitCheckInfo">�������Ă��邩���ׂ��������蔻��</param>
    /// <returns>�������Ă���Փˌ��ʂ�Ԃ�</returns>
    virtual CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo);
    /// <summary>
    /// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
    /// </summary>
    /// <returns>�����蔻��ŕK�v�ȏ��</returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;
    /// <summary>
    /// true�Ȃ瓖���蔻�薳��
    /// </summary>
    /// <returns>�����蔻��̎����傪�����Ă��Ȃ��Ȃ�True</returns>
    bool IsDead();
protected:
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objAInfo">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(const HitCheckInfo objAInfo, const HitCheckInfo objBInfo);

protected:
    /// <summary>
    /// �����������ǂ������ׂ�Ƃ��̋��ʏ���
    /// </summary>
    /// <param name="objAInfo">���ׂ����I�u�W�F�N�gA</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheckProcess(HitCheckInfo objAInfo, HitCheckInfo objBInfo);

    //�����蔻��̎�����
    std::shared_ptr<Actor> object = nullptr;
};