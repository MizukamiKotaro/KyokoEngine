#pragma once
#include <array>
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"

class SpotLightBoxAnimationEditor;
/// <summary>
/// ツインのスポットライトエディター
/// </summary>
class TwinSpotLightBoxAnimationEditor : public BaseStageObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	TwinSpotLightBoxAnimationEditor(const std::string& mainName, const std::string& name, uint32_t no);
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
	/// <param name="camera">カメラ</param>
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

public:
	std::array<std::unique_ptr<SpotLightBoxAnimationEditor>, 2> lights_;// ライト
};