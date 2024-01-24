#pragma once
#include <memory>
#include "GameElement/Live/Live.h"


class Camera;

class Game {
public: 

	Game();

	void Initialize(Camera* camera);

	void Update();

	void Draw(Camera* camera);

private:
	
	std::unique_ptr<Live> live_;

};
