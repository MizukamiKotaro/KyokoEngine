#pragma once
#include "BasePostEffect/BasePostEffect.h"
/// <summary>
/// ノイズ
/// </summary>
class Noise : public BasePostEffect
{
public:
	Noise();
	~Noise() override;
	/// <summary>
	/// ノイズのタイプ
	/// </summary>
	enum NoiseType {
		RAND_NOISE, // ランダム
		MOSAIC_NOISE, // モザイク
		MOSAIC_LERP_NOISE, // モザイクラープ
		MOSAIC_VALUE_NOISE, // モザイクバリュー
		MOSAIC_PERLIN_NOISE, // パーリンノイズ
		MOSAIC_FRACTAL_SUM_PERLIN_NOISE, // フラクタルパーリンノイズ
		SANDSTORM, // 砂嵐
		LIGHTNING, // ライトニング
		WATER_SURFACE, // 水の揺れ
		WATER, // 水
	};

	void SetCameraPos(const Vector3& pos);

	void Initialize();

	void Update(float time);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;
	struct NoiseData {
		float density; // 密度
		float time; // 時間
		Vector2 screenSize; // スクリーンのサイズ
		Vector4 waterColor; // 水の靄の色
		Vector4 lightningColor; // 水の白のうねうねの色
		Vector2 cameraPos; // カメラの座標
		float moveScale; // 大きいほどカメラの影響を受けない
		int32_t type; // タイプ
		int32_t isNormal; // NormalBlendかどうか
	};
private:
	void CreateNoiseRes();
	void CreateResources() override;
private:
	Kyoko::ResourceManualRelease noiseResource_;
public:
	NoiseData* noiseData_;
	const Vector3* camera;
};