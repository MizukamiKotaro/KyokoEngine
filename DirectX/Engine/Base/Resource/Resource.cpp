#include "Resource.h"
#include "DirectXBase/DirectXBase.h"
#include "ResourceReleaser/ResourceReleaser.h"

// 響子
namespace Kyoko {
	void BaseResource::CreateResource(size_t sizeInBytes, D3D12_RESOURCE_FLAGS resourceFlags)
	{
		resource_ = DirectXBase::CreateBufferResource(sizeInBytes, resourceFlags);
	}
	void BaseResource::Map(void** ppData, UINT subresource, const D3D12_RANGE* pReadRange)
	{
		resource_->Map(subresource, pReadRange, ppData);
	}

	const D3D12_GPU_VIRTUAL_ADDRESS BaseResource::GetGPUVirtualAddress() const
	{
		return resource_->GetGPUVirtualAddress();
	}

	ID3D12Resource* BaseResource::Get() const
	{
		return resource_.Get();
	}

	ID3D12Resource** BaseResource::GetAddressOf()
	{
		return resource_.GetAddressOf();
	}

	ResourceManualRelease::~ResourceManualRelease()
	{
		ResourceReleaser::GetInstance()->AddManualResource(std::move(resource_));
	}
	ResourceAutoRelease::~ResourceAutoRelease()
	{
		ResourceReleaser::GetInstance()->AddResource(std::move(resource_));
	}
}