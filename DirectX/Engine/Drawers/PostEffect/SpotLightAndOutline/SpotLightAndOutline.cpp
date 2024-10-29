#include "SpotLightAndOutline.h"

SpotLightAndOutline::SpotLightAndOutline()
{
	light_ = std::make_unique<LightDepth>();
	outline_ = std::make_unique<MemoDepth>();
	object_ = std::make_unique<MemoDepth>();
	bloomMemo_ = std::make_unique<MemoDepth>();
	bloom_ = std::make_unique<Bloom>();
	bloomTexture_ = std::make_unique<PostEffect>();

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
	outline_->ToReadBarrier();
	object_->ToReadBarrier();
	bloomMemo_->ToReadBarrier();
	light_->Draw(camera);
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

	bloom_->PreDrawScene();
	bloomMemo_->Draw();
	bloom_->PostDrawScene();

	bloomTexture_->PreDrawScene();
	bloom_->Draw();
	bloomTexture_->PostDrawScene();
}
