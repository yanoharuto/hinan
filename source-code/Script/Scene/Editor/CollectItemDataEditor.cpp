#include "CollectItemDataEditor.h"
#include "EditorObject.h"
#include "UserInput.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "CameraObserver.h"
//読み込む配置情報の書いてあるファイルのパス
const std::string CollectItemDataEditor::loadFileName = "collectData";
/// <summary>
/// 収集アイテムの編集するクラス
/// </summary>
CollectItemDataEditor::CollectItemDataEditor()
    :StageDataEditor(loadFileName,InitObjKind::collect)
{
}
/// <summary>
/// 親クラスと同じ更新と収集アイテムの数を更新する
/// </summary>
void CollectItemDataEditor::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    //親クラスと同じ更新
    StageDataEditor::Update(cameraObserever);


}
/// <summary>
/// 編集中や編集し終えたオブジェクトの描画
/// </summary>
void CollectItemDataEditor::Draw() const
{
    StageDataEditor::Draw();
    
    //収集アイテムの数
    DrawString(0, drawCollectNumY, std::to_string(collectNum).c_str(), GetColor(0, 0, 0));
    //ミッションの数
    DrawString(0, drawEditedCollectNumY, std::to_string(getCollectNum).c_str(), GetColor(0, 0, 0));
}
 