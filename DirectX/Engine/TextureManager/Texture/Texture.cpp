#include "Texture.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"

Texture::~Texture()
{
	resource_->Release();
	intermediateResource_->Release();
}