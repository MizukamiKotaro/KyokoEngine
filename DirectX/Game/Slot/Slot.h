#pragma once
#include "Light/Light.h"
#include <memory>
#include <array>
#include "Sprite.h"
#include "PostEffect/PostEffect.h"
#include "Model.h"

class Camera;

class Slot {
public: 

	Slot();

	void Initialize();

	void Update(Camera* camera);

	void Draw(Camera* camera);

public:

	void StartRotation();

	void StopSlot(int num);

private:

	void PostEffectWright(Camera* camera);

	void DownToTop();

private:

	std::unique_ptr<PostEffect> postEffect_;

	std::unique_ptr<Model> plane_;
	
	std::array<std::array<std::unique_ptr<Sprite>, 3>, 3> slot_;

	std::unique_ptr<Sprite> back_;

	std::array<float, 3> rotSpeed_;
};
