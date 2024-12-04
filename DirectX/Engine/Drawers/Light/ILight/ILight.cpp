#include "ILight.h"
#include "ResourceManager/ResourceManager.h"

BaseLight::~BaseLight()
{
	ResourceManager::GetInstance()->AddResource(std::move(resource_));
}