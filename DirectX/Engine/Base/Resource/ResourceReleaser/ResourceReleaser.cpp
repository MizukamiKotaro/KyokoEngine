#include "ResourceReleaser.h"

namespace Kyoko {
	ResourceReleaser* ResourceReleaser::GetInstance()
	{
		static ResourceReleaser instance;
		return &instance;
	}

	void ResourceReleaser::BeginFrame()
	{
		for (const Microsoft::WRL::ComPtr<ID3D12Resource>& resource : manualList_) {
			if (resource) {
				resource->Release();
			}
		}
		manualList_.clear();
		list_.clear();
	}

	void ResourceReleaser::Finalize()
	{
		for (const Microsoft::WRL::ComPtr<ID3D12Resource>& resource : manualList_) {
			if (resource) {
				resource->Release();
			}
		}
		manualList_.clear();
		list_.clear();
	}

	void ResourceReleaser::AddResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
	{
		list_.push_back(std::move(resource));
	}

	void ResourceReleaser::AddManualResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
	{
		manualList_.push_back(std::move(resource));
	}
}
