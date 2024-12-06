#pragma once

#include "PostEffect/PostEffect.h"
#include "HighLumi/HighLumi.h"
#include "GaussianBlur/GaussianBlur.h"
#include <memory>

/// <summary>
/// ブルーム
/// </summary>
class Bloom
{
public:

	Bloom();
	Bloom(const Vector2& size);
	~Bloom();
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
	void Draw();
	/// <summary>
	/// 書き込み前処理
	/// </summary>
	void PreDrawScene();
	/// <summary>
	/// 書き込み後処理
	/// </summary>
	void PostDrawScene();
	/// <summary>
	/// ハイルミのデータ取得
	/// </summary>
	/// <returns>ハイルミのデータ</returns>
	HighLumi::HighLumiData* GetHighLumiData() const { return highLumi_->highLumiData_; }

private:
	std::unique_ptr<PostEffect> postEffect_; // 書き込み用
	std::unique_ptr<HighLumi> highLumi_; // 輝度の高い色抽出用
	std::unique_ptr<GaussianBlur> gaussianBlur_; // ガウシアンブラー用

};

