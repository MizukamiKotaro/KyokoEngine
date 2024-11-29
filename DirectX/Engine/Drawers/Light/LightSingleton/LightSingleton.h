#pragma once
#include <memory>

class BaseLight;

// モデルなどを生成したときに最初に入れる用
class LightSingleton
{
public:
	static LightSingleton* GetInstance();

	void Initialize();

	const BaseLight* GetDirectionaLight() const { return directionalLight_.get(); }
	const BaseLight* GetPointLight() const { return pointLight_.get(); }
	const BaseLight* GetSpotLight() const { return spotLight_.get(); }

private:
	LightSingleton() = default;
	~LightSingleton() = default;
	LightSingleton(const LightSingleton&) = delete;
	LightSingleton& operator=(const LightSingleton&) = delete;

private:
	std::unique_ptr<BaseLight> directionalLight_;
	std::unique_ptr<BaseLight> pointLight_;
	std::unique_ptr<BaseLight> spotLight_;
};
