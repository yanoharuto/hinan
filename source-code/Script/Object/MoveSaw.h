#pragma once
#include "Saw.h"
#include "EditObjectData.h"
class ReusableTimer;
class SphereHitChecker;
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è
/// </summary>
class MoveSaw : public Saw
{
public:
    /// <summary>
    /// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è
    /// </summary>
    MoveSaw(PlacementData editData);
    /// <summary>
    /// ˆÚ“®‚µ‚È‚ª‚ç‰ñ“]‚·‚é
    /// </summary>
    void Update()override;
private:
    enum class MoveParametor
    {
        //ˆÚ“®‘¬“x
        moveSpeed ,
        //ˆÚ“®ŽžŠÔ
        moveTime
    };
    //ˆÚ“®ŽžŠÔ
    std::unique_ptr<ReusableTimer> moveLarpTimer;
};

