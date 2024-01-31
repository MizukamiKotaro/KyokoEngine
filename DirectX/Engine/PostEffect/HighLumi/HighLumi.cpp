#include "HighLumi.h"

#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "WindowsInfo/WindowsInfo.h"

HighLumi::HighLumi()
{
	piplineType_ = GraphicsPiplineManager::PiplineType::HIGH_LUMI;

	//CreatePostEffect();
}

HighLumi::~HighLumi()
{
	vertexResource_->Release();
	transformResource_->Release();
	materialResource_->Release();
	DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap()->DeleteDescriptor(srvHandles_);
	DescriptorHeapManager::GetInstance()->GetRTVDescriptorHeap()->DeleteDescriptor(rtvHandles_);
	DescriptorHeapManager::GetInstance()->GetDSVDescriptorHeap()->DeleteDescriptor(dsvHandles_);
}

