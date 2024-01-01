#pragma once
#include "DxLib.h"
#include <math.h>
#include<random>
#define RAGE  static_cast<float>(DX_PI / 180.0f) //���W�A��

class OriginalMath
{
public:
    /// <summary>
    /// �������Ƒ������̊p�x�̂�����o��
    /// </summary>
    /// <param name="direction1"></param>
    /// <param name="direction2"></param>
    /// <returns>�f�O���[�ŕԂ�</returns>
    static float GetDegreeMisalignment(VECTOR direction1, VECTOR direction2)
    {
        float destinationDir = 0;
        destinationDir = VDot(direction1, direction2) / (VSize(direction2) * VSize(direction1));
        destinationDir = acosf(destinationDir) / RAGE;
        return destinationDir;
    }
    /// <summary>
    /// �����_���Ȓl��Ԃ�
    /// </summary>
    /// <param name="min">�Œ�l</param>
    /// <param name="max">�ő�l</param>
    /// <returns></returns>
    static int GetRandom(int min, int max)
    {
        std::random_device seed;
        std::mt19937 engine(seed());
        std::uniform_int_distribution<> dist{ min,max };
        return dist(engine);
    }
    /// <summary>
    /// �����̓x������y���ŋȂ������x�N�g����Ԃ�
    /// </summary>
    /// <param name="rotateVector">�Ȃ������x�N�g��</param>
    /// <param name="degree">�Ȃ������p�x</param>
    /// <returns>�Ȃ����x�N�g��</returns>
    static VECTOR GetYRotateVector(VECTOR rotateVector, float degree)
    {
        MATRIX pM = MGetRotY(degree * RAGE);
        rotateVector = VTransform(rotateVector, pM);
        return rotateVector;
    }
    /// <summary>
    /// �����̓x������x���ŋȂ������x�N�g����Ԃ�
    /// </summary>
    /// <param name="rotateVector">�Ȃ������x�N�g��</param>
    /// <param name="degree">�Ȃ������p�x</param>
    /// <returns>�Ȃ����x�N�g��</returns>
    static VECTOR GetXRotateVector(VECTOR rotateVector, float degree)
    {
        MATRIX pM = MGetRotX(degree * RAGE);
        rotateVector = VTransform(rotateVector, pM);
        return rotateVector;
    }
    /// <summary>
    /// �����̓x������z���ŋȂ������x�N�g����Ԃ�
    /// </summary>
    /// <param name="rotateVector">�Ȃ������x�N�g��</param>
    /// <param name="degree">�Ȃ������p�x</param>
    /// <returns>�Ȃ����x�N�g��</returns>
    static VECTOR GetZRotateVector(VECTOR rotateVector, float degree)
    {
        MATRIX pM = MGetRotZ(degree * RAGE);
        rotateVector = VTransform(rotateVector, pM);
        return rotateVector;
    }
    /// <summary>
    /// ������Ԃ�
    /// </summary>
    /// <param name="num"></param>
    /// <returns></returns>
    static int GetDigits(int num)
    {
        int digits = 1;
        while (num >= 10)
        {
            num /= 10;
            digits++;
        }
        return digits;
    }
};