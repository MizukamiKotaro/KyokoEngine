#include "Light.h"

const LightSingleton* Light::light_ = nullptr;

void Light::FirstInitialize()
{
	light_ = LightSingleton::GetInstance();
}

void Light::Initialize()
{
	directionalLight_ = light_->GetDirectionaLight();

	pointLight_ = light_->GetPointLight();

	spotLight_ = light_->GetSpotLight();
}
