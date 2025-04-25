#include "SkinClustr.h"
#include "Base/Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Base/Descriptor/DescriptorHeap/DescriptorHeap.h"

SkinCluster::~SkinCluster()
{
	Kyoko::Descriptor::DescriptorHeap* srvHeap = Kyoko::Descriptor::DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap();
	srvHeap->AddDeleteDescriptor(influenceSrvHandle);
	srvHeap->AddDeleteDescriptor(inputVertexSrvHandle);
	srvHeap->AddDeleteDescriptor(outputVertexSrvHandle);
	srvHeap->AddDeleteDescriptor(paletteSrvHandle);
}
