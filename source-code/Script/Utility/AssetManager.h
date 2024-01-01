#pragma once
#include <vector>
#include <string>
#include <unordered_map>
class JsonFileLoader;
/// <summary>
/// アセットまでのパスを共有できるように親クラスに渡す
/// </summary>
class AssetManager abstract
{
public:
    enum class AssetList;
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    AssetManager();
    virtual ~AssetManager() {};

    enum class AssetList
    {
        camera,//カメラ
        effect,//エフェクト
        object,//オブジェクト
        ui,//UI
        sound,//音
        stageData,//ステージの初期位置や制限時間
        objectAddData//オブジェクトの追加情報
    };
    /// <summary>
    /// 引数のファイルが存在するか調べる
    /// </summary>
    /// <param name="fileName"></param>
    /// <returns>存在するならtrue</returns>
    static bool IsExistFile(std::string fileName);
    /// <summary>
    /// jsonFileで読み取れそうか調べる
    /// </summary>
    /// <returns>調べれそうならtrue</returns>
    static bool IsExistJsonFile();
protected:
    /// <summary>
    /// 初期化で使うCSVファイルのパスを所得
    /// </summary>
    /// <param name="fileKind">欲しいファイルの種類</param>
    /// <returns>初期化で使うCSVファイルのパス</returns>
   static std::string GetInitCsvFilePath(AssetList fileKind);
   /// <summary>
   /// 初期化で使うJsonファイルのパスを所得
   /// </summary>
   /// <param name="fileKind">欲しいファイルの種類</param>
   /// <returns>初期化で使うJsonファイルのパス</returns>
   static std::string GetInitJsonFilePath(AssetList fileKind);
   /// <summary>
   /// asset一覧をVectorに移していく
   /// </summary>
   /// <param name="listKind">読み取りたいファイルの種類</param>
   static std::vector<std::string> GetAssetList(AssetList listKind);
   //csvファイルまでのパス
   static std::string const initCSVFilePath;
   //jsonファイルまでのパス
   static std::string const initJSONFilePath;
private:
    //asset一覧で使うスキーマのパス
    static const std::string listSchemaPath;
    //Jsonファイルがあるか調べるのに使う
    static const std::string jsonExistFile;
    //初期化ファイルの名前
    static std::string const initFileNames[];
};