#include "CollectController.h"
#include "FirstPositionGetter.h"
#include "CollectItem.h"
#include "MiniMap.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "InitActor.h"
#include "DrawModel.h"
#include "Object.h"
/// <summary>
/// ���W�A�C�e����\��New���čő喇����ۑ�
/// </summary>
CollectItemController::CollectItemController()
    :ActorController(InitObjKind::collect)
{
    //�z�u��񏊓�
    auto positionGetter = std::make_unique<FirstPositionGetter>();
    auto editDataVec = positionGetter->GetPlaceData(InitObjKind::collect);
    SAFE_RESET(positionGetter);
    //�z�u���Ɋ�Â���New���Ă���
    for (int i = 0; i < CONTAINER_GET_SIZE(editDataVec); i++)
    {
        //���W�A�C�e���̈ʒu���R���X�g���N�^�ɗ^����
        auto newCoin = std::make_shared<CollectItem>(editDataVec[i]);
        //�����蔻���ǉ�
        std::shared_ptr<Actor> actor = newCoin;
        AddConflictManagement(actor);
        actorList.push_back(newCoin);  
        //�}�b�v�Ɉʒu��`���邽�߃I�u�U�[�o�[��n��
        auto observer = std::make_unique<ObjectObserver>(newCoin);
        MiniMap::AddMarker(std::move(observer));
    }
    //���W�A�C�e���ő�l
    totalCollectNum = CONTAINER_GET_SIZE(actorList);
    //�c��̐�
    remainingCollectNum = totalCollectNum;
    //���o�Ă��Ă�����W�A�C�e���̐�
    collectCount = 0;
    //�`���
    drawModel = std::make_unique<DrawModel>(InitObjKind::collect);
    //���̃A�C�e���̈ʒu
    nowActiveCollectItemPos = {};
    //�������Ă��邩�ǂ����̃t���O
    isCollectLastOne = false;
}
/// <summary>
/// actorList�̐擪�̎��W�A�C�e�������X�V
/// </summary>
void CollectItemController::Update()
{
    //�����Ȃ���ԂȂ�I��
    if (actorList.empty())return;
    //actorList�̐擪�̈����������
    auto objIte = actorList.begin();
    (*objIte)->Update();
    //�����ݓ����Ă���A�C�e���̏ꏊ���X�V
    nowActiveCollectItemPos = (*objIte)->GetPos();

    //����Ă��邯�ǃG�t�F�N�g���o���Ă���r���Ȃ猻�������ւ炷
    Object::ObjectState objState = (*objIte)->GetObjectState();
    //�v���C���[�ɂԂ����Ď��ꂽ�Ȃ�A�N�e�B�u�ȊO�̏�ԂɂȂ��Ă���
    if (objState == Object::ObjectState::dead)
    {
        //�c�萔��S�̂���1���炷
        remainingCollectNum = CONTAINER_GET_SIZE(actorList) - 1;
        //�󂵂Ă����悤�ɂ���
        auto brokenObj = (*objIte);
        //�����Ă���������������
        actorList.erase(objIte);
        SAFE_RESET(brokenObj);
        //���̃A�C�e���͉��Ԗڂ�
        collectCount = totalCollectNum - remainingCollectNum;
    }
    //�Ō�̈��������ꂽ��
    else if (objState == Object::ObjectState::activeEnd && static_cast<int>(actorList.size()) == 1)
    {
        isCollectLastOne = true;
    }
}
/// <summary>
/// ���W�A�C�e���̕`��
/// </summary>
void CollectItemController::Draw(std::weak_ptr<CameraObserver>& cameraObserever) const
{
    if (!actorList.empty())
    {
        auto drawItem = *(actorList.begin());
        drawModel->Draw(drawItem->GetPos(),drawItem->GetDir());
    }
}
/// <summary>
/// �Q�[�����n�܂�O�̏���
/// </summary>
void CollectItemController::PrepareGame()
{
    //�C�e���[�^�[
    auto objIte = actorList.begin();
     (*objIte)->PrepareGame();
    //�����ݓ����Ă���A�C�e���̏ꏊ���X�V
    nowActiveCollectItemPos = (*objIte)->GetPos();
}
/// <summary>
/// �����Ǝ��W�A�C�e���̋���
/// </summary>
/// <param name="pos">���W�A�C�e���Ƃ̋����𒲂ׂ����ʒu</param>
/// <returns>�����Ǝ��W�A�C�e���̋����x�N�g��</returns>
VECTOR CollectItemController::GetItemBetween(VECTOR pos)const
{
    return VSub(nowActiveCollectItemPos, pos);
}
/// <summary>
/// �ŏ��ɃX�e�[�W�ɔz�u����閇��
/// </summary>
/// <returns>�X�e�[�W�ɔz�u���ꂽ�ő吔</returns>
int CollectItemController::GetTotalNum()const
{
    return totalCollectNum;
}
/// <summary>
/// �A�C�e���̎c�薇��
/// </summary>
/// <returns>�v���C���[�Ɏ����ƌ���</returns>
int CollectItemController::GetRemainingNum()const
{
    return remainingCollectNum;
}
/// <summary>
/// ���̎��W�A�C�e�������Ԗڂ̃A�C�e����
/// </summary>
/// <returns>���ꂽ�瑝����</returns>
int CollectItemController::GetCollectCount()const
{
    return collectCount;
}
/// <summary>
/// �Ō�̈�̃A�C�e����������ꂽ��
/// </summary>
/// <returns>������ꂽ��True</returns>
bool CollectItemController::IsCollectLastOne()const
{
    return isCollectLastOne;
}