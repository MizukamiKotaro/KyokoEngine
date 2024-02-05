#pragma once

#include "SceneSystem/IScene/IScene.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "Sprite.h"
#include <array>
#include "Particle.h"

class SelectScene : public IScene
{
public:
	SelectScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Particle> pa_;

	std::unique_ptr<Sprite> sp_;
	const Texture* tex0;
	const Texture* tex1;
	bool is1 = false;
	bool a = false;

	bool x = false;
	bool y = false;

	Vector2 l = { 0.0f,0.0f };
	Vector2 s = { 1.0f,1.0f };
	Vector4 c = { 1.0f,1.0f,1.0f,1.0f };
	
	Audio se_;
};

