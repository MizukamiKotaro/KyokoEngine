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
	void WrightPostEffect();

private:

	std::unique_ptr<HighLumi> highLumi_;
	std::unique_ptr<PostEffect> post_;
	std::unique_ptr<Sprite> rainbow_;
	float texcoodY_;

	std::unique_ptr<Dome> dome_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<Screen> screen_;


	std::unique_ptr<Sprite> title_;
	std::unique_ptr<Sprite> space_;

	std::unique_ptr<Mosaic> mosaic_;
	std::unique_ptr<RGBShift> rgbShift_;

	std::unique_ptr<SpotLightBoxAnimation> spotLightBox_;
	std::unique_ptr<SpotLightBoxAnimation> spotLightBox2_;

	std::unique_ptr<Vignette> vignette_;
	std::unique_ptr<Noise> noise_;
	
	std::unique_ptr<Bloom> bloom_;
	std::unique_ptr<RadialBlur> radial_;

	Audio se_;
	std::unique_ptr<SpotLightAndOutline> spotlightAndOutline_;
};

