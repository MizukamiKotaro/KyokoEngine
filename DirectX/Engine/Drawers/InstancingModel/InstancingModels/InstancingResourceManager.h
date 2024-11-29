#pragma once
#include <list>
#include <memory>
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "InstancingModelData.h"
#include <unordered_map>

/// <summary>
/// インスタンシング用のリソースマネージャー
/// </summary>
class InstancingResourceManager
{
public:
	static const uint32_t kNumInstance = 10000; // インスタンスの数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static InstancingResourceManager* GetInstance();
	/// <summary>
	/// マテリアル
	/// </summary>
	struct Material
	{
		Vector4 color; // 色
		int32_t enableLighting; // ライトのタイプ
	};
	
	struct ParticleForGPU {
		Matrix4x4 WVP;
		Matrix4x4 World;
		Matrix4x4 uvMatrix;
		Vector4 color;
	};

	struct InstancingResources {
		Microsoft::WRL::ComPtr<ID3D12Resource> instancingResource_;
		ParticleForGPU* instancingData_;
		const DescriptorHandles* srvHandles_;
	};

	struct Resources
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
		Material* materialData_;
		std::vector<InstancingResources> instancingResources_;
		int32_t instancingNum_;
	};

	void Clear();
	void Finalize();

	void AddResource(const InstancingGroupData* modelData);
	Resources* GetResources(const InstancingGroupData* modelData);
	void CreateSRV(const int32_t& num, const InstancingGroupData* modelData);

private:
	InstancingResourceManager() = default;
	~InstancingResourceManager() = default;
	InstancingResourceManager(const InstancingResourceManager&) = delete;
	const InstancingResourceManager& operator=(const InstancingResourceManager&) = delete;


private:
	
	std::unordered_map<const InstancingGroupData*, std::unique_ptr<Resources>> resources_;
};