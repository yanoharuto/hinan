#include "CollectItemObserver.h"
#include "CollectController.h"
/// <summary>
/// �Ǘ��N���X������
/// </summary>
/// <param name="collectItemController">���W�A�C�e���̊Ǘ��N���X</param>
CollectItemObserver::CollectItemObserver(std::shared_ptr<CollectItemController>& collectItemController)
{
	collectController = collectItemController;
}
/// <summary>
/// �Ǘ��N���X���J��
/// </summary>
CollectItemObserver::~CollectItemObserver()
{
	collectController.reset();
}
/// <summary>
/// �ŏ��ɃX�e�[�W�ɔz�u����閇��
/// </summary>
/// <returns>�X�e�[�W�ɔz�u���ꂽ�ő吔</returns>
int CollectItemObserver::GetTotalItemNum() const
{
	return collectController->GetTotalNum();
}
/// <summary>
/// �����Ǝ��W�A�C�e���̋���
/// </summary>
/// <param name="pos">���W�A�C�e���Ƃ̋����𒲂ׂ����ʒu</param>
/// <returns>�����Ǝ��W�A�C�e���̋����x�N�g��</returns>
VECTOR CollectItemObserver::GetItemBetween(VECTOR pos) const
{
	return collectController->GetItemBetween(pos);
}
/// <summary>
/// �A�C�e���̎c�薇��
/// </summary>
/// <returns>�v���C���[�Ɏ����ƌ���</returns>
int CollectItemObserver::GetRemainingItemNum() const
{
	return  collectController->GetRemainingNum();
}
/// <summary>
/// ���̎��W�A�C�e�������Ԗڂ̃A�C�e����
/// </summary>
/// <returns>�v���C���[�Ɏ����Ƒ�����</returns>
int CollectItemObserver::GetCollectCount() const
{
	return collectController->GetCollectCount();
}
/// <summary>
/// �Ō�̈�̃A�C�e����������ꂽ��
/// </summary>
/// <returns>������ꂽ��True</returns>
bool CollectItemObserver::IsCollectLastOne() const
{
	return collectController->IsCollectLastOne();
}
