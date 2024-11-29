#pragma once
#include <wrl.h>
#include <d3d12.h>
/// <summary>
/// ライトのタイプ
/// </summary>
enum class LightType {
	kDirectionalLight, // 平行光源
	kPointLight, // ポイントライト
	kSpotLight // スポットライト
};
/// <summary>
/// ライトの基盤
/// </summary>
class BaseLight
{
public:
	virtual ~BaseLight();
	virtual void Update() = 0;
	/// <summary>
	/// GPUアドレスの取得
	/// </summary>
	/// <returns>GPUアドレス</returns>
	const D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const { return resource_->GetGPUVirtualAddress(); }
	/// <summary>
	/// タイプの取得
	/// </summary>
	/// <returns>タイプ</returns>
	const LightType GetLightType() const { return lightType_; }
protected:
	LightType lightType_; // タイプ
	Microsoft::WRL::ComPtr<ID3D12Resource> resource_; // リソース
};