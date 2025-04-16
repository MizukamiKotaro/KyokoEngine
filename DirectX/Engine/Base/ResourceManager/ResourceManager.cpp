#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return &instance;
}

void ResourceManager::BeginFrame()
{
	for (const Microsoft::WRL::ComPtr<ID3D12Resource>& resource : releaseList_) {
		if (resource) {
			resource->Release();
		}
	}
	releaseList_.clear();
	list_.clear();
}

void ResourceManager::Finalize()
{
	for (const Microsoft::WRL::ComPtr<ID3D12Resource>& resource : releaseList_) {
		if (resource) {
			resource->Release();
		}
	}
	releaseList_.clear();
	list_.clear();
}

void ResourceManager::AddResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
{
	list_.push_back(std::move(resource));
}

void ResourceManager::AddReleaseResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
{
	releaseList_.push_back(std::move(resource));
}
