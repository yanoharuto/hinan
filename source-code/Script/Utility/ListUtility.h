#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "DxLib.h"

/// <summary>
/// ���X�g���x�N�^�[�ɕϊ�����
/// </summary>
/// <typeparam name="T">���X�g�ɓ����Ă���N���X</typeparam>
/// <param name="list">�x�N�^�[�ɂ��������X�g</param>
/// <returns>���X�g���x�N�^�[�ɂ�������</returns>
template<typename T>
static std::vector<T> ConvertListToVector(std::list<T> list)
{
    std::vector<T> newList(list.begin(), list.end());
    return newList;
}
/// <summary>
/// �x�N�^�[���烊�X�g�ɂ���
/// </summary>
/// <typeparam name="T">�x�N�^�[�ɓ����Ă���N���X</typeparam>
/// <param name="vector">���X�g�ɂ������x�N�^�[</param>
/// <returns>�x�N�^�[�����X�g�ɂ�������</returns>
template<typename T>
static std::list<T> ConvertVectorToList(std::vector<T> vector)
{
    std::list<T> newVec(vector.begin(), vector.end());
    return newVec;
}
/// <summary>
///�@�x�N�^�[�̒��������̗v�f���C�e���[�^�[�ɂ��ēn��
/// </summary>
/// <typeparam name="T">�x�N�^�[�̒��Ŋi�[����Ă���N���X</typeparam>
/// <param name="vector">�T�������C�e���[�^�[�̂���x�N�^�[</param>
/// <param name="element">����̗v�f</param>
/// <returns>�x�N�^�[�̒��ɓ���̗v�f���Ȃ�������end()���Ԃ��Ă���</returns>
template<typename T>
static std::vector<T*>::iterator FindVector(std::vector<T*>* vector,T* element)
{
    for (auto itr = (*vector).begin(); itr != (*vector).end(); itr++)
    {
        if ((*itr) == element)//�T�������v�f������������C�e���[�^�[��Ԃ�
        {
            return itr;
        }
    }
    return (*vector).end();
}
/// <summary>
/// ���X�g�̒��������̗v�f���C�e���[�^�[�ɂ��ēn��
/// </summary>
/// <typeparam name="T">���X�g�̒��Ŋi�[����Ă���N���X</typeparam>
/// <param name="list">�T�������C�e���[�^�[�̂��郊�X�g</param>
/// <param name="element">����̗v�f</param>
/// <returns>���X�g�̒��ɓ���̗v�f���Ȃ�������end()���Ԃ��Ă���</returns>
template<typename T>
static std::list<T*>::iterator FindList(std::list<T*>* list, T* element)
{
    for (auto itr = (*list).begin(); itr != (*list).end(); itr++)
    {
        if ((*itr) == element)//�T�������v�f������������C�e���[�^�[��Ԃ�
        {
            return itr;
        }
    }
    return (*list).end();
}