#pragma once
#include "RigidAnimationModel/RigidAnimationModel.h"
#include "SpotLight/SpotLight.h"
#include "PointLight/PointLight.h"
#include "GameElement/BaseStageObject/BaseStageObject.h"

class Camera;
/// <summary>
/// スポットライトエディター
/// </summary>
class SpotLightBoxAnimationEditor : public BaseStageObject
{
public:
	/// <summary>
	/// ステージエディター用コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	SpotLightBoxAnimationEditor(const std::string& mainName, const std::string& name, uint32_t no);
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpotLightBoxAnimationEditor();
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
	/// <summary>
	/// ライト部分の描画
	/// </summary>
	/// <param name="camera"></param>
	void DrawLight(const Camera& camera) override;

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
	/// ライトの更新
	/// </summary>
	void LightUpdate();
	/// <summary>
	/// 作成
	/// </summary>
	void Create();
	/// <summary>
	/// インスタンシングデータの作成
	/// </summary>
	void MakeInstancingData();
	/// <summary>
	/// インスタンシングの要素の追加
	/// </summary>
	void AddInstancing();

public:
	std::unique_ptr<SpotLight> spotLights_[2]; // スポットライト
	std::unique_ptr<RigidAnimationModel> box_; // ライトが出ている箱
	bool isDraw_ = true; // 描画するか
private:
	std::unique_ptr<PointLight> point_; // ポイントライト
};