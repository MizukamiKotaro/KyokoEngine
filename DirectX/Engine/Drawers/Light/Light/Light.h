#pragma once
#include <d3d12.h>

class LightSingleton;
class BaseLight;

// モデルなどの変数に使う用
class Light 
{
public:
	static void StaticInitialize();

	void Initialize();

	void SetLight(const BaseLight* light);

	const D3D12_GPU_VIRTUAL_ADDRESS GetDirectionalLightGPUVirtualAddress() const;
	const D3D12_GPU_VIRTUAL_ADDRESS GetPointLightGPUVirtualAddress() const;
	const D3D12_GPU_VIRTUAL_ADDRESS GetSpotLightGPUVirtualAddress() const;

private:
	static const LightSingleton* light_;

	const BaseLight* directionalLight_ = nullptr;
	const BaseLight* pointLight_ = nullptr;
	const BaseLight* spotLight_ = nullptr;
};