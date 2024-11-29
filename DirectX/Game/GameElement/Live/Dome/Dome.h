#pragma once
#include "Model.h"
#include <memory>

class Camera;
/// <summary>
/// ステージのドーム
/// </summary>
class Dome {
public: 
	Dome();
	void Initialize();
	void Update();
	void Draw(Camera* camera);

private:
	std::unique_ptr<Model> model_;
};
