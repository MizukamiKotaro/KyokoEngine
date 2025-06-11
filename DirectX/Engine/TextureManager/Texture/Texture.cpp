#include "Texture.h"
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"

Texture::~Texture()
{
	resource_->Release();
	intermediateResource_->Release();
}