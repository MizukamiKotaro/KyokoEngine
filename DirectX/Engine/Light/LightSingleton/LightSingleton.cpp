#include "LightSingleton.h"
#include "Light/Light.h"

LightSingleton* LightSingleton::GetInstance()
{
	static LightSingleton instance;
	return &instance;
}

void LightSingleton::Initialize()
{
	directionalLight_ = std::make_unique<DirectionalLight>();
	pointLight_ = std::make_unique<PointLight>();
	spotLight_ = std::make_unique<SpotLight>();

	Light::FirstInitialize();
}
