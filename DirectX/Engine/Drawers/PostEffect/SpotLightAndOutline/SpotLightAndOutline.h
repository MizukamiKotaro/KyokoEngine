#pragma once
#include "MemoDepth/MemoDepth.h"
#include "LightDepth/LightDepth.h"
#include <memory>
#include "Bloom/Bloom.h"

/// <summary>
/// ライブステージ用ポストエフェクト
/// </summary>
class SpotLightAndOutline
{
public:
	SpotLightAndOutline();
	SpotLightAndOutline(const Vector2& size);
	~SpotLightAndOutline();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(const Camera& camera);
	/// <summary>
	/// ライト描画前処理
	/// </summary>
	void PreDrawLight();
	/// <summary>
	/// ライト描画後処理
	/// </summary>
	void PostDrawLight();
	/// <summary>
	/// アウトライン描画前処理
	/// </summary>
	void PreDrawOutline();
	/// <summary>
	/// アウトライン描画後処理
	/// </summary>
	void PostDrawOutline();
	/// <summary>
	/// 通常描画前処理
	/// </summary>
	void PreDrawObject();
	/// <summary>
	/// 通常描画後処理
	/// </summary>
	void PostDrawObject();
	/// <summary>
	/// ブルーム描画前処理
	/// </summary>
	void PreDrawBloom();
	/// <summary>
	/// ブルーム描画後処理
	/// </summary>
	void PostDrawBloom();

private:
	std::unique_ptr<LightDepth> light_; // ライトの用
	std::unique_ptr<MemoDepth> outline_; // アウトライン用
	std::unique_ptr<MemoDepth> object_; // 通常オブジェクト用
	std::unique_ptr<MemoDepth> bloomMemo_; // ブルーム用
	std::unique_ptr<Bloom> bloom_; // ブルーム
	std::unique_ptr<PostEffect> bloomTexture_; // ブルームテクスチャ
};

