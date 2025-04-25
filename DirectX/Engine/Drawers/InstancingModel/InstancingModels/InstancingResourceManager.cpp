#include "InstancingResourceManager.h"
#include "DirectXBase/DirectXBase.h"
#include <algorithm>
#include "Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Descriptor/DescriptorHeap/DescriptorHeap.h"

void InstancingResourceManager::CreateSRV(const int32_t& num, const InstancingGroupData* modelData)
{
	for (int32_t i = 0; i < num; i++) {
		resources_[modelData]->instancingResources_.push_back(InstancingResources{});
		InstancingResources& resource = resources_[modelData]->instancingResources_.back();
		resource.instancingResource_ = DirectXBase::CreateBufferResource(sizeof(ParticleForGPU) * kNumInstance);
		resource.instancingData_ = nullptr;
		resource.instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&resource.instancingData_));

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		srvDesc.Buffer.NumElements = kNumInstance;
		srvDesc.Buffer.StructureByteStride = sizeof(ParticleForGPU);

		resource.srvHandles_ = Kyoko::Descriptor::DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap()->GetNewDescriptorHandle();

		DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(resource.instancingResource_.Get(), &srvDesc, resource.srvHandles_->cpuHandle);
	}
}

InstancingResourceManager* InstancingResourceManager::GetInstance()
{
	static InstancingResourceManager instance;
	return &instance;
}

void InstancingResourceManager::Clear()
{
	for (std::pair<const InstancingGroupData* const, std::unique_ptr<Resources>>& resource : resources_) {
		resource.second->instancingNum_ = 0;
	}
}

void InstancingResourceManager::Finalize()
{
	for (std::pair<const InstancingGroupData* const, std::unique_ptr<Resources>>& resource : resources_) {
		for (InstancingResources& res : resource.second->instancingResources_) {
			res.instancingResource_->Release();
			Kyoko::Descriptor::DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap()->AddDeleteDescriptor(res.srvHandles_);
		}
		resource.second->materialResource_->Release();
	}
}

void InstancingResourceManager::AddResource(const InstancingGroupData* modelData)
{
	if (resources_.find(modelData) == resources_.end()) {
		resources_[modelData] = std::make_unique<Resources>();

		resources_[modelData]->materialResource_ = DirectXBase::CreateBufferResource(sizeof(Material));

		resources_[modelData]->materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&resources_[modelData]->materialData_));
		*resources_[modelData]->materialData_ = { Vector4(1.0f, 1.0f, 1.0f, 1.0f) , 0 };

		resources_[modelData]->instancingNum_ = 0;
		CreateSRV(5, modelData);
	}
}

InstancingResourceManager::Resources* InstancingResourceManager::GetResources(const InstancingGroupData* modelData)
{
	if (resources_.find(modelData) != resources_.end()) {
		return resources_[modelData].get();
	}

	return nullptr;
}
