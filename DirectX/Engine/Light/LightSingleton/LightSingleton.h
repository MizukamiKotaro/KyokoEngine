#pragma once

#include "DirectionalLight/DirectionalLight.h"
#include "PointLight/PointLight.h"
#include "SpotLight/SpotLight.h"

// モデルなどを生成したときに最初に入れる用
class LightSingleton
{
public:

	static LightSingleton* GetInstance();

	void Initialize();

	const DirectionalLight* GetDirectionaLight() const { return directionalLight_.get(); }

	const PointLight* GetPointLight() const { return pointLight_.get(); }

	const SpotLight* GetSpotLight() const { return spotLight_.get(); }

private:
	LightSingleton() = default;
	~LightSingleton() = default;
	LightSingleton(const LightSingleton&) = delete;
	LightSingleton& operator=(const LightSingleton&) = delete;

private:
	std::unique_ptr<DirectionalLight> directionalLight_;

	std::unique_ptr<PointLight> pointLight_;

	std::unique_ptr<SpotLight> spotLight_;
};
