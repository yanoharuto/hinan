#pragma once
#include "JsonWriter.h"
#include "EditObjectData.h"
#include <vector>
constexpr char TOTALNUM_MEMBER[] = "totalEdit";
constexpr char EDIT_MEMBER[] = "editNum";
/// <summary>
/// 編集したものを元に戻せるように記録する
/// </summary>
class EditLog :public JsonWriter
{
public:
    /// <summary>
    /// 編集するファイルの名前と編集総数を保存　
    /// </summary>
    /// <param name="logFileName">ファイルの名前</param>
    /// <param name="firstTotalEditNum">編集総数</param>
    EditLog(std::string logFileName,int firstTotalEditNum);

    ~EditLog() {};
    /// <summary>
    /// placeDataを後ろからprevNum番目に追加
    /// </summary>
    /// <param name="prevNum">戻りたい場所</param>
    /// <param name="totalEdit">保存したいオブジェクトの総数</param>
    /// <param name="nowEditNum">編集番号</param>
    /// <param name="placeData">保存したい情報</param>
    void SaveEditDataLog(int prevNum,int totalEdit,int nowEditNum, PlacementData placeData);
    
    /// <summary>
    /// ひとつ前の状態に戻せるか
    /// </summary>
    /// <returns></returns>
    bool CanBackPrevState(int prevNum)const;
    /// <summary>
    /// 編集内容
    /// </summary>
    enum class EditActionKind
    {
        deleteData,//削除
        reEdit,//再編集
        addData//追加
    };
    /// <summary>
    /// 編集内容
    /// </summary>
    struct EditData
    {
        EditActionKind editAction;//編集内容
        PlacementData data;//配置情報
        int editNum;//編集番号
    };
    /// <summary>
    /// 再編集の時のLogを反映させたとき記録を入れ替える
    /// </summary>
    /// <param name="prevNum">入れ替え先</param>
    /// <param name="editData">入れ替え前のデータ</param>
    /// <param name="placeData">入れ替え後のデータ</param>
    void UpdateReEditData(int prevNum, EditData editData, PlacementData placeData);
    /// <summary>
    /// ひとつ前に編集したものの情報を渡す
    /// </summary>
    /// <param name="prevNum">戻りたい段階数 0なら一番最後のログを所得　負の数はない</param>
    /// <returns></returns>
    EditLog::EditData GetPrevEditData(int prevNum);
    /// <summary>
    /// ひとつ前の状態のときに一つ先の状態に戻す
    /// </summary>
    /// <param name="prevNum">戻りたい段階数 0なら一番最後のログを所得　負の数はない</param>
    /// <returns></returns>
    EditLog::EditData GetStepEditData(int prevNum);
private:
    /// <summary>
    /// 保存するためにJsonのValueに登録して返す
    /// </summary>
    /// <param name="totalEdit">編集総数</param>
    /// <param name="editNum">編集配列番号</param>
    /// <param name="editData">編集情報</param>
    /// <param name="allocator">Jsonのアロケーター</param>
    /// <returns></returns>
    rapidjson::Value GetEditPlaceData(int totalEdit,int editNum,PlacementData editData, rapidjson::Document::AllocatorType& allocator)const;
    //スキーマのパス
    const std::string schemaStr = "editLogData.json";

    int firstTotalNum = 0;
};