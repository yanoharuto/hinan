#pragma once
#include "AddableObjectController.h"
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
/// </summary>
class MoveSawController : public AddableObjectController
{
public:
    /// <summary>
    /// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚ÌŠÇ—Ò
    /// </summary>
    MoveSawController();
    /// <summary>
    /// ‰ñ“]‚Ì‚±‚¬‚è‚ğˆÚ“®‚³‚¹‚é@”j‰ó‚³‚ê‚½‚ç”jŠü
    /// </summary>
    void Update()override;
protected:
    /// <summary>
    /// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è‚Ì’Ç‰Á
    /// </summary>
    /// <param name="editData">ˆÊ’u‚âŒü‚«</param>
    void AddObject(PlacementData editData)override;
};

