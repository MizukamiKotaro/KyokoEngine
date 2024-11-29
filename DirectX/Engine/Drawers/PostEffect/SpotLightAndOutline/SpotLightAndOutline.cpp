#include "SpotLightAndOutline.h"

SpotLightAndOutline::SpotLightAndOutline()
{
	light_ = std::make_unique<LightDepth>();
	outline_ = std::make_unique<MemoDepth>();
	object_ = std::make_unique<MemoDepth>();
	bloomMemo_ = std::make_unique<MemoDepth>();
	bloom_ = std::make_unique<Bloom>();
	bloomTexture_ = std::make_unique<PostEffect>();

	// GPUに送るためのアドレスのセット
	light_->SetOutlineTex(outline_->GetSRVGPUDescriptorHandle());
	light_->SetOutlineDepth(outline_->GetDepthHandle());
	light_->SetObjectsTex(object_->GetSRVGPUDescriptorHandle());
	light_->SetObjectsDepth(object_->GetDepthHandle());
	light_->SetBloomTex(bloomTexture_->GetSRVGPUDescriptorHandle());
	light_->SetBloomDepth(bloomMemo_->GetDepthHandle());
}

SpotLightAndOutline::~SpotLightAndOutline()
{
}

void SpotLightAndOutline::Initialize()
{
}

void SpotLightAndOutline::Update()
{
}

void SpotLightAndOutline::Draw(const Camera& camera)
{
	// バリアの設定
	outline_->ToReadBarrier();
	object_->ToReadBarrier();
	bloomMemo_->ToReadBarrier();
	// 描画
	light_->Draw(camera);
	// バリアの再設定
	outline_->ToWriteBarrier();
	object_->ToWriteBarrier();
	bloomMemo_->ToWriteBarrier();
}

void SpotLightAndOutline::PreDrawLight()
{
	light_->PreDrawScene();
}

void SpotLightAndOutline::PostDrawLight()
{
	light_->PostDrawScene();
}

void SpotLightAndOutline::PreDrawOutline()
{
	outline_->PreDrawScene();
}

void SpotLightAndOutline::PostDrawOutline()
{
	outline_->PostDrawScene();
}

void SpotLightAndOutline::PreDrawObject()
{
	object_->PreDrawScene();
}

void SpotLightAndOutline::PostDrawObject()
{
	object_->PostDrawScene();
}

void SpotLightAndOutline::PreDrawBloom()
{
	bloomMemo_->PreDrawScene();
}

void SpotLightAndOutline::PostDrawBloom()
{
	bloomMemo_->PostDrawScene();

	// ブルームをかけるために書き込み
	bloom_->PreDrawScene();
	bloomMemo_->Draw();
	bloom_->PostDrawScene();

	// ブルームの結果を書き込み
	bloomTexture_->PreDrawScene();
	bloom_->Draw();
	bloomTexture_->PostDrawScene();
}
