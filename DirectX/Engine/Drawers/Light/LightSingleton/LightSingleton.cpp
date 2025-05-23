#include "LightSingleton.h"
#include "Light/Light.h"
#include "DirectionalLight/DirectionalLight.h"
#include "PointLight/PointLight.h"
#include "SpotLight/SpotLight.h"

LightSingleton* LightSingleton::GetInstance()
{
	static LightSingleton instance;
	return &instance;
}

void LightSingleton::Initialize()
{
	Light::StaticInitialize();

	directionalLight_ = std::make_unique<DirectionalLight>();
	pointLight_ = std::make_unique<PointLight>();
	spotLight_ = std::make_unique<SpotLight>();

}

void LightSingleton::Finalize()
{
	directionalLight_.reset();
	pointLight_.reset();
	spotLight_.reset();
}
