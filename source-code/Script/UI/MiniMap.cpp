#include "MiniMap.h"
#include "UIManager.h"
#include "OriginalMath.h"
#include "Object.h"
#include "Utility.h"
#include "UIDrawer.h"
#include "StageWall.h"
//���@��Icon�̑傫��
const int MiniMap::iconSize;
//�~�j�}�b�v�ɕ\������_
std::list<std::unique_ptr<ObjectObserver>> MiniMap::markerObserverList;
//�~�j�}�b�v�̃f�[�^
UIData MiniMap::miniMapUIData;
/// <summary>
/// ���W�A�C�e���Ƃ���`�悷�邽�߂̓z
/// </summary>
MiniMap::MiniMap(std::weak_ptr<ObjectObserver> player)
{
    //UI�ǂݍ���
    miniMapUIData = UIManager::CreateUIData(UIInit::UIKind::radar);
    //�~�j�}�b�v�̏c��
    int mapGraphLength;
    GetGraphSize(miniMapUIData.dataHandle[0], &mapGraphWidth, &mapGraphLength);
    
    playerObserver = player;
    betweenSize = mapGraphWidth / 6000 * betweenSize;
}
/// <summary>
/// �`�悷��}�[�J�[������
/// </summary>
MiniMap::~MiniMap()
{
    //�`�悷�郊�X�g��S����
    for (auto itr = markerObserverList.begin(); itr != markerObserverList.end(); itr++)
    {
        (*itr).reset();
    }
    markerObserverList.clear();
    UIManager::DeleteUIGraph(&miniMapUIData);
}
/// <summary>
/// ���W�A�C�e���̈ʒu���X�V
/// </summary>
/// <param name="objInfo"></param>
void MiniMap::Update()
{
    //��x�S����
    drawPosList.clear();
    //���ꂩ��UpdateDrawPosList�Œǉ����ꂽ���̂���map�ɔ��f����
    for (auto ite = markerObserverList.begin(); ite != markerObserverList.end(); ite++)
    {
        //�A�N�e�B�u�ȃI�u�W�F�N�g�Ȃ�
        if ((*ite)->GetSubjectState() == Object::ObjectState::active)
        {
            VECTOR itePos = (*ite)->GetSubjectPos();
            //DrawPosList�ɃI�u�W�F�N�g�̈ʒu��ǉ����Ă���
            UpdateDrawPosList(itePos);
        }
    }
    //�k�̈ʒu��map�ɔ��f
    northPos = VGet(mapGraphWidth / 2 * miniMapUIData.size / betweenSize, 0, 0);
    northPos = ConvertPosition(northPos);
}
/// <summary>
/// �}�b�v�ɕ\������_�ƃ��[�_�[�̘g
/// </summary>
void MiniMap::Draw()const
{
    //�g�`��
    UIDrawer::DrawRotaUI(miniMapUIData);
    //�v���C���[�A�C�R���̕`��
    DrawCircle(miniMapUIData.x, miniMapUIData.y, iconSize, playerColor, 1, 1);
    //���W�A�C�e���̕`��
    for (auto ite = drawPosList.begin(); ite != drawPosList.end(); ite++)
    {
        DrawCircle(static_cast<int>((*ite).x), static_cast<int>((*ite).y), iconSize, coinColor, 1, 1);
    }
    //�k�̈ʒu��map�ɔ��f
    DrawCircle(static_cast<int>(northPos.x), static_cast<int>(northPos.y), iconSize, northColor, 1, 1);
}
/// <summary>
/// �}�b�v�ɔ��f���������A�C�e���̒ǉ�
/// </summary>
/// <param name="obserber"></param>
void MiniMap::AddMarker(std::unique_ptr<ObjectObserver> obserber)
{
    markerObserverList.push_back(std::move(obserber));
}
/// <summary>
/// �~�j�}�b�v�̑傫���ɕϊ�����
/// </summary>
/// <param name="between">�����̃A�C�e������̋���</param>
/// <returns></returns>
VECTOR MiniMap::ConvertPosition(VECTOR between)
{
    VECTOR playerDir = playerObserver.lock()->GetSubjectDir();
    //�}�b�v�̒������̌����ƃ}�[�J�[�̈ʒu�̊p�x��
    float rotate = OriginalMath::GetDegreeMisalignment(between, playerDir);
    //�E����������
    rotate = VCross(between, playerDir).y < 0 ? -rotate : rotate ;
    //�p�x���Ȃ����Ă���s��ŋ������Ȃ���
    MATRIX pM = MGetRotY(-rotate * RAGE);
    between = VTransform(VGet(0, 0, -VSize(between)), pM);
    //�~�j�}�b�v�̑傫���ɕϊ�
    VECTOR convertPos;
    convertPos.x = -between.x * betweenSize + miniMapUIData.x;
    convertPos.y = between.z * betweenSize + miniMapUIData.y;
    return convertPos;
}
/// <summary>
/// �`�悷��}�[�J�[�̃|�W�V����
/// </summary>
/// <param name="subjectPos">���������}�[�J�[�̃I�u�W�F�N�g�̃|�W�V����</param>
void MiniMap::UpdateDrawPosList(VECTOR subjectPos)
{
    //�v���C���[���}�b�v�̒��S�ɂȂ�悤�ɂ���
    VECTOR playerPos = playerObserver.lock()->GetSubjectPos();
    playerPos.y = 0;
    //�����܂ł̃v���C���[�̋����x�N�g��
    VECTOR distance = VSub(subjectPos, playerPos);
    distance.y = 0;
    //�������}�b�v�ɔ��f�\�ȑ傫���Ȃ�
    if (VSize(distance) * betweenSize < mapGraphWidth / 2)
    {
        distance = ConvertPosition(distance);

        drawPosList.push_back(distance);
    }
}