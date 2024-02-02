#pragma once

#include "LightSingleton/LightSingleton.h"

// モデルなどの変数に使う用
class Light 
{
public:
	static void FirstInitialize();

	void Initialize();

	void SetDirectionalLight(const DirectionalLight* light) { directionalLight_ = light; }

	void SetPointLight(const PointLight* light) { pointLight_ = light; }

	void SetSpotLight(const SpotLight* light) { spotLight_ = light; }

	const D3D12_GPU_VIRTUAL_ADDRESS GetDirectionalLightGPUVirtualAddress() const { return directionalLight_->GetGPUVirtualAddress(); }

	const D3D12_GPU_VIRTUAL_ADDRESS GetPointLightGPUVirtualAddress() const { return pointLight_->GetGPUVirtualAddress(); }

	const D3D12_GPU_VIRTUAL_ADDRESS GetSpotLightGPUVirtualAddress() const { return spotLight_->GetGPUVirtualAddress(); }

private:

	static const LightSingleton* light_;

	const DirectionalLight* directionalLight_ = nullptr;

	const PointLight* pointLight_ = nullptr;

	const SpotLight* spotLight_ = nullptr;
};
