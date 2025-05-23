#pragma once
#include "Model.h"
#include <memory>

class Camera;

/// <summary>
/// ステージのステージ
/// </summary>
class Stage {
public: 
	Stage();
	void Initialize();
	void Update();
	void Draw(Camera* camera);

private:
	std::unique_ptr<Model> model_;
};
