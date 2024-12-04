#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return &instance;
}

void ResourceManager::BeginFrame()
{
	for (const Microsoft::WRL::ComPtr<ID3D12Resource>& resource : list_) {
		if (resource) {
			resource->Release();
		}
	}
	list_.clear();
}

void ResourceManager::Finalize()
{
	for (const Microsoft::WRL::ComPtr<ID3D12Resource>& resource : list_) {
		if (resource) {
			resource->Release();
		}
	}
	list_.clear();
}

void ResourceManager::AddResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
{
	list_.push_back(std::move(resource));
}
