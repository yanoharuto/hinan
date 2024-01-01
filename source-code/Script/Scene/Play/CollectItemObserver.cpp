#include "CollectItemObserver.h"
#include "CollectController.h"
/// <summary>
/// 管理クラスを所得
/// </summary>
/// <param name="collectItemController">収集アイテムの管理クラス</param>
CollectItemObserver::CollectItemObserver(std::shared_ptr<CollectItemController>& collectItemController)
{
	collectController = collectItemController;
}
/// <summary>
/// 管理クラスを開放
/// </summary>
CollectItemObserver::~CollectItemObserver()
{
	collectController.reset();
}
/// <summary>
/// 最初にステージに配置される枚数
/// </summary>
/// <returns>ステージに配置された最大数</returns>
int CollectItemObserver::GetTotalItemNum() const
{
	return collectController->GetTotalNum();
}
/// <summary>
/// 引数と収集アイテムの距離
/// </summary>
/// <param name="pos">収集アイテムとの距離を調べたい位置</param>
/// <returns>引数と収集アイテムの距離ベクトル</returns>
VECTOR CollectItemObserver::GetItemBetween(VECTOR pos) const
{
	return collectController->GetItemBetween(pos);
}
/// <summary>
/// アイテムの残り枚数
/// </summary>
/// <returns>プレイヤーに取られると減る</returns>
int CollectItemObserver::GetRemainingItemNum() const
{
	return  collectController->GetRemainingNum();
}
/// <summary>
/// 今の収集アイテムが何番目のアイテムか
/// </summary>
/// <returns>プレイヤーに取られると増える</returns>
int CollectItemObserver::GetCollectCount() const
{
	return collectController->GetCollectCount();
}
/// <summary>
/// 最後の一つのアイテムが回収されたか
/// </summary>
/// <returns>回収されたらTrue</returns>
bool CollectItemObserver::IsCollectLastOne() const
{
	return collectController->IsCollectLastOne();
}
