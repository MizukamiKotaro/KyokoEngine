#pragma once
#include <memory>
#include "SceneSystem/ISceneFactory/ISceneFactory.h"
#include "SceneSystem/IScene/IScene.h"
class Input;
class FrameInfo;

class SceneManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// アプリループ
	/// </summary>
	int Run();
private:
	// シーンを保持するメンバ変数
	std::unique_ptr<IScene> scene_;

	int currentSceneNo_; // 現在のシーン
	int preSceneNo_; // 前のシーン

	std::unique_ptr<ISceneFactory> sceneFactory_; // シーンファクトリー

	Input* input_; // 入力
	FrameInfo* frameInfo_; // フレーム情報
};