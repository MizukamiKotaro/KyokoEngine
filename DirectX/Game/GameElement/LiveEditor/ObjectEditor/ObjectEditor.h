#pragma once
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"
#include "ModelData/ModelData.h"
/// <summary>
/// オブジェクトエディター
/// </summary>
class ObjectEditor : public BaseStageObject
{
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	ObjectEditor(const std::string& mainName, const std::string& name, uint32_t no);
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="time">デルタタイム</param>
	void Update(float time) override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(const Camera& camera) override;
private:
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	void SetGlobalVariable() override;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	void ApplyGlobalVariable() override;
	/// <summary>
	/// インスタンシング描画用の追加
	/// </summary>
	void AddInstancing();
	/// <summary>
	/// インスタンシング描画用の追加
	/// </summary>
	/// <param name="matrix">マトリクス</param>
	void AddInstancing(const Matrix4x4& matrix);
	/// <summary>
	/// インスタンシングのグループデータの取得
	/// </summary>
	/// <param name="tag">タグ</param>
	/// <returns>インスタンシングのグループデータ</returns>
	const InstancingGroupData* GetInstancingData(const std::string& tag);
private:
	const ModelData* modelData_; // モデルデータ
	std::string modelName_; // モデル名
	Vector3 position_; // 座標
	Vector3 rotate_; // 回転
	Vector3 scale_; // スケール
	Vector4 color_; // 色
	float allScale_; // 全体スケール
	bool isTwin_; // 左右対称に表示させるか
	bool isOutLine_; // アウトラインを付けるか
	bool isBloom_; // ブルームをかけるか
};
