#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectSubject;
class ObjectObserver;
class SphereHitChecker;
class ConflictProccesor;
/// <summary>
/// ���e�̊Ǘ��N���X
/// </summary>
class BomberController : public DamageObjectController
{
public:
    /// <summary>
    /// ���e�̊Ǘ��N���X
    /// </summary>
    BomberController();
    /// <summary>
    /// ���e���X�V�ł���悤�ɂ���
    /// </summary>
    /// <param name="sub">���e�𓊉������I�u�W�F�N�g</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
    /// <summary>
    /// ���e�̍X�V
    /// </summary>
    void Update()override;
private:
};