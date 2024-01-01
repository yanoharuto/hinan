#pragma once
#include "Actor.h"
#include "WallCollider.h"
#include <string>
/// <summary>
/// �s���͈͂����߂��
/// </summary>
class StageWall : public Actor
{
public:
    /// <summary>
    /// �s���͈͂����߂��
    /// </summary>
    StageWall();
    ~StageWall() {};
private:
    //�t����΂���
    const float setBouncePower = 50;
    //�}�b�v�̒[�P
    const VECTOR stageBiggestSize = { 2850,0,3150 };
    //�}�b�v�̒[2
    const VECTOR stageSmallestSize = { -3150,0,-2850 } ;
};