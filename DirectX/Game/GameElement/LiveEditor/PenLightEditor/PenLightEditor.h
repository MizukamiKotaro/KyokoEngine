#pragma once
#include "RigidAnimationModel/RigidAnimationModel.h"
#include "GameElement/BaseStageObject/BaseStageObject.h"

class Camera;
/// <summary>
/// ペンライトエディター
/// </summary>
class PenLightEditor : public BaseStageObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	PenLightEditor(const std::string& mainName, const std::string& name, uint32_t no);
	/// <summary>
	/// 時間のセット
	/// </summary>
	/// <param name="time">時間</param>
	void SetTime(float time) override;
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
	/// インスタンシングデータの作成
	/// </summary>
	void MakeInstancingData();
	/// <summary>
	/// インスタンシングの要素の追加
	/// </summary>
	void AddInstancing();
private:
	// 仮実装だから雑
	std::unique_ptr<RigidAnimationModel> box_;
	bool isTwin_;
	float distance_;
	int32_t num_;
	int32_t n_;
	Vector4 color_;
	Vector3 angle_;
	Vector3 scale_;
	float length_;
	float y_;

};