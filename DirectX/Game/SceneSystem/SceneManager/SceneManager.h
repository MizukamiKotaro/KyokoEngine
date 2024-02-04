#pragma once

#include <memory>

class IScene;
class SceneFactory;

class SceneManager
{
private:
	// シーンを保持するメンバ変数
	std::unique_ptr<IScene> scene_;

	// どのステージを呼び出すかを管理する変数
	int currentSceneNo_; // 現在のシーン
	int preSceneNo_; // 前のシーン

	std::unique_ptr<SceneFactory> sceneFactory_;

public:
	SceneManager();
	~SceneManager();

	int Run(); //この関数でゲームループを呼び出す

};

