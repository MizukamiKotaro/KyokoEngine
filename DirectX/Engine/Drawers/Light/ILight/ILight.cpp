#include "ILight.h"

BaseLight::~BaseLight()
{
	resource_->Release();
}