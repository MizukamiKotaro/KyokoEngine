#pragma once
#include <string>
#include <list>
#include <memory>
class BaseStageObject;
class StageEditor;
class Camera;
enum class StageObjectType;
class DescriptorHandles;
/// <summary>
/// ライブステージのオブジェクトマネージャー
/// </summary>
class StageObjectManager {
public:
	/// <summary>
	/// タイプの追加
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="mainName">メインの名前</param>
	/// <param name="subName">サブの名前</param>
	void AddType(StageObjectType type, const std::string& mainName, const std::string& subName);
	/// <summary>
	/// クリア
	/// </summary>
	void Clear() { objects_.clear(); }
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	void Update(float deltaTime);
	/// <summary>
	/// 時間のセット
	/// </summary>
	/// <param name="time">時間</param>
	void SetTime(float time);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(const Camera& camera) const;
	/// <summary>
	/// ライトの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void DrawLight(const Camera& camera) const;
	/// <summary>
	/// アウトラインを付けたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void DrawOutline(const Camera& camera);
	/// <summary>
	/// ブルームをかけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void DrawBloom(const Camera& camera);

protected:
	/// <summary>
	/// グローバル変数の更新
	/// </summary>
	void ApplyGlobalVariable();
	/// <summary>
	/// オブジェクトの作成
	/// </summary>
	void CreateObjects();

protected:
	std::list<std::unique_ptr<BaseStageObject>> objects_; // オブジェクトのリスト
	std::unique_ptr<StageEditor> stageEditor_; // ステージエディター
	/// <summary>
	/// タイプ
	/// </summary>
	struct Type
	{
		uint32_t num; // 数
		uint32_t preNum; // 以前の数
		StageObjectType type; // オブジェクトのタイプ
		std::string mainName; // メインの名前
		std::string subName; // サブの名前
	};
	std::list<std::unique_ptr<Type>> types_; // タイプのリスト
};