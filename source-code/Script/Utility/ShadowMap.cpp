#include "ShadowMap.h"
#include "ObjectObserver.h"

/// <summary>
/// �v���C���[�𒆐S�ɉe��`��ł���悤�ɂ���
/// </summary>
/// <param name="player">�v���C���[�̈ʒu��`����N���X</param>
ShadowMap::ShadowMap(std::weak_ptr <ObjectObserver> player)
{
    //�����̌���
    SetShadowMapLightDirection(shadowMap, VGet(0.1f, -1, 0));
    SetShadowMapDrawArea(shadowMap, DrawAreaMinPos, DrawAreaMaxPos);
    playerObserber = player;
}
/// <summary>
/// �v���C���[�̃I�u�U�[�o�[�̃��Z�b�g�ƃV���h�E�}�b�v�̍폜
/// </summary>
ShadowMap::~ShadowMap()
{
    playerObserber.reset();
    DeleteShadowMap(shadowMap);
}
/// <summary>
/// �e�̕`��͈͂̕ύX
/// </summary>
void ShadowMap::SetShadowMapArea()
{
    VECTOR targetPos = playerObserber.lock()->GetSubjectPos();
    VECTOR minPos = VAdd(targetPos, DrawAreaMinPos);
    VECTOR maxPos = VAdd(targetPos, DrawAreaMaxPos);
    SetShadowMapDrawArea(shadowMap, minPos, maxPos);
}
/// <summary>
/// ���ꂩ��`�悷��e�̏���
/// </summary>
void ShadowMap::SetUpDrawShadow()
{
    ShadowMap_DrawSetup(shadowMap);
}
/// <summary>
/// �e��`�悷��̏I��
/// </summary>
void ShadowMap::EndDrawShadow()
{
    //�V���h�E�}�b�v�ւ̕`����I��
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowMap);
}
/// <summary>
/// �������񂾃V���h�E�}�b�v���g��
/// </summary>
void ShadowMap::Use()
{
    SetUseShadowMap(0, -1);
}