#pragma once
#include "Editor/StageEditor.h"
class Camera;
class InstancingModelManager;
class InstancingGroupData;

/// <summary>
/// ステージオブジェクトの基盤
/// </summary>
class BaseStageObject
{
public:
	/// <summary>
	/// 共通部分の初期化
	/// </summary>
	static void StaticInitialize();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseStageObject() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	virtual void Update(float deltaTime = 0) = 0;
	/// <summary>
	/// タイムのセット
	/// </summary>
	/// <param name="time">タイム</param>
	virtual void SetTime(float time);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void Draw(const Camera& camera) = 0;
	/// <summary>
	/// ライトの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void DrawLight(const Camera& camera);
	/// <summary>
	/// アウトラインをつけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void DrawOutline(const Camera& camera);
	/// <summary>
	/// ブルームをかけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void DrawBloom(const Camera& camera);

protected:
	/// <summary>
	/// ステージエディターの設定
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	/// <param name="isMany">沢山配置するか</param>
	void CreateStageEditor(const std::string& mainName, const std::string& name, uint32_t no, bool isMany = false);
	/// <summary>
	/// 個別でのステージエディターの設定
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="treeName">ツリー名</param>
	/// <param name="no">ナンバー</param>
	/// <param name="isMany">沢山配置するか</param>
	void CreateStageEditor(const std::string& mainName, const std::string& name, const std::string& treeName, uint32_t no, bool isMany = false);
	/// <summary>
	/// エディターの初期化
	/// </summary>
	void InitializeEditor();
	/// <summary>
	/// グローバル変数の更新
	/// </summary>
	void UpdateGlobalVariable();
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	virtual void SetGlobalVariable() = 0;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	virtual void ApplyGlobalVariable() = 0;

	std::unique_ptr<StageEditor> stageEditor_; // ステージエディター
	static InstancingModelManager* instancingManager_; // インスタンシングマネージャー
	const InstancingGroupData* instancingData_; // インスタンシングデータ
};