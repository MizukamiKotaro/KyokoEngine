#pragma once

#include "SceneSystem/SceneBase/SceneBase.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "Sprite.h"
#include "HighLumi/HighLumi.h"

#include "Mosaic/Mosaic.h"
#include "RGBShift/RGBShift.h"

#include "GameElement/Live/SpotLightBox/SpotLightBox.h"
#include "GameElement/Live/SpotLightBoxAnimation/SpotLightBoxAnimation.h"

#include "Vignette/Vignette.h"
#include "Noise/Noise.h"
#include "Bloom/Bloom.h"
#include "RadialBlur/RadialBlur.h"
#include "SpotLightAndOutline/SpotLightAndOutline.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	/// <summary>
	/// ポストエフェクトの書き込み
	/// </summary>
	void WrightPostEffect();

private:

	std::unique_ptr<Dome> dome_; // ドーム
	std::unique_ptr<Stage> stage_; // ステージ
	std::unique_ptr<Screen> screen_; // スクリーン
	std::unique_ptr<SpotLightBoxAnimation> spotLightBox_; // スポットライト1
	std::unique_ptr<SpotLightBoxAnimation> spotLightBox2_; // スポットライト2

	std::unique_ptr<Sprite> title_; // タイトル
	std::unique_ptr<Sprite> space_; // スペース
	std::unique_ptr<Sprite> rainbow_; // 虹色
	float texcoodY_; // uvのy

	Audio se_; // SE

	// ポストエフェクト用
	std::unique_ptr<PostEffect> post_; // ポスト
	std::unique_ptr<HighLumi> highLumi_; // ハイルミ
	std::unique_ptr<Mosaic> mosaic_; // モザイク
	std::unique_ptr<RGBShift> rgbShift_; // rgbシフト
	std::unique_ptr<Vignette> vignette_; // ヴィネット
	std::unique_ptr<Noise> noise_; // ノイズ
	std::unique_ptr<Bloom> bloom_; // ブルーム
	std::unique_ptr<RadialBlur> radial_; // ラディアルブラー
	std::unique_ptr<SpotLightAndOutline> spotlightAndOutline_; // ステージ用

};

