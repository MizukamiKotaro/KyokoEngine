#include "ILight.h"
#include "ResourceManager/ResourceManager.h"

BaseLight::~BaseLight()
{
	ResourceManager::GetInstance()->AddReleaseResource(std::move(resource_));
}