#pragma once

#include <memory>
#include "SceneSystem/SceneFactory/SceneFactory.h"
#include "SceneSystem/IScene/IScene.h"

class Input;

class SceneManager
{
private:
	// シーンを保持するメンバ変数
	std::unique_ptr<IScene> scene_;

	// どのステージを呼び出すかを管理する変数
	int currentSceneNo_; // 現在のシーン
	int preSceneNo_; // 前のシーン

	std::unique_ptr<SceneFactory> sceneFactory_;

	Input* inputManager_;

public:
	SceneManager();

	int Run(); //この関数でゲームループを呼び出す

};

